#include "stdafx.h"

#include <opencv2\opencv.hpp>  
#include <opencv2/core/core.hpp>   
#include <iostream>  
#include<opencv2/highgui/highgui.hpp>
#include"opencv2/imgproc/imgproc.hpp"
#include <string>  
using namespace cv;
using namespace std;
int main()
{
	//实验一：显示图片
    /*Mat img = imread("E:\\1.jpg");
    if (img.empty())
    {
        cout << "error";
        return -1;
    }
    imshow("ceshi", img);
    waitKey();
	return 0;*/

	//实验二：显示图片轮廓
	Mat M = imread("E:\\1.jpg");
	cvtColor(M,M,CV_BGR2GRAY);
	Mat contours;
	Canny(M,contours,125,350);
	threshold(contours,contours,128,155,THRESH_BINARY);
	namedWindow("lunkuo");
	imshow("lunkuo", contours);
	waitKey();
	return 0;
} 