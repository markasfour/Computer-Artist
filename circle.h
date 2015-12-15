#ifndef CIRCLE_H
#define CIRCLE_H

#include <opencv2/opencv.hpp>
#include <stdlib.h>

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
	my_circle(Point x)
	{
		center = x;
		radius = rand()%100+1;
		color = Scalar(rand()%255, rand()%255, rand()%255);
	}

	void mutate()
	{
		center += Point(rand()%15-15/2,rand()%15-15/2) ; 
		radius += abs(rand()%7-7/2);
		color += Scalar(rand()%50-50/2,rand()%50-50/2,rand()%50-50/2);
	}
};

#endif
