#include <iostream>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include "rectangle.h"
#include "circle.h"
#include "ellipse.h"
#include "picture.h"

using namespace std;
using namespace cv;

const int POPULATION = 3;		//size of test population

float getFitness(picture curr, Mat mainImage)
{
	float f = 0.0;
	for (int x = 0; x < curr.img.rows; x++)
	{
		for (int y = 0; y < curr.img.cols; y++)
		{
			Vec3b bgrMainPic = mainImage.at<Vec3b>(x, y);
			Vec3b bgrCurrPic = curr.img.at<Vec3b>(x, y);
			
			f += abs(bgrCurrPic.val[0] - bgrMainPic.val[0]);	//b
			f += abs(bgrCurrPic.val[1] - bgrMainPic.val[1]);	//g
			f += abs(bgrCurrPic.val[2] - bgrMainPic.val[2]);	//r
		}
	}
	return f;
}

int main (int argc, char** argv)
{
	//get main image
	Mat mainImage = imread(argv[1], IMREAD_UNCHANGED);
	if (!mainImage.data)
	{
		cout << "Could not open image" << endl;
		return 0;
	}
	
	int ROWS = mainImage.rows;
	int COLS = mainImage.cols;

	//set up display windows
	namedWindow("Evolving Image", WINDOW_AUTOSIZE);
	//set rand seed
	srand(time(NULL));
	
	vector<picture> current(POPULATION);

	//generate random images
	for (int i = 0; i < POPULATION; i++)
	{
		Mat curModel(ROWS, COLS, CV_8UC3, Scalar(0,0,0));
		current.at(i).img = curModel;
		current.at(i).fitness = 0;

		Mat buf(ROWS, COLS, CV_8UC3, Scalar(0,0,0));
		my_ellipse el(Point(rand()%COLS, rand()%ROWS),
					  Size(rand()%100+20, rand()%100+20),
					  Scalar(rand()%255, rand()%255, rand()%255),
					  rand()%360);
		ellipse(current.at(i).img, el.pos, el.size, el.angle, 0, 360, el.color, -1);
		current.at(i).ellipses.push_back(el);
	}

	picture bestPicture;
	Mat curModel(ROWS, COLS, CV_8UC3, Scalar(0,0,0));
	bestPicture.img = curModel;
	bestPicture.fitness = 9999;
	
	for (int k = 0; k < 10000; k++)
	{
		cout << "Number of shapes = " << k << endl;
		for (int n = 0; n < 100; n++)
		{
			//calculate image fitness level for all in population
			for (int i = 0; i < POPULATION; i++)
			{
				current.at(i).fitness = 0;
				current.at(i).fitness = getFitness(current.at(i), mainImage);
				current.at(i).fitness /= (current.at(i).img.rows * current.at(i).img.cols) * 3;
				imshow("Evolving Image", current.at(i).img);
				waitKey(1);
			}

			float bestFitness = 9999;
			int bestPic = -1;

			//select best image generated in population
			for (int i = 0; i < POPULATION; i++)
			{
				if (current.at(i).fitness < bestFitness)
				{
					bestFitness = current.at(i).fitness;
					bestPic = i;
				}
			}

			//generate new population by mutating the best image
			my_ellipse el = current.at(bestPic).ellipses.at(current.at(bestPic).ellipses.size() - 1);
			for (int i = 0; i < POPULATION; i++) //mutate the population
			{
				current.at(i) = current.at(bestPic);
				if (i != bestPic)
				{
					el.pos += Point(rand()%15-15/2,rand()%15-15/2) ; 
					el.color += Scalar(rand()%50-50/2,rand()%50-50/2,rand()%50-50/2) ;
					el.size += Size(rand()%15-15/2,rand()%15-15/2) ;
					el.size.width = abs(el.size.width) ;
					el.size.height = abs(el.size.height) ;
					el.angle += rand()%15-15/2;
					Mat buf(ROWS, COLS, CV_8UC3, Scalar(0,0,0)) ;
					bestPicture.img.copyTo(buf) ;																		
					ellipse(buf, el.pos, el.size, el.angle, 0, 360, el.color, -1);
					current.at(i).img = buf;
					current.at(i).ellipses.at(current.at(i).ellipses.size() - 1) = el;
				}
			}

			if (n == 99)
			{
				//change bestPicture if new picture is an improvement
				cout << "Previous best = " << bestPicture.fitness << endl;
				cout << "Current best = " << current.at(bestPic).fitness << endl;
				if (bestPicture.fitness >= current.at(bestPic).fitness)
				{
					bestPicture = current.at(bestPic);
					stringstream path;
					path << "KyloRen" << k << ".jpg";
					string savePath = path.str();
					if (k % 5 == 0)
					{
						imwrite(savePath, bestPicture.img);
					}
				}
				cout << "Best fitness = " << bestFitness << endl;
			}
		}
		for (int q = 0; q < POPULATION; q++) //create new shapes
		{
			Mat buf(ROWS, COLS, CV_8UC3, Scalar(0,0,0));
			bestPicture.img.copyTo(buf);
			current.at(q).fitness = bestPicture.fitness;
			current.at(q).ellipses = bestPicture.ellipses;
			
			my_ellipse el(Point(rand()%COLS, rand()%ROWS),
						  Size(rand()%100+20, rand()%100+20),
						  Scalar(rand()%255, rand()%255, rand()%255),
						  rand()%360);
			ellipse(buf, el.pos, el.size, el.angle, 0, 360, el.color, -1);
			current.at(q).img = buf;
			current.at(q).ellipses.push_back(el);
		}
	}
	
	waitKey(0);
	return 0;

}
