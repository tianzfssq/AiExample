/*
 ʹ�����̸���ѡ�羰ͼ�񣬷ֱ�ʹ��SIFT��FAST��ORB���Ӽ��ǵ㣬���ȽϷ����������
(��ѡ)ʹ��Harris�ǵ������Ӽ�����̸񣬲�����������Ƚϡ�
*/

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// ��ֵ
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

	// thre:��ֵ,��Բ�ϵ� n �����������ص�����ֵ�ֱ��� p ������ֵ�������Щ��ֵ�ľ���ֵ���� Ip+thre ��򶼱� Ip-thre С�������� p Ϊ�ǵ�
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
	//Ptr <Feature2D> sift = SIFT::create��1600��; //���Ų���Խ��Խ��ȷ���Զ�

	//vector <KeyPoint> keypointsa��kp2;

	//Mat a��b;
	//sift->detectAndCompute(); //�õ������������������
	//sift->detectAndCompute();
	//drawKeypoints(src, keypointsa, src); //����������

	//drawKeypoints(src2, kp2, src2);
}
