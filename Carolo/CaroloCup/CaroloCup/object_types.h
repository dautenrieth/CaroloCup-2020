// This file contains all possible object types
#pragma once
#include<opencv2/opencv.hpp>
using namespace cv;
#include "object.h"
#include "defines.h"
#include "auxiliary_functions.h"


// The Obstacle class extends the object class and gives it a unique detection function, which
// will determine if the found object is an obstacle or not
class obstacle : public object {
public:
	bool detection(Mat* img, double coefficients1[], double coefficients2[], double coefficients3[]);
};

class startline : public object {
public:
	bool detection(Mat* img, double coefficients1[], double coefficients2[], double coefficients3[]);
};

class stopline : public object {
public:
	bool detection(Mat* img, double coefficients1[], double coefficients2[], double coefficients3[]);
};

//Extension
class obstacle_left : public object {
public:
	bool detection(Mat* img, double coefficients1[], double coefficients2[], double coefficients3[]);
};