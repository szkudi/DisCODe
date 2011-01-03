/*!
 * \file CvFilter2D_Processor.cpp
 * \brief
 * \author mstefanc
 * \date 2010-07-05
 */

#include <memory>
#include <string>
#include <iostream>

#include "KS_BarcodeReader.hpp"
#include "Logger.hpp"

#include "MagickBitmapSource.h"
#include <zxing/Binarizer.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/Result.h>
#include <zxing/ReaderException.h>
#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/common/HybridBinarizer.h>
#include <exception>
#include <zxing/Exception.h>
#include <zxing/common/IllegalArgumentException.h>

#include <zxing/qrcode/QRCodeReader.h>



#include <vector>

using namespace Magick;
using namespace std;
using namespace zxing;

namespace Processors {
namespace BCReader {

KS_BarcodeReader::KS_BarcodeReader(const std::string & name) : Base::Component(name)
{
	LOG(LTRACE) << "Hello KS_BarcodeReader\n";

	raw_dump = false;
	show_format = false;
	tryHarder = false;
	show_filename = false;

}

KS_BarcodeReader::~KS_BarcodeReader()
{
	LOG(LTRACE) << "Good bye KS_BarcodeReader\n";
}

bool KS_BarcodeReader::onInit()
{
	LOG(LTRACE) << "KS_BarcodeReader::initialize\n";

	h_onNewImage.setup(this, &KS_BarcodeReader::onNewImage);
	registerHandler("onNewImage", &h_onNewImage);

	registerStream("in_img", &in_img);
	return true;
}

bool KS_BarcodeReader::onFinish()
{
	LOG(LTRACE) << "KS_BarcodeReader::finish\n";

	return true;
}

bool KS_BarcodeReader::onStep()
{
	LOG(LTRACE) << "KS_BarcodeReader::step\n";
	return true;
}

bool KS_BarcodeReader::onStop()
{
	return true;
}

bool KS_BarcodeReader::onStart()
{
	return true;
}

void KS_BarcodeReader::onNewImage()
{
	LOG(LTRACE) << "KS_BarcodeReader::onNewImage\n";
	try {
		Magick::Image img = in_img.read();

		  try {
		    Ref<MagickBitmapSource> source(new MagickBitmapSource(img));

		    Ref<Binarizer> binarizer(NULL);
//		    if (false) {
//		      binarizer = new LocalBlockBinarizer(source);
//		    } else {
		      binarizer = new GlobalHistogramBinarizer(source);
//		    }


		    Ref<BinaryBitmap> image(new BinaryBitmap(binarizer));
		    zxing::qrcode::QRCodeReader reader;
		    Ref<Result> result(reader.decode(image));

		    cout << result->getText()->getText() << endl;
		  } catch (zxing::Exception& e) {
			cerr << "Error: " << e.what() << endl;
		  }

	} catch (...) {
		LOG(LERROR) << "KS_BarcodeReader::onNewImage failed\n";
	}

}

Ref<Result> KS_BarcodeReader::decode(Ref<BinaryBitmap> image, DecodeHints hints)
{
  Ref<Reader> reader(new MultiFormatReader);
  return reader->decode(image, hints);
}


int KS_BarcodeReader::test_image(Image& image, bool hybrid, string expected = "")
{

  string cell_result;
  int res = -1;

  Ref<BitMatrix> matrix(NULL);
  Ref<Binarizer> binarizer(NULL);
  const char* result_format = "";

  try {
    Ref<MagickBitmapSource> source(new MagickBitmapSource(image));

    if (hybrid) {
      binarizer = new HybridBinarizer(source);
    } else {
      binarizer = new GlobalHistogramBinarizer(source);
    }

    DecodeHints hints(DecodeHints::DEFAULT_HINT);
    hints.setTryHarder(tryHarder);
    Ref<BinaryBitmap> binary(new BinaryBitmap(binarizer));
    Ref<Result> result(decode(binary, hints));
    cell_result = result->getText()->getText();
    result_format = barcodeFormatNames[result->getBarcodeFormat()];
    res = 0;
  } catch (ReaderException e) {
    cell_result = "zxing::ReaderException: " + string(e.what());
    res = -2;
  } catch (zxing::IllegalArgumentException& e) {
    cell_result = "zxing::IllegalArgumentException: " + string(e.what());
    res = -3;
  } catch (zxing::Exception& e) {
    cell_result = "zxing::Exception: " + string(e.what());
    res = -4;
  } catch (std::exception& e) {
    cell_result = "std::exception: " + string(e.what());
    res = -5;
  }

  if (cell_result.compare(expected)) {
    res = -6;
    if (!raw_dump) {
        cout << (hybrid ? "Hybrid" : "Global") << " binarizer failed:\n";
        if (expected.length() >= 0) {
          cout << "  Expected: " << expected << "\n";
        }
        cout << "  Detected: " << cell_result << endl;
    }
  }


  if (raw_dump && !hybrid) {/* don't print twice, and global is a bit better */
    cout << cell_result;
    if (show_format) {
      cout << " " << result_format;
    }
    cout << endl;

  }
  return res;
}

int KS_BarcodeReader::test_image_hybrid(Image& image, string expected = "")
{
  return test_image(image, true, expected);
}

int KS_BarcodeReader::test_image_global(Image& image, string expected = "")
{
  return test_image(image, false, expected);
}

string KS_BarcodeReader::get_expected(string imagefilename)
{
  string textfilename = imagefilename;
  int dotpos = textfilename.rfind(".");
  textfilename.replace(dotpos+1, textfilename.length() - dotpos - 1, "txt");
  char data[MAX_EXPECTED];
  FILE *fp = fopen(textfilename.data(), "rb");

  if (!fp) {
    // could not open file
    return "";
  }
  // get file size
  fseek(fp, 0, SEEK_END);
  int toread = ftell(fp);
  rewind(fp);

  if (toread > MAX_EXPECTED) {
  	cerr << "MAX_EXPECTED = " << MAX_EXPECTED << " but file '" << textfilename << "' has " << toread
  	     << " bytes! Skipping..." << endl;
    fclose(fp);
    return "";
  }

  int nread = fread(data, sizeof(char), toread, fp);
  if (nread != toread) {
    cerr << "Could not read entire contents of file '" << textfilename << "'! Skipping..." << endl;
    fclose(fp);
    return "";
  }
  fclose(fp);
  data[nread] = '\0';
  string expected(data);
  return expected;
}

}//: namespace BCReader
}//: namespace Processors
