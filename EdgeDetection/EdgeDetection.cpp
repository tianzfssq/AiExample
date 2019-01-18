/*

��LenaΪԭʼͼ��ͨ��OpenCVʵ��ƽ���˲�����˹�˲�����ֵ�˲����Ƚ��˲������

*/

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void testSobel(Mat img, int type = 0)
{
	Mat imageGray, imageGauss;

	cvtColor(img, imageGray, COLOR_BGR2GRAY);
	GaussianBlur(imageGray, imageGauss, Size(3, 3), 0);

	if (type == 1)
	{
		img = imageGray;
	}
	else if (type == 2)
	{
		img = imageGauss;
	}
	imshow("ԭͼ", img);

	// Sobel����

	//��3���� X�����ݶ�  
	Mat imageSobel_x, abs_grad_x;
	Sobel(img, imageSobel_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(imageSobel_x, abs_grad_x);
	imshow("��Ч��ͼ�� X����Sobel", abs_grad_x);

	//��4����Y�����ݶ�  
	Mat imageSobel_y, abs_grad_y;
	Sobel(img, imageSobel_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(imageSobel_y, abs_grad_y);
	imshow("��Ч��ͼ��Y����Sobel", abs_grad_y);

	//��5���ϲ��ݶ�(����)  
	Mat imageSobel;
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, imageSobel);
	imshow("��Ч��ͼ�����巽��Sobel", imageSobel);

	// Canny�㷨
	//blur(imageGauss, imageCanny, Size(5, 5));
	//imshow("imageSobel", imageCanny);

	waitKey(0);
}

void testCanny(Mat img, int type = 0)
{
	Mat imageGray, imageGauss;

	cvtColor(img, imageGray, COLOR_BGR2GRAY);
	GaussianBlur(imageGray, imageGauss, Size(3, 3), 0);

	if (type == 1)
	{
		img = imageGray;
	}
	else if (type == 2)
	{
		img = imageGauss;
	}

	imshow("ԭͼ", img);

	// Canny����
	Mat imageCandy;
	Canny(img, imageCandy, 100, 200, 3);
	imshow("Canny����", imageCandy);
	waitKey(0);
}

int main()
{
	Mat img = imread("../Pics/Lena.png");

	testSobel(img, 1);
	testCanny(img, 1);

	return 0;
}