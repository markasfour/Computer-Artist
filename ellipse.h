#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <opencv2/opencv.hpp>
#include <stdlib.h>

using namespace std;
using namespace cv;

struct my_ellipse
{
	Point pos ;
	Size size ;
	Scalar color ;
	float angle ;

	my_ellipse() //default constructor
	{
		pos = Point(0, 0);
		size = Size(0, 0);
		color = Scalar(0, 0, 0);
		angle = 0.0;
	}
	my_ellipse(Point x)	//construct random ellipse from point x
	{
		pos = x;			  
		size = Size(rand()%100+20, rand()%100+20);
		color =	Scalar(rand()%255, rand()%255, rand()%255);
		angle = rand()%360;
	}

	void mutate()
	{
		pos += Point(rand()%15-15/2,rand()%15-15/2) ; 
		color += Scalar(rand()%50-50/2,rand()%50-50/2,rand()%50-50/2) ;
		size += Size(rand()%15-15/2,rand()%15-15/2) ;
		size.width = abs(size.width) ;
		size.height = abs(size.height) ;
		angle += rand()%15-15/2;
	}
};

#endif
