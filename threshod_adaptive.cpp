
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

int main(int, char)
{
	namedWindow("img", 0);

	Mat img = imread("E:\\999_Work\\adaptive.png");

	Mat gray, binary, binary1, binary2, img_result;
	cvtColor(img, gray, CV_BGR2GRAY);

	threshold(gray, binary, 128, 255, CV_THRESH_BINARY);
	adaptiveThreshold(gray, binary1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, 5);
	adaptiveThreshold(gray, binary2, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 15, 5);

	hconcat(gray, binary, img_result);
	hconcat(img_result, binary1, img_result);
	hconcat(img_result, binary2, img_result);

	imshow("img", img_result);

	waitKey(0);
	
	return 0;
}

