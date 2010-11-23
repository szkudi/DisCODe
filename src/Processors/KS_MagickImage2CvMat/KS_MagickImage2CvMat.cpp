/*
 * KS_MagickImage2CvMat.cpp
 *
 *  Created on: 22-11-2010
 *      Author: szkudi
 */

#include "KS_MagickImage2CvMat.hpp"

namespace Processors{

namespace MI2CvMat {

KS_MagickImage2CvMat::KS_MagickImage2CvMat(const std::string & name) : Base::Component(name)
{
	LOG(TRACE) << "Hello KS_MagickImage2CvMat\n";
}

KS_MagickImage2CvMat::~KS_MagickImage2CvMat()
{
	LOG(TRACE) << "Good bye KS_MagickImage2CvMat\n";
}

bool KS_MagickImage2CvMat::onInit()
{
	LOG(TRACE) << "KS_MagickImage2CvMat::initialize\n";

	h_onNewImage.setup(this, &KS_MagickImage2CvMat::onNewImage);
	registerHandler("onNewImage", &h_onNewImage);

	registerStream("in_img", &in_img);

	newImage = registerEvent("newImage");

	registerStream("out_img", &out_img);

	return true;
}

bool KS_MagickImage2CvMat::onFinish()
{
	LOG(TRACE) << "KS_MagickImage2CvMat::finish\n";

	return true;
}

bool KS_MagickImage2CvMat::onStep()
{
	LOG(TRACE) << "KS_MagickImage2CvMat::step\n";
	return true;
}

bool KS_MagickImage2CvMat::onStop()
{
	return true;
}

bool KS_MagickImage2CvMat::onStart()
{
	return true;
}

void KS_MagickImage2CvMat::onNewImage()
{
	LOG(TRACE) << "KS_MagickImage2CvMat::onNewImage\n";
	try {
		Magick::Image img = in_img.read();

		cv::Size size;

		size.height = img.size().height();
		size.width = img.size().width();

		char pixels[size.width * size.height];

		img.write(0, 0, size.width, size.height, "RGB", MagickCore::CharPixel, pixels);

		cv::Mat mimg(size, CV_8UC3, pixels );

		out_img.write(mimg);

		newImage->raise();
	} catch (...) {
		LOG(ERROR) << "KS_MagickImage2CvMat::onNewImage failed\n";
	}

}

}
