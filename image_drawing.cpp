#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

bool bClick = false;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)		// Lecture 3-5
{
	if (event == EVENT_LBUTTONDOWN)
	{
		printf("LBUTTONDOWN down %d, %d \n", x, y);
		bClick = true;
	}
	else if (event == EVENT_LBUTTONUP)
	{
		printf("LBUTTONUP up %d, %d \n", x, y);
		bClick = false;
	}
	else if (event == EVENT_RBUTTONDOWN)
	{
		printf("RBUTTONDOWN down %d, %d \n", x, y);
		(*(Mat*)userdata).setTo(255);
	}
	else if (event == EVENT_MBUTTONDOWN)
	{
		printf("MBUTTONDOWN down %d, %d \n", x, y);
	}
	else if (event == EVENT_MOUSEMOVE)
	{
		printf("MOUSEMOVE %d, %d \n", x, y);

		if (bClick)	
			circle((*(Mat*)userdata), Point(x, y), 2, CV_RGB(255, 0, 0), 2);
	}

	//imshow("img", (*(Mat*)userdata));
}

int main(int, char)
{
	namedWindow("img", 0);
	
	Mat img(Size(500, 500), CV_8UC3);
	img.setTo(255);
	
	setMouseCallback("img", CallBackFunc, &img);
	
	while (1)
	{
		imshow("img", img);
		if (waitKey(1) > 0)
			break;
	}
	
	destroyAllWindows();

	return 0;
}
