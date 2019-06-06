#pragma once
#include <vector>
#include <opencv2/opencv.hpp>

class featureMatcher{
private:
	std::vector<cv::DMatch> matches;

public:
	void match(const cv::Mat& descriptors1, const cv::Mat& descriptors2);
	cv::Mat draw(const cv::Mat& actframe, 
			const std::vector<cv::KeyPoint>& keypoints1, 
			const cv::Mat& prevFrame,
			const std::vector<cv::KeyPoint>& keypoints2);
 
};
