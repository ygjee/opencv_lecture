
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat src, src_gray, dst;
const char* window_name = "Threshold Demo";

const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted\n";
const char* trackbar_value = "Value";

void Threshold_Demo(int, void*);

int main(int, char)
{
	src = imread("E:\\999_Work\\수지.jpg");

	cvtColor(src, src_gray, CV_BGR2GRAY);

	namedWindow(window_name, 0);
	resizeWindow(window_name, 500, 500);

	printf("%s", trackbar_type);
	createTrackbar(trackbar_type, window_name, &threshold_type, max_type, Threshold_Demo);

	createTrackbar(trackbar_value, window_name, &threshold_value, max_value, Threshold_Demo);

	Threshold_Demo(0, 0);

	namedWindow("origin", 0);
	imshow("origin", src);

	while (true)
	{
		int c;
		c = waitKey(20);
		if ((char)c == 27)
		{
			break;
		}
	}

	waitKey(0);
	
	return 0;
}

void Threshold_Demo(int, void*)
{
	threshold(src_gray, dst, threshold_value, max_BINARY_value, threshold_type);

	imshow(window_name, dst);
}

