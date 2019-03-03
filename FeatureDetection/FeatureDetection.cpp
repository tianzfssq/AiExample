/*
 使用棋盘格及自选风景图像，分别使用SIFT、FAST及ORB算子检测角点，并比较分析检测结果。
(可选)使用Harris角点检测算子检测棋盘格，并与上述结果比较。
*/

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 阈值
int thre = 40;
Mat src;

void trackBar(int, void*);

void showFast();

void showSIFT();

int main(int argc, char** argv)
{
	src = imread("../Pics/pattern.png");
	
	namedWindow("Fast", WINDOW_AUTOSIZE);
	createTrackbar("threshould", "Fast", &thre, 255, trackBar);
	showFast();
	cvWaitKey(0);
	return 0;
}

void showFast()
{
	std::vector<KeyPoint> keypoints;
	Mat dst = src.clone();

	// thre:阈值,让圆上的 n 个连续的像素的像素值分别与 p 的像素值做差，若这些差值的绝对值都比 Ip+thre 大或都比 Ip-thre 小，则像素 p 为角点
	Ptr<FastFeatureDetector> detector = FastFeatureDetector::create(thre);
	detector->detect(src, keypoints);

	drawKeypoints(dst, keypoints, dst, Scalar::all(-1), DrawMatchesFlags::DRAW_OVER_OUTIMG);
	imshow("Fast", dst);
}

void trackBar(int, void*)
{
	showFast();
}


void showSIFT()
{
	//SiftFeatureDetector sift;
	//Ptr <Feature2D> sift = SIFT::create（1600）; //括号参数越大越精确，自定

	//vector <KeyPoint> keypointsa，kp2;

	//Mat a，b;
	//sift->detectAndCompute(); //得到特征点和特征点描述
	//sift->detectAndCompute();
	//drawKeypoints(src, keypointsa, src); //画出特征点

	//drawKeypoints(src2, kp2, src2);
}
