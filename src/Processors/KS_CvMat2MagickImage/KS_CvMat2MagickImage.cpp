/*!
 * \file CvFilter2D_Processor.cpp
 * \brief
 * \author mstefanc
 * \date 2010-07-05
 */

#include <memory>
#include <string>

#include "KS_CvMat2MagickImage.hpp"
namespace Processors {
namespace CvMat2MI {

KS_CvMat2MagickImage::KS_CvMat2MagickImage(const std::string & name) : Base::Component(name)
{
	LOG(TRACE) << "Hello KS_CvMat2MagickImage\n";
}

KS_CvMat2MagickImage::~KS_CvMat2MagickImage()
{
	LOG(TRACE) << "Good bye KS_CvMat2MagickImage\n";
}

bool KS_CvMat2MagickImage::onInit()
{
	LOG(TRACE) << "KS_CvMat2MagickImage::initialize\n";

	h_onNewImage.setup(this, &KS_CvMat2MagickImage::onNewImage);
	registerHandler("onNewImage", &h_onNewImage);

	registerStream("in_img", &in_img);

	newImage = registerEvent("newImage");

	registerStream("out_img", &out_img);

	return true;
}

bool KS_CvMat2MagickImage::onFinish()
{
	LOG(TRACE) << "KS_CvMat2MagickImage::finish\n";

	return true;
}

bool KS_CvMat2MagickImage::onStep()
{
	LOG(TRACE) << "KS_CvMat2MagickImage::step\n";
	return true;
}

bool KS_CvMat2MagickImage::onStop()
{
	return true;
}

bool KS_CvMat2MagickImage::onStart()
{
	return true;
}

void KS_CvMat2MagickImage::onNewImage()
{
	LOG(TRACE) << "KS_CvMat2MagickImage::onNewImage\n";
	try {
		cv::Mat img = in_img.read();

		img.convertTo(img, CV_8UC3);


//		Magick::Blob blob(img.data, img.rows * img.cols);
		Magick::Image mimg;

		cv::Size size = img.size();

		mimg.read(size.width, size.height, "RGB", MagickCore::CharPixel, (void *)img.data);
//		mimg.read(blob);

		out_img.write(mimg);

		newImage->raise();
	} catch (...) {
		LOG(ERROR) << "KS_CvMat2MagickImage::onNewImage failed\n";
	}

}

}//: namespace CvMat2IM
}//: namespace Processors
