#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>

using namespace std;

using namespace cv;


//----------------大津算法-------------------
void showThreshold(Mat srcImg)
{
	Mat imgThreshold;
	/*
	src：源图像，可以为8位的灰度图，也可以为32位的彩色图像。（两者由区别）
	dst：输出图像
	thresh：阈值
	maxval：dst图像中最大值
	type：阈值类型，可以具体类型如下
	*/
	threshold(srcImg, imgThreshold, 100, 255, CV_THRESH_OTSU);
	imshow(string("imgThreshold"), imgThreshold);
}

// 区域生长
void showFloodFill(Mat srcImg, int iDiff = 100)
{
	Mat imgFloodFill;
	/*
	image    【输入/输出】 1或者3通道、 8bit或者浮点图像。仅当参数flags的FLOODFILL_MASK_ONLY标志位被设置时image不会被修改，否则会被修改。
	mask     【输入/输出】 操作掩码，必须为单通道、8bit，且比image宽2个像素、高2个像素。使用前必须先初始化。
	          Flood-filling无法跨越mask中的非0像素。例如，一个边缘检测的结果可以作为mask来阻止边缘填充。
			  在输出中，mask中与image中填充像素对应的像素点被设置为1，或者flags标志位中设置的值(详见flags标志位的解释)。
			  此外，该函数还用1填充了mask的边缘来简化内部处理。因此，可以在多个调用中使用同一mask，以确保填充区域不会重叠。
	seedPoint 起始像素点
	newVal    重绘像素区域的新的填充值(颜色)
	rect      可选输出参数，返回重绘区域的最小绑定矩形。
	loDiff    当前选定像素与其连通区中相邻像素中的一个像素，或者与加入该连通区的一个seedPoint像素，二者之间的最大下行差异值。
	upDiff    当前选定像素与其连通区中相邻像素中的一个像素，或者与加入该连通区的一个seedPoint像素，二者之间的最大上行差异值。
	flags     flags标志位是一个32bit的int类型数据，其由3部分组成： 0-7bit表示邻接性(4邻接、8邻接)；8-15bit表示mask的填充颜色；16-31bit表示填充模式（详见填充模式解释）
	*/
	
	Rect ccomp;
	//floodFill(srcImg, Point(10, 10), Scalar(92, 2, 79), 
	//		  &ccomp, Scalar(iDiff, iDiff, iDiff), Scalar(iDiff, iDiff, iDiff), 8);

	floodFill(srcImg, Point(10, 10), Scalar(92, 2, 79));

	imshow(string("imgFloodFill"), srcImg);
}

void showImage(const String& filename)
{
	//读取本地的一张图片便显示出来
	Mat img = imread(filename);
	imshow("Source Image", img);

	Mat gray;
	cvtColor(img, gray, CV_BGR2GRAY);

	showThreshold(gray);
	//showFloodFill(gray);
}

// 显示直方图
// 
void showHist(Mat srcImg)
{
	IplImage* image = new IplImage(srcImg);
	int arr_size = 255;					//定义一个变量用于表示直方图行宽
	float hranges_arr[] = { 0, 255 };		//图像方块范围数组
	float *phranges_arr = hranges_arr;		//cvCreateHist参数是一个二级指针，所以要用指针指向数组然后传参

	// 创建一个一维的直方图，行宽为255，多维密集数组，方块范围为0-255，bin均化
	// 参数1：直方图的维数
	// 参数2：直方图维数尺寸的组数
	CvHistogram *hist = cvCreateHist(1, &arr_size, CV_HIST_ARRAY, &phranges_arr, 1);

	//创建一个空白图像用于绘制直方图
	IplImage *histimg = cvCreateImage(cvSize(320, 255), 8, 3);
	cvZero(histimg);//清空histimag-imagedata数据
	//计算图像直方图大小
	cvCalcHist(&image, hist, 0, 0);
	//直方图根据size分组然后根据ranges取值范围来统计图像像素点范围，
	//也就是说ranges为0-255则将图像中像素值叠加在一起(叠加成MIN：0、MIX：255)
	//并分组到对应的size维中，所以size维里的每个元素非常大，所以要按比例缩小
	float max_val;	//用于存储获取到的最大值
	cvGetMinMaxHistValue(hist, 0, &max_val, 0, 0);		//获取直方图最大值
	cout << "max_val:" << max_val << endl;


	//@param src Source array
	//@param dst Destination array
	//@param scale Scale factor
	//@param shift Value added to the scaled source array elements
	double scale = max_val ? 255. / max_val : 0.;
	cvConvertScale(hist->bins, hist->bins, scale, 0);	//按比例缩小直方图
	cout << "scale:" << scale << endl;

	//开始绘制直方图
	int bin_w;
	bin_w = histimg->width / arr_size;//得到开始绘制点位置

	for (int i = 0; i < arr_size; i++)
	{
		double val = (cvGetReal1D(hist->bins, i)*histimg->height / 255); //获取矩阵元素值，并转换为对应高度
		CvScalar color = CV_RGB(255, 255, 0); 

		cvRectangle( histimg, cvPoint(i*bin_w, histimg->height),
				     cvPoint((i + 1)*bin_w, 
			         (int)(histimg->height - val)),
			         color, 1, 8, 0 );
	}
	//显示结果
	imshow("grayimg", srcImg);		//绘制出来的直方图
	cvShowImage("histimg", histimg);		//绘制出来的直方图
	waitKey(0);
}

int main()
{
	Mat img = imread("../Pics/lena.png");
	imshow("Source Image", img);

	Mat gray;
	cvtColor(img, gray, CV_BGR2GRAY);

	showHist(gray);
	//showThreshold(gray);
	//showFloodFill(img);

	waitKey(0);
	return 0;
}