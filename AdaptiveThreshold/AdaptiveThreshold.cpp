#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;


int main()
{
	//读取本地的一张图片便显示出来
	Mat img = imread("../Pics/3.png");
	imshow("Src Image", img);

	Mat imgGray;
	cvtColor(img, imgGray, COLOR_BGR2GRAY);

	Mat destImage;
	// [0] 滤波
	GaussianBlur(imgGray, destImage, Size(5, 5), 0);//高斯滤波去除小噪点
	
	//Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	//cout << "element = " << endl << " " << element << endl << endl;
	//morphologyEx(imgGray, destImage, MORPH_OPEN, element);
	//morphologyEx(destImage, destImage, MORPH_CLOSE, element);
	//imshow("adaptiveThreshold", destImage);

	// [1] 自适应阈值二值化
	Mat bw;
	adaptiveThreshold(destImage, bw, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 7, 2);

	imshow("adaptiveThreshold", bw);
	//等待用户按键
	waitKey(0);

	return 0;
}