#ifndef CIRCLE_H
#define CIRCLE_H

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct my_circle
{
	Point center;
	int radius;
	Scalar color;

	my_circle()
	{
		center = Point(0, 0);
		radius = 0;
		color = Scalar(0, 0, 0);
	}
	my_circle(Point a, int b, Scalar c)
	{
		center = a;
		radius = b; 
		color = c;
	}
};

#endif
