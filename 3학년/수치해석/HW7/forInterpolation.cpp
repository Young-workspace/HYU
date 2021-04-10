#ifdef _DEBUG
#pragma comment (lib, "opencv_world331d.lib")
#else
#pragma comment (lib, "opencv_world331.lib")
#endif

//file I/O and resize with interpolation
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


//보간하는 부분 변경 가능
void BilinearInterpolation(cv::Mat &src, cv::Mat &dst, double rate);
cv::Mat bi_dst;

int main()
{
	cv::Mat src;
	src = cv::imread("test.jpg", 1);  //절대 경로 혹은 상대 경로(0은 gray scale)
	if (src.empty())
	{
		std::cout << "Cannot find an image" << std::endl;
		return -1;
	}
	cv::imshow("SourceImage", src);
	cv::waitKey(0);

	//이미지를 2배 키웠을 때의 Bilinear interpolation
	int height = src.rows;
	int width = src.cols;
	double scale_rate = 0.5;
	bi_dst = cv::Mat(height*scale_rate, width*scale_rate, src.type(), cv::Scalar(0)); //결과물을 담을 Mat

	//bilinearInterpolation
	BilinearInterpolation(src, bi_dst, scale_rate);
	cv::imshow("BIImage", bi_dst);
	cv::waitKey(0);
	
	return 0;
}

void BilinearInterpolation(cv::Mat &src, cv::Mat &dst, double rate)
{
	/////////////////////////////////////////////////
	////bilinear interpolation
	cv::Vec3b p1, p2, p3, p4;
	//cv::resize(src, dst, cv::Size(src.cols * rate, src.rows * rate));
	for (int y = 0; y < dst.rows; y++)
	{
		for (int x = 0; x < dst.cols; x++)
		{
			int px = (int)(x / rate);			// 그림의 x 축
			int py = (int)(y / rate);			// 그림의 y축

			double fx1 = (double)x / (double)rate - (double)px;
			double fx2 = 1 - fx1;
			double fy1 = (double)y / (double)rate - (double)py;
			double fy2 = 1 - fy1;

			if(px <= src.cols && py <=src.rows) p1 = src.at<cv::Vec3b>(py, px);
			if (px + 1 < src.cols && py <= src.rows) p3 = src.at<cv::Vec3b>(py, px + 1);
			if (px <= src.cols && py + 1 < src.rows) p2 = src.at<cv::Vec3b>(py + 1, px);
			if (px+1 < src.cols && py+1 < src.rows) p4 = src.at<cv::Vec3b>(py + 1, px + 1);

			double w1 = fx2 * fy2;
			double w2 = fx1 * fy2;
			double w3 = fx2 * fy1;
			double w4 = fx1 * fy1;

			dst.at<cv::Vec3b>(y, x) = w1 * p1 + w2 * p2 + w3 * p3 + w4 * p4;
		}
	}
	///////////////////////////////////////////////
}