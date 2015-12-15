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
const int MUTATIONS = 100;		//number of mutations per generation
const int GENERATIONS = 10000;	//number of generations

//returns the total difference in color between the two images
//the less, the better
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

//returns the main file name without the extension
string getFileName(string x)
{
	int i;
	for(i = 0; i < x.size(); i++)
	{
		if (x.at(i) == '.')
			break;
	}
	return x.erase(i, x.size() - i);
}

//determines shape to be used 
string getShape(int argc, char** argv)
{
	if (argc != 3) //not provided in command line
	{
		int x = rand() % 3;
		if (x == 0)
			return "ellipse";
		else if (x == 1)
			return "circle";
		else if (x == 2)
			return "rectangle";
	}
	else
	{
		cout << argv[2] << endl;
		if (string(argv[2]) == "E")
			return "ellipse";
		else if (string(argv[2]) == "C")
			return "circle";
		else if (string(argv[2]) == "R")
			return "rectangle";
		else
			return "bad";
	}
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
	string FILENAME = getFileName(argv[1]);	
	int ROWS = mainImage.rows;
	int COLS = mainImage.cols;
	
	//determine shape to use
	bool ELLIPSE = false, CIRCLE = false, RECTANGLE = false;
	string SHAPE = getShape(argc, argv);
	if (SHAPE == "bad")
	{
		cout << "Invalid shape input. Use E, C, or R." << endl;
		return 0;
	}
	else if (SHAPE == "ellipse")
		ELLIPSE = true;
	else if (SHAPE == "circle")
		CIRCLE = true;
	else if (SHAPE == "rectangle")
		RECTANGLE = true;

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
		if (ELLIPSE)
		{
			my_ellipse el(Point(rand()%COLS, rand()%ROWS));
			ellipse(current.at(i).img, el.pos, el.size, el.angle, 0, 360, el.color, -1);
			current.at(i).ellipses.push_back(el);
		}
		else if (CIRCLE)
		{
			my_circle C(Point(rand()%COLS, rand()%ROWS));
			circle(current.at(i).img, C.center, C.radius, C.color, -1);
			current.at(i).circles.push_back(C);
		}
	}

	picture bestPicture;
	Mat curModel(ROWS, COLS, CV_8UC3, Scalar(0,0,0));
	bestPicture.img = curModel;
	bestPicture.fitness = 9999;

	//start genetic hill climbing 
	for (int k = 0; k < GENERATIONS; k++)
	{
		cout << "Generation #" << k << endl;
		for (int n = 0; n < MUTATIONS; n++)
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
			my_ellipse el;
			my_circle C;
			if (ELLIPSE)
				el = current.at(bestPic).ellipses.at(current.at(bestPic).ellipses.size() - 1);
			else if (CIRCLE)
				C = current.at(bestPic).circles.at(current.at(bestPic).circles.size() - 1);
			
			for (int i = 0; i < POPULATION; i++) //mutate the population
			{
				current.at(i) = current.at(bestPic);
				if (i != bestPic)
				{
					if (ELLIPSE)
						el.mutate();
					else if (CIRCLE)
						C.mutate();
					Mat buf(ROWS, COLS, CV_8UC3, Scalar(0,0,0));
					bestPicture.img.copyTo(buf);	
					if (ELLIPSE)
					{
						ellipse(buf, el.pos, el.size, el.angle, 0, 360, el.color, -1);
						current.at(i).img = buf;
						current.at(i).ellipses.at(current.at(i).ellipses.size() - 1) = el;
					}
					else if (CIRCLE)
					{
						circle(buf, C.center, C.radius, C.color, -1);
						current.at(i).img = buf;
						current.at(i).circles.at(current.at(i).circles.size() - 1) = C;
					}
				}
			}
			
			if (n == MUTATIONS - 1) //after last mutation
			{
				//change bestPicture if new picture is an improvement
				cout << "Previous best = " << bestPicture.fitness << endl;
				cout << "Current best = " << current.at(bestPic).fitness << endl;
				if (bestPicture.fitness >= current.at(bestPic).fitness)
				{
					bestPicture = current.at(bestPic);
					stringstream path;
					if (k % 5 == 0)	//save image to computer
					{
						if (k < 10)
							path << FILENAME << "000" << k << ".jpg";
						else if (k < 100)
							path << FILENAME << "00" << k << ".jpg";
						else if (k < 1000)
							path << FILENAME << "0" << k << ".jpg";
						else
							path << FILENAME << k << ".jpg";
						string savePath = path.str();
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
			if (ELLIPSE)
			{
				current.at(q).ellipses = bestPicture.ellipses;
				my_ellipse el(Point(rand()%COLS, rand()%ROWS));
				ellipse(buf, el.pos, el.size, el.angle, 0, 360, el.color, -1);
				current.at(q).img = buf;
				current.at(q).ellipses.push_back(el);
			}
			else if (CIRCLE)
			{
				current.at(q).circles = bestPicture.circles;
				my_circle C(Point(rand()%COLS, rand()%ROWS));
				circle(buf, C.center, C.radius, C.color, -1);
				current.at(q).img = buf;
				current.at(q).circles.push_back(C);
			}
		}
	}
	
	waitKey(0);
	return 0;

}
