
#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/cudafilters.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;
using namespace std;

int main(int, char)
{
	Mat frame;
	Mat old_frame;
	Mat sub_frame;
	Mat img_result;

	VideoCapture stream1(0);

	if (!stream1.isOpened())
	{
		cout << "cannot open camera 0";
		return 0;
	}

	while (1)
	{
		if (!(stream1.read(frame)))
			break;

		if (old_frame.empty())
		{
			old_frame = frame.clone();
			continue;
		}

		subtract(old_frame, frame, sub_frame);

		hconcat(frame, sub_frame, img_result);

		imshow("frame", img_result);

		old_frame = frame.clone();

		if (waitKey(5) >= 0)
			break;
	}

	return 0;
}

