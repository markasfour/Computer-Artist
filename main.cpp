#include <iostream>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main (int argc, char** argv)
{
	Mat mainImage = imread(argv[1], IMREAD_UNCHANGED);
	if (!mainImage.data)
	{
		cout << "Could not open image" << endl;
		return 0;
	}

	namedWindow("Evolving Image", WINDOW_AUTOSIZE);
	imshow("Evolving Image", mainImage);

	waitKey(0);

	srand(time(NULL));

	return 0;

}
