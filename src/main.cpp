#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <utility>
#include "../headers/processing.hpp"
#include "../headers/featureExtractor.hpp"
#include "../headers/arguments.hpp"


int main(int argc, char** argv){
	// Supported algorithms for feature detection
	enum Algorithm{
		ORB  = 0, // Oriented FAST and Rotated BRIEF
		GFFT = 1  // Good Features To Track 
	};

	std::string data = "";
	Algorithm alg = ORB; // Default algorithm is ORB
	if(argc >= 2){
		for( std::size_t i = 1; i < argc; ++i){
			std::string arg = argv[i];
			if(arg == "h" || arg == "--help"){ std::cout << 1; logUsage(); return 0; }
			if(arg == "GFTT"){ std::cout << 2; alg = GFFT; }
			else data = arg;
		}	
	}

	logInfo();
	cv::VideoCapture cap(0, CV_WINDOW_NORMAL); // Get the Webcam video capture
	std::cout << data << std::endl;
	if(data != ""){
		cap.open(data, CV_WINDOW_NORMAL);
		if(!cap.isOpened()) throw std::invalid_argument("Could not open " + data);
	} 
		
	cv::Mat frame; // OpenCV image type
	imageHandler image; // src/imageHandler.cpp class
	featureExtractor detector; // src/featureDetector.cpp class
	cv::Mat gray;

	while (cap.isOpened()){ cap >> frame;
		cv::resize(frame, frame, cv::Size(frame.size[1]*0.5, frame.size[0]*0.5)); // Downscaling the image by half.
		cv::cvtColor(frame, gray, CV_RGB2GRAY);

		if(alg == ORB){
			std::pair<cv::Mat, std::vector<cv::KeyPoint>> result =  detector.ORB_alg(gray);
			frame = detector.drawKeyPoints(frame, result.second);
		}
		if(alg == GFFT){
			std::vector<cv::Point2f> result = detector.GFTT_alg(frame);
			std::vector<cv::KeyPoint> keypoints = detector.mat2KeyPoints(result);
			frame = detector.drawKeyPoints(frame, keypoints);
		}
		image.draw(frame);
		if(cv::waitKey(30) >= 0) break;
		if(frame.empty()) break;
	}

	return 0;
}
