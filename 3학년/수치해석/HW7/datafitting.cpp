#ifdef _DEBUG
#pragma comment (lib, "opencv_world331d.lib")
#else
#pragma comment (lib, "opencv_world331.lib")
#endif

#include <iostream>
#include <opencv2/core.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"


using namespace cv;
using namespace std;

Mat AddGaussianNoise(Mat &src);
Mat MaskedNoise(Mat &src);
void MatchedKeyPoint(Mat &src1, Mat &src2);

//global variable
int distThresh = 30;
vector<Point2f> Left;
vector<Point2f> Right;


int main()
{
	Mat LeftImg = imread("badleft.jpg");
	Mat RightImg = imread("badright.jpg");

	//image가 너무 클 경우 사이즈 조정
	//resize(LeftImg, LeftImg, Size(), 0.25, 0.25, INTER_LINEAR);
	//resize(RightImg, RightImg, Size(), 0.25, 0.25, INTER_LINEAR);

	//0. normal case
	
	//1.Add Gaussian noise
	RightImg = AddGaussianNoise(RightImg);

	//2. Add Gaussian noise + addtional noise;
	//RightImg = MaskedNoise(RightImg);

	//Extract features and matching correspondence
	MatchedKeyPoint(LeftImg, RightImg);					// 왼쪽 그림과 오른쪽 그림의 매치되는 개수를 확인
	cout << Left.size() << endl;					//매치되는 개수?
	cout << Right.size() << endl;

	return 0;
}



Mat AddGaussianNoise(Mat &src)
{
	Mat noise_src(src.size(), src.type());
	// average  와 std 로 gaussian noise 조절 가능
	double average = 0.0;
	double std = 50.0;					// 커질수록 noise가 추가 됨
	randn(noise_src, Scalar::all(average), Scalar::all(std));

	Mat tmp_img;
	src.convertTo(tmp_img, src.type());
	addWeighted(tmp_img, 1.0, noise_src, 1.0, 0.0, tmp_img);    // tmp_img = 1.0 * tmp_img, 1.0 * noise_src

	imshow("tmp", tmp_img);
	waitKey(0);

	return tmp_img;
}

Mat MaskedNoise(Mat &src)
{
	Mat noised_mask = imread("D:/학교/3학년 2학기/수치해석(박종일)/과제/과제8/과제8/masking1.jpg");
	resize(noised_mask, noised_mask, Size(src.cols, src.rows));
	
	Mat mask1 = Mat::zeros(src.rows, src.cols, CV_32F);				
	Mat mask2 = Mat::zeros(src.rows, src.cols, CV_32F);
	rectangle(mask1, Rect(0, 0, src.cols, src.rows), Scalar(0.8f), FILLED);				// mask가 0.8 값을 가지도록
	rectangle(mask2, Rect(0, 0, src.cols, src.rows), Scalar(0.2f), FILLED);
	Mat result = Mat(src.rows, src.cols, CV_8UC3);
	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++)
		{
			result.at<cv::Vec3b>(y, x) = src.at<cv::Vec3b>(y, x) * mask1.at<float>(y, x) 
				+ noised_mask.at<cv::Vec3b>(y, x) * mask2.at<float>(y, x);
		}
	}
	
	//gaussian noise 추가
	Mat noise_src(result.size(), result.type());
	double average = 0.0;
	double std = 50.0;
	randn(noise_src, Scalar::all(average), Scalar::all(std));

	Mat tmp_img;
	result.convertTo(tmp_img, result.type());
	addWeighted(tmp_img, 1.0, noise_src, 1.0, 0.0, tmp_img);

	return tmp_img;
}


void MatchedKeyPoint(Mat &src1, Mat &src2)
{
	Ptr<Feature2D> featureExtractor;
	featureExtractor = ORB::create();
	vector<KeyPoint> LeftKeypoints, RightKeypoints;
	Mat LeftDescriptors, RightDescriptors;
	Mat matchingImage;
	featureExtractor->detectAndCompute(src1, Mat(), LeftKeypoints, LeftDescriptors);
	featureExtractor->detectAndCompute(src2, Mat(), RightKeypoints, RightDescriptors);

	Ptr<DescriptorMatcher> matcher;
	vector<vector<DMatch>> knnMatches;
	vector<DMatch> matches;

	matcher = DescriptorMatcher::create("BruteForce-Hamming");
	matcher->match(LeftDescriptors, RightDescriptors, matches);
	vector<DMatch>::iterator it = matches.begin();
	for (; it != matches.end(); )
	{
		if (it->distance > distThresh)
		{
			it = matches.erase(it);
		}
		else
		{
			it++;
		}
	}
	cout << matches.size() << endl;                               
	//cout << LeftKeypoints[matches[0].queryIdx].pt << endl;
	//cout << RightKeypoints[matches[0].trainIdx].pt << endl;
	drawMatches(src1, LeftKeypoints, src2, RightKeypoints, matches, matchingImage);


	imshow("matches", matchingImage);
	waitKey(0);

	for (int i = 0; i < matches.size(); i++)
	{
		//Left이 src1의 point들, Right이 src2의 point들
		Left.push_back(LeftKeypoints[matches[i].queryIdx].pt);
		Right.push_back(RightKeypoints[matches[i].trainIdx].pt);
	}

}