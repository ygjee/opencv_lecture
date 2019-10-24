
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

int main(int, char)
{
	Mat im_in = imread("E:\\999_Work\\nickel.jpg", IMREAD_GRAYSCALE);

	Mat im_th, im_result;
	threshold(im_in, im_th, 220, 255, THRESH_BINARY_INV);

	Mat im_floodfill = im_th.clone();
	floodFill(im_floodfill, Point(0, 0), Scalar(255));

	Mat im_floodfill_inv;
	bitwise_not(im_floodfill, im_floodfill_inv);

	Mat im_out;// = (im_th | im_floodfill_inv);

	bitwise_or(im_th, im_floodfill_inv, im_out);

	hconcat(im_in, im_th, im_result);
	hconcat(im_result, im_floodfill, im_result);
	hconcat(im_result, im_floodfill_inv, im_result);
	hconcat(im_result, im_out, im_result);

	namedWindow("img", 0);
	imshow("img", im_result);

	waitKey(0);
	
	return 0;
}

