/*
 * KS_MagickImage2CvMat.cpp
 *
 *  Created on: 22-11-2010
 *      Author: szkudi
 */

#include "KS_ROICrop.hpp"
#include "Logger.hpp"

using namespace Types;

namespace Processors{

namespace ROIC {

KS_ROICrop::KS_ROICrop(const std::string & name) : Base::Component(name)
{
	LOG(LTRACE) << "Hello KS_ROICrop\n";
}

KS_ROICrop::~KS_ROICrop()
{
	LOG(LTRACE) << "Good bye KS_ROICrop\n";
}

bool KS_ROICrop::onInit()
{
	LOG(LTRACE) << "KS_ROICrop::initialize\n";

	h_onNewImage.setup(this, &KS_ROICrop::onNewImage);
	registerHandler("onNewImage", &h_onNewImage);

	registerStream("in_img", &in_img);

	h_onNewDrawable.setup(this, &KS_ROICrop::onNewDrawable);
	registerHandler("onNewDrawable", &h_onNewDrawable);

	registerStream("in_container", &in_container);


	newImage = registerEvent("newImage");

	registerStream("out_img", &out_img);

	img_ready = false;
	container_ready = false;

	return true;
}

bool KS_ROICrop::onFinish()
{
	LOG(LTRACE) << "KS_ROICrop::finish\n";

	return true;
}

bool KS_ROICrop::onStep()
{
	LOG(LTRACE) << "KS_ROICrop::step\n";
	try{
		img_ready = false;
		container_ready = false;

		for(unsigned int i = 0; i < container.getSize(); ++i){
			Rectangle* it = (Rectangle*)container.get(i);
			cv::Point p1 = it->get(0);
			cv::Point p2 = it->get(1);

			cv::Mat tmp(img, cv::Rect(p1, p2));

			out_img.write(cv::Mat(img, cv::Rect(p1, p2)).clone());
			newImage->raise();
		}
	}catch(...){
		LOG(LERROR) << "KS_ROICrop::step\n";
	}

	return true;
}

bool KS_ROICrop::onStop()
{
	return true;
}

bool KS_ROICrop::onStart()
{
	return true;
}

void KS_ROICrop::onNewImage()
{
	LOG(LTRACE) << "KS_ROICrop::onNewImage\n";
	try {
		img = in_img.read();
		img_ready = true;
		if(img_ready && container_ready)
			onStep();
	} catch (...) {
		LOG(LERROR) << "KS_ROICrop::onNewImage failed\n";
	}

}

void KS_ROICrop::onNewDrawable(){
	LOG(LTRACE) << "KS_ROICrop::onNewDrawable\n";
	try{
		container = in_container.read();
//		std::cout << "Data read " << container.getSize() <<"\n" << std::endl;
		container_ready = true;
		if(img_ready && container_ready)
			onStep();
	}catch(...){
		LOG(LERROR) << "KS_ROICrop::onNewDrawable\n";
	}
}

}//: namespace ROIC
}//: namespace Processors
