#include <opencv2/opencv.hpp>

#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

using namespace cv;

int main()
{
	Mat image = imread("../Pics/rice.png");
	Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	//大津算法
	Mat bw;
	threshold(gray, bw, 0, 0xff, CV_THRESH_OTSU);
	imshow("threshold", bw);
	//形态学滤波
	Mat element = getStructuringElement(MORPH_CROSS, Size(5, 5));
	morphologyEx(bw, bw, MORPH_OPEN, element);
	imshow("morphologyEx", bw);
	//图像分割
	Mat seg = bw.clone();
	vector<vector<Point>> cnts;
	findContours(seg, cnts, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	double areaAll = 0.;
	double lengthAll = 0.;
	vector<double> areaVec;
	vector<double> lengthVec;

	int count = 0;
	for (int i = cnts.size() - 1; i >=0 ; i--)
	{
		vector<Point> c = cnts[i];

		double area = contourArea(c);
		if (area < 10)
		{
			continue;
		}
		areaAll += area;
		areaVec.push_back(area);
		

		count++; // 统计米粒数
		//cout << "blob " << i << " : " << area << endl;
		Rect rect = boundingRect(c);
		int length = rect.width > rect.height ? rect.width : rect.height;
		lengthAll += length;
		lengthVec.push_back(length);
		//cout << "rect.w : " << rect.width << "    "<< "rect.h : " << rect.height << endl;

		rectangle(image, rect, Scalar(0, 0, 0xff), 1);

		std::string s;
		std::to_string(count);
		putText(image, cv::String(s), Point(rect.x, rect.y), CV_FONT_HERSHEY_PLAIN, 0.5, Scalar(0, 0xff, 0));
	}

	double areaAver = areaAll / count;
	double lenghtAver = lengthAll / count;
	cout << "面积均值： " << areaAver << "   " << " 长度均值: " << lenghtAver << endl;

	double areaVariance = 0.;
	double lenghtVariance = 0.;
	for (int i = 0 ; i < count; i++)
	{
		areaVariance += pow(areaVec[i] - areaAver, 2);
		lenghtVariance += pow(lengthVec[i] - lenghtAver, 2);
	}
	cout << "面积方差： " << areaVariance / count << "   " << " 长度方差: " << lenghtVariance / count << endl;

	imshow("Test_Rice", image);
	waitKey(0);

	return 0;
}
