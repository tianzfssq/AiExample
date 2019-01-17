#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

// D:\ThirdParty\opencv\build\include
// D:\ThirdParty\opencv\build\x64\vc15\lib
// opencv_world344d.lib

Mat g_srcImage, g_dstImage;     //ԭʼͼ��Ч��ͼ
int g_nTrackbarNumer = 0;       //0��ʾ��ʴ��1��ʾ����
int g_nSructElementSize = 3;    //�ṹԪ�أ��ں˾��󣩳ߴ�


void Process();                 //��ʴ�����͵Ĵ�����
void on_TrackbarNumChange(int, void *); //�ص�����
void on_ElementSizeChange(int, void *); //�ص�����

int main()
{
	system("color 5E");

	//����ԭͼ
	g_srcImage = imread("../Pics/Lena.png");
	if (!g_srcImage.data)
	{
		printf("��ȡsrcImage����~!\n");
		return false;
	}

	//��ʾԭͼ
	namedWindow("��ԭʼͼ��");
	imshow("��ԭʼͼ��", g_srcImage);

	//���и�ʴ�����Ͳ�������ʾЧ��ͼ
	namedWindow("��Ч��ͼ��");

	//��ȡ�Զ����
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nSructElementSize + 1, 2 * g_nSructElementSize + 1), Point(g_nSructElementSize, g_nSructElementSize));
	erode(g_srcImage, g_dstImage, element);
	imshow("��Ч��ͼ��", g_dstImage);

	//�����켣��
	createTrackbar("��ʴ/����", "��Ч��ͼ��", &g_nTrackbarNumer, 1, on_TrackbarNumChange);
	createTrackbar("�ں˳ߴ�", "��Ч��ͼ��", &g_nSructElementSize, 21, on_ElementSizeChange);

	//����q�˳�
	while (char(waitKey(1)) != 'q') {}
	return 0;
}

//  �����������Զ���ĸ�ʴ�����Ͳ���
void Process()
{
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nSructElementSize + 1, 2 * g_nSructElementSize + 1), Point(g_nSructElementSize, g_nSructElementSize));

	if (g_nTrackbarNumer == 0)
	{
		erode(g_srcImage, g_dstImage, element);
	}
	else
	{
		dilate(g_srcImage, g_dstImage, element);
	}

	//��ʾЧ��ͼ
	imshow("��Ч��ͼ��", g_dstImage);
}

//  ��������ʴ������֮���л����ػص�����
void on_TrackbarNumChange(int, void *)
{
	Process();
}


//  ��������ʴ�������ں˸ı�ص�����
void on_ElementSizeChange(int, void *)
{
	Process();
}