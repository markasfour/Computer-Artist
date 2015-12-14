#include <iostream>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include "rectangle.h"
#include "circle.h"
#include "ellipse.h"
#include "picture.h"

using namespace std;
using namespace cv;

const int POPULATION = 10;

float getFitness (picture curr, Mat mainImage)
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
	int lowest = 9999;
	for (int k = 0; k < 10000; k++)
	{
		cout << "Number of shapes = " << k << endl;
		for (int n = 0; n < 100; n++)
		{
			//calculate image fitness level for all in population
			for (int i = 0; i < POPULATION; i++)
			{
				current.at(i).fitness = 0;
				for (int x = 0; x < current.at(i).img.rows; x++)
				{
					for (int y = 0; y < current.at(i).img.cols; y++)
					{
						Vec3b bgrMainPic = mainImage.at<Vec3b>(x, y);
						Vec3b bgrCurrPic = current.at(i).img.at<Vec3b>(x, y);
						
						current.at(i).fitness += abs(bgrCurrPic.val[0] - bgrMainPic.val[0]);	//b
						current.at(i).fitness += abs(bgrCurrPic.val[1] - bgrMainPic.val[1]);	//g
						current.at(i).fitness += abs(bgrCurrPic.val[2] - bgrMainPic.val[2]);	//r
					}
				}
				current.at(i).fitness /= (current.at(i).img.rows * current.at(i).img.cols) * 3;
				//cout << "Fitness = " << current.at(i).fitness << endl;
				if (current.at(i).fitness < lowest)
				{
					lowest = current.at(i).fitness;
					cout << "NEW LOWEST = " << lowest << endl;
				}
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
			cout << "Mutation # = " << n << endl;
			cout << "bestPic = " << bestPic << endl;
			cout << "bestFitnes = " << bestFitness << endl;
			

			//generate new population by mutating the best image
			cout << "SIZE = " << current.at(bestPic).ellipses.size() << endl;
			my_ellipse el = current.at(bestPic).ellipses.at(current.at(bestPic).ellipses.size() - 1);
			for (int i = 0; i < POPULATION; i++) //mutate the population
			{
				current.at(i) = current.at(bestPic);
				if (i != bestPic)
				{
					el.pos += Point(rand()%5-5/2,rand()%5-5/2) ; 
					el.color += Scalar(rand()%10-10/2,rand()%10-10/2,rand()%10-10/2) ;
					el.size += Size(rand()%5-5/2,rand()%5-5/2) ;
					el.size.width = abs(el.size.width) ;
					el.size.height = abs(el.size.height) ;
					el.angle += rand()%5-5/2;
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
					path << k << ".jpg";
					string savePath = path.str();
					if (k % 5 == 0)
					{
						imwrite(savePath, bestPicture.img);
					}
				}
				else
					cout << "NOPE!!!!!!!!!!!!!!!!" << endl;
				cout << "Best fitness = " << bestFitness << endl;
			}
		}
		for (int i = 0; i < POPULATION; i++) //create new shapes
		{
			Mat buf(ROWS, COLS, CV_8UC3, Scalar(0,0,0));
			bestPicture.img.copyTo(buf);
			current.at(i).fitness = bestPicture.fitness;
			current.at(i).ellipses = bestPicture.ellipses;
			
			my_ellipse el(Point(rand() % COLS, rand() % ROWS),
						  Size(rand()%100+20, rand()%100+20),
						  Scalar(rand() % 255, rand() % 255, rand() % 255),
						  rand()%360);

			current.at(i).img = buf;
			current.at(i).ellipses.push_back(el);
		}
	}
	
	waitKey(0);
	return 0;

}
