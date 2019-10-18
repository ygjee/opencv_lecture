
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

int main(int, char)
{
	Mat img = imread("E:\\999_Work\\수지.jpg");
	Mat img_mask = Mat(img.rows, img.cols, img.type());
	Mat img_result;

	img_mask.setTo(0);
	circle(img_mask, Point(img.rows / 2, img.cols / 3), 70, CV_RGB(255, 255, 255), CV_FILLED);

	Mat res;
	bitwise_and(img, img_mask, res);	hconcat(img, res, img_result);
	bitwise_or(img, img_mask, res);		hconcat(img_result, res, img_result);
	bitwise_xor(img, img_mask, res);	hconcat(img_result, res, img_result);
	bitwise_not(img, res);				hconcat(img_result, res, img_result);

	imshow("img", img_result);

	waitKey(0);

	return 0;
}

