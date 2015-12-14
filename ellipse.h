#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct my_ellipse
{
	Point pos ;
	Size size ;
	Scalar color ;
	float angle ;

	my_ellipse()
	{
		pos = Point(0, 0);
		size = Size(0, 0);
		color = Scalar(0, 0, 0);
		angle = 0.0;
	}
	my_ellipse(Point p, Size s, Scalar c, float a) 
	{
		pos = p;
		size = s;
		color = c;
		angle = a;
	}
};

#endif
