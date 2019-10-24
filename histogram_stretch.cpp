
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

Mat getHistoImage(Mat inImg)
{
 	//variables preparing 
 	/////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
 	int hbins = 255; //histogram x axis size, that is histSize,  
 					//ex) 2 -> 0~128, 129~256, ex)16 -> 0 ~ 15, 16 ~ 31...,  
 	int channels[] = { 0 }; //index of channel 
 	int histSize[] = { hbins };
 	float hranges[] = { 0, 255 };
 	const float* ranges[] = { hranges };

	MatND Hist;
	MatND nomHist;
 	//cal histogram & normalization 
 	/////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
 	calcHist(&inImg, 1, channels, Mat(), //MaskForHisto, // // do use mask 
 		Hist, 1, histSize, ranges,
 		true, // the histogram is uniform 
 		false);
 	normalize(Hist, Hist, 0, 255, CV_MINMAX);

 	// Draw the histograms for B, G and R 
 	int hist_w = 500; int hist_h = 255;
 	int ratio = cvRound((double)hist_w / hbins);
 	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

 	int x1, y1;
 	int x2, y2;
 	for (int i = 1; i < hbins; i++)
 	{
 		x1 = ratio * (i - 1);
 		y1 = hist_h - cvRound(Hist.at<float>(i - 1));

 		x2 = ratio * (i);
 		y2 = hist_h - cvRound(Hist.at<float>(i));

 		line(histImage, Point(x1, y1), Point(x2, y2),
 			Scalar(255, 255, 255), 2, 8, 0);
 	}

 	return histImage;
}


int main(int, char)
{
	Mat imgA, grayImg;
	imgA = imread("E:\\999_Work\\hill.jpg");

	cvtColor(imgA, grayImg, CV_BGR2GRAY);
	imshow("grayImg", grayImg);

	Mat histImage = getHistoImage(grayImg);

	Mat grayImg_stretch;
	normalize(grayImg, grayImg_stretch, 0, 255, CV_MINMAX);
	Mat histStretchImg = getHistoImage(grayImg_stretch);
	imshow("grayImg_stretch", grayImg_stretch);

	namedWindow("calcHist Demo", 0);
	imshow("calcHist Demo", histImage);
	namedWindow("histStretchImg Demo", 0);
	imshow("histStretchImg Demo", histStretchImg);
	
	waitKey(0);
	
	return 0;
}

