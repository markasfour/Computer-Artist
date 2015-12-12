#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct my_rectangle
{
	Point p1;
	Point p2;
	Scalar color;
	float transparency;

	my_rectangle()
	{
		p1 = Point(0, 0);
		p2 = Point(0, 0);
		color = Scalar(0, 0, 0);
		transparency = 0.0;
	}
	my_rectangle(Point a, Point b, Scalar c, float t)
	{
		p1 = a;
		p2 = b; 
		color = c;
		transparency = t;
	}
};

#endif
