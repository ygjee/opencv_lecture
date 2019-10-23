
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

int main(int, char)
{
	namedWindow("img", 0);

	Mat img = imread("E:\\999_Work\\otsu1.jpg");

	Mat gray, binary, binary_th, binary_ad, img_result;
	cvtColor(img, gray, CV_RGB2GRAY);

	threshold(gray, binary_th, 128, 255, CV_THRESH_BINARY);
	adaptiveThreshold(gray, binary_ad, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 9, 5);
	GaussianBlur(gray, gray, Size(7, 7), 0);
	threshold(gray, binary, 0, 255, CV_THRESH_BINARY + THRESH_OTSU);

	hconcat(gray, binary, img_result);
	hconcat(img_result, binary_th, img_result);
	hconcat(img_result, binary_ad, img_result);

	imshow("img", img_result);

	waitKey(0);
	
	return 0;
}

