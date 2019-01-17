/*
��������
�����ܹ���4����ҵ��һ����չ��ҵ��
1. ��LenaΪԭʼͼ��ͨ��OpenCVʵ��ƽ���˲�����˹�˲�����ֵ�˲����Ƚ��˲������
2. ��LenaΪԭʼͼ��ͨ��OpenCVʹ��Sobel��Canny���Ӽ�⣬�Ƚϱ�Ե�������
3. ��OpenCV��װĿ¼���ҵ��γ̶�Ӧ��ʾͼƬ(��װĿ¼\sources\samples\data)�����ȼ���Ҷ�ֱ��ͼ����һ��ʹ�ô���㷨���зָ���ȽϷ����ָ�����
4. ʹ������ͼ�񣬷ָ�õ������������ȼ��������(����)����������ȵ���Ϣ����һ��������������ȵľ�ֵ�������������3sigma��Χ��������������

��չ��ҵ��
5. ʹ�����̸���ѡ�羰ͼ�񣬷ֱ�ʹ��SIFT��FAST��ORB���Ӽ��ǵ㣬���ȽϷ����������
(��ѡ)ʹ��Harris�ǵ������Ӽ�����̸񣬲�����������Ƚϡ�

������ʾ
1. �ο�CSDN������¡�
2. �ǵ�������Feature2D�ࡣ

*/

// D:\ThirdParty\opencv\build\include
// D:\ThirdParty\opencv\build\x64\vc15\lib
// opencv_world344d.lib


#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void blurTest(Mat img)
{
	imshow("ԭͼ", img);

	// ��ֵ�˲�
	Mat imageBlur;
	blur(img, imageBlur, Size(5,5));
	imshow("��ֵ�˲�", imageBlur);


	// ��˹�˲�
	Mat imageGauss;
	/*
	������������Size���͵�ksize��˹�ں˵Ĵ�С������ksize.width��ksize.height���Բ�ͬ�������Ƕ�����Ϊ���������������ߣ����ǿ�������ģ����Ƕ�����sigma���������
	���ĸ�������double���͵�sigmaX����ʾ��˹�˺�����X����ĵı�׼ƫ�
	�����������double���͵�sigmaY����ʾ��˹�˺�����Y����ĵı�׼ƫ���sigmaYΪ�㣬�ͽ�����ΪsigmaX�����sigmaX��sigmaY����0����ô����ksize.width��ksize.height���������
	Ϊ�˽������ȷ�����룬����ǰѵ���������Size�����ĸ�����sigmaX�͵��������sigmaYȫ��ָ������
	������������int���͵�borderType�������ƶ�ͼ���ⲿ���ص�ĳ�ֱ߽�ģʽ��ע������Ĭ��ֵBORDER_DEFAULT��
	*/
	GaussianBlur(img, imageGauss, Size(5, 5), 0);
	imshow("��˹�˲�", imageBlur);

	// ��ֵ�˲�
	Mat imageMedian;
	medianBlur(img, imageMedian, 5);
	imshow("��ֵ�˲�", imageBlur);

	waitKey(0);
}

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
	Mat img = imread("./Lena.png");
	
	//blurTest(img);
	//testSobel(img, 1);
	testCanny(img, 1);

	return 0;
}