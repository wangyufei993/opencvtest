#include "stdafx.h"

#include <opencv2\opencv.hpp>  
#include <opencv2/core/core.hpp>   
#include <iostream>  
#include <cv.h>
#include<opencv2/highgui/highgui.hpp>
#include"opencv2/imgproc/imgproc.hpp"
#include <string>  
using namespace cv;
using namespace std;

#define cvQueryHistValue_2D( hist, idx0, idx1 )   cvGetReal2D( (hist)->bins, (idx0), (idx1) )
#define cvQueryHistValue_1D( hist, idx0 ) \
	((float)cvGetReal1D( (hist)->bins, (idx0)))

//实验一：显示图片

/*int main()
{
Mat img = imread("E:\\1.jpg");
if (img.empty())
{
cout << "error";
return -1;
}
imshow("ceshi", img);
waitKey();
return 0;
}*/

//实验二：显示图片轮廓
/*int main()
{
Mat M = imread("E:\\1.jpg");
cvtColor(M,M,CV_BGR2GRAY);
Mat contours;
Canny(M,contours,125,350);
threshold(contours,contours,128,155,THRESH_BINARY);
namedWindow("lunkuo");
imshow("lunkuo", contours);
waitKey();
return 0;
return 0;
}*/
//实验三，直线检测
/* void drawDetectLines(Mat& image,const vector<Vec4i>& lines,Scalar & color)  
{  
// 将检测到的直线在图上画出来  
vector<Vec4i>::const_iterator it=lines.begin();  
while(it!=lines.end())  
{  
Point pt1((*it)[0],(*it)[1]);  
Point pt2((*it)[2],(*it)[3]);  
line(image,pt1,pt2,color,2); //  线条宽度设置为2  
++it;  
}  
} 
int main()
{  
Mat image=imread("E:\\3.jpg");  
Mat I;  
cvtColor(image,I,CV_BGR2GRAY);  

Mat contours;  
Canny(I,contours,125,350);  
threshold(contours,contours,128,255,THRESH_BINARY);  

vector<Vec4i> lines;  
// 检测直线，最小投票为90，线条不短于50，间隙不小于10  
HoughLinesP(contours,lines,1,CV_PI/180,80,50,10);  
drawDetectLines(image,lines,Scalar(0,255,0));  

namedWindow("zhixian");  
imshow("zhixian",image);  
waitKey();  
return 0;  
}  */



//实验四：比较两张图片的相似度（灰度图）
int HistogramBins = 256;  
float HistogramRange1[2]={0,255};  
float *HistogramRange[1]={&HistogramRange1[0]};  
int CompareHist()  
{  
	int size = 256;
	int scale = 2;
	int height = 256;
	IplImage * image1=cvLoadImage("E:\\1.jpg",0);  
	IplImage * image2=cvLoadImage("E:\\1.jpg",0); 

	//cvCvtColor(image1, image1,CV_RGB2GRAY);
	//cvCvtColor(image2,image2,CV_RGB2GRAY);


	CvHistogram *Histogram1 = cvCreateHist(1, &HistogramBins, CV_HIST_ARRAY,HistogramRange);  
	CvHistogram *Histogram2 = cvCreateHist(1, &HistogramBins, CV_HIST_ARRAY,HistogramRange);  

	cvCalcHist(&image1, Histogram1);  
	cvCalcHist(&image2, Histogram2);  

	cvNormalizeHist(Histogram1, 1);  
	cvNormalizeHist(Histogram2, 1);  
	IplImage* hist_img= cvCreateImage(cvSize(size* scale, height), 8, 3);
	//图像置零
	cvZero(hist_img);
	//计算直方图的最大方块值,初始化为0
	float max_value= 0;
	cvGetMinMaxHistValue(Histogram1, 0, &max_value, 0, 0);
	//绘制直方图
	for(int i=0; i<size; i++)
	{
		float bin_val= cvQueryHistValue_1D(Histogram1,i);   //像素i的概率
		int intensity = cvRound(bin_val* height/ max_value);  // 绘制的高度
		cvRectangle(hist_img,
			cvPoint(i* scale, height- 1),
			cvPoint((i+1)* scale- 1, height- intensity),
			CV_RGB(255, 255, 255));
	}

	// CV_COMP_CHISQR,CV_COMP_BHATTACHARYYA这两种都可以用来做直方图的比较，值越小，说明图形越相似  
	printf("CV_COMP_CHISQR : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_CHISQR));  
	printf("CV_COMP_BHATTACHARYYA : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_BHATTACHARYYA));  


	// CV_COMP_CORREL, CV_COMP_INTERSECT这两种直方图的比较，值越大，说明图形越相似  
	printf("CV_COMP_CORREL : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_CORREL));  
	printf("CV_COMP_INTERSECT : %.4f\n", cvCompareHist(Histogram1, Histogram2, CV_COMP_INTERSECT));  

	cvShowImage("tupian1",image1);
	cvShowImage("tupian2",image2);
	cvShowImage("zhifangtu",hist_img);
	cvWaitKey();
	cvReleaseImage(&image1);  
	cvReleaseImage(&image2);  
	cvReleaseHist(&Histogram1);  
	cvReleaseHist(&Histogram2);  
	return 0;  
}  
int main(int argc, char** argv)  
{  
	CompareHist();  
	return 0;  
}