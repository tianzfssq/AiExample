/*

��LenaΪԭʼͼ��ͨ��OpenCVʵ��ƽ���˲�����˹�˲�����ֵ�˲����Ƚ��˲������

*/

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

int main()
{
	Mat img = imread("../Pics/Lena.png");
	
	blurTest(img);

	return 0;
}