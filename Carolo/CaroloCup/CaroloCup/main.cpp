#include<opencv2/opencv.hpp>
#include<fstream>
#include<iostream>
#include<math.h>
#include<string.h>
#include<windows.h>

#include "defines.h"
#include "auxiliary_functions.h"
#include "object.h"
#include "object_types.h"
#include "object_detection.h"

using namespace std;
using namespace cv;


#define NUMBER_OF_PICTURES  169
string pictures[NUMBER_OF_PICTURES];

//Necessary in main programm
obstacle myobstacle;
startline mystartline;
stopline mystopline;
obstacle_left myleftobstacle;


//TO DO:
// - check-pixel-Funktion fertig stellen 
// - Overlapping-Obstacle-Fall beheben


int main()
{
    double coefficients1[4] = {};
    double coefficients2[4] = {};
    double coefficients3[4] = {};
    Mat img;

    // Framework for loading pictures
    string row, name;
    ifstream myfile("param.txt");
    for (int pic = 0; pic < NUMBER_OF_PICTURES; pic++) {

        getline(myfile, row);
        stringstream rowpuffer(row);
        rowpuffer >> name >> coefficients1[0] >> coefficients1[1] >> coefficients1[2] >> coefficients1[3] >> coefficients2[0] >> coefficients2[1] >> coefficients2[2] >> coefficients2[3] >> coefficients3[0] >> coefficients3[1] >> coefficients3[2] >> coefficients3[3];

        // Uncomment the following to pretend one function is missing
        //coefficients2[0] = 0; coefficients2[1] = 0; coefficients2[2] = 0; coefficients2[3] = 0;

        img = imread("Bilder/" + name, IMREAD_GRAYSCALE);

        // Show original picture -> Pictures from the main programm will already have a treshold filter applied
        //threshold(img, img, TRESHOLD, 255, THRESH_BINARY);

        //Show image name
        //putText(img, name, cvPoint(400, 400), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);

        // function which will be implemented in the car
        object_detection(&img, coefficients1, coefficients2, coefficients3);
        
        

        waitKey(0);
    }

    waitKey(0);
    return 0;
}

