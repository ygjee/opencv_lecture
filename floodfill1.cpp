
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

int click_x = 0, click_y = 0;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		printf("ILBUTTONDOWN down %d, %d \n", x, y);

		click_x = x;
		click_y = y;
	}
}

int main(int, char)
{
	int width = 500;
	int height = 500;
	int count = 10;

	srand(time(0));

	namedWindow("img", 1);

	Mat img = Mat(width, height, CV_8UC1);
	img.setTo(0);

	setMouseCallback("img", CallBackFunc, &img);

	int x, y, w, h;

	for (int i = 0; i < count; ++i)
	{
		x = rand() % width;
		y = rand() % height;
		w = rand() % (x - width);
		h = rand() % (y - height);

		printf("(%d): left:%d top:%d - right:%d bottom:%d (width:%d, height:%d) \n",
			i, x, y, x + w, y + h, w, h);
		rectangle(img, Rect(x, y, w, h), CV_RGB(255, 255, 255), 1);
	}

	while (1)
	{
		if (click_x != 0 && click_y != 0)
		{
			floodFill(img, Point(click_x, click_y), Scalar(255));
			click_x = 0;
			click_y = 0;
		}

		imshow("img", img);

		if (waitKey(10) > 0)
			break;
	}

//	waitKey(0);
	
	return 0;
}

