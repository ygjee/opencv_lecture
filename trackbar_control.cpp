#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

int g_slider;
int g_slider_max;

void on_trackbar(int, void*)
{
	if (g_slider % 2 == 0)
		g_slider += 1;

	printf("%d\n", g_slider);
}

int main(int, char)
{
	Mat edges;
	VideoCapture cap = VideoCapture(0);

	if (!cap.isOpened()) return -1;

	g_slider = 0;
	g_slider_max = 255;

	namedWindow("edges", 1);

	createTrackbar("TrackbarName", "edges", &g_slider, g_slider_max, on_trackbar);

	for (;;)
	{
		Mat frame;
		cap >> frame;
		cvtColor(frame, edges, CV_BGR2GRAY);
		GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		Canny(edges, edges, g_slider, 30, 3);
		imshow("edges", edges);
		if (waitKey(30) >= 0)
			break;
	}

	return 0;
}
