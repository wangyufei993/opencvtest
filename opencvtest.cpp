#include "stdafx.h"

#include <opencv2\opencv.hpp>  
#include <opencv2/core/core.hpp>   
#include <iostream>  
#include<opencv2/highgui/highgui.hpp>
#include"opencv2/imgproc/imgproc.hpp"
#include <string>  
using namespace cv;
using namespace std;

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
 void drawDetectLines(Mat& image,const vector<Vec4i>& lines,Scalar & color)  
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
}  
