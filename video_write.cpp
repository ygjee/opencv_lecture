
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

int main(int, char)	// Lecture - 2강 6번
{
	VideoCapture capture("E:\\999_Work\\111.avi");
	Mat frame;

	int askFileTypeBox = 0;
	int Color = 1;
	Size S = Size((int)capture.get(CV_CAP_PROP_FRAME_WIDTH),
		(int)capture.get(CV_CAP_PROP_FRAME_HEIGHT));

	VideoWriter outVideo;
	outVideo.open("E:\\999_Work\\outcpp_out.avi", askFileTypeBox, capture.get(CV_CAP_PROP_FPS), S, Color);

	if (!capture.isOpened())
	{
		printf("AVI file can not open.\n");
		return 0;
	}

	namedWindow("w");

	while(1)
	{
		capture >> frame;

		if (frame.empty())
			break;

		Sobel(frame, frame, frame.depth(), 1, 0);

		outVideo.write(frame);
		outVideo << frame;
		
		imshow("w", frame);
		if (waitKey(100) > 0)
			break;
	}

	return 0;
}
