#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)		// Lecture 3-5
{
	if (event == EVENT_LBUTTONDOWN)
	{
		printf("LBUTTONDOWN down %d, %d \n", x, y);
		circle((*(Mat*)userdata), Point(x, y), 10, CV_RGB(255, 0, 0), 3);
	}
	else if (event == EVENT_RBUTTONDOWN)
	{
		printf("RBUTTONDOWN down %d, %d \n", x, y);
	}
	else if (event == EVENT_MBUTTONDOWN)
	{
		printf("MBUTTONDOWN down %d, %d \n", x, y);
	}
	else if (event == EVENT_MOUSEMOVE)
	{
		printf("MOUSEMOVE %d, %d \n", x, y);
	}

	//imshow("img", (*(Mat*)userdata));
}

int main(int, char)
{
	namedWindow("img", 0);

	Mat img = imread("E:\\999_Work\\up.jpg");

	setMouseCallback("img", CallBackFunc, &img);

	while (1)
	{
		imshow("img", img);
		if (waitKey(10) > 0)
			break;
	}

	destroyAllWindows();

	return 0;
}
