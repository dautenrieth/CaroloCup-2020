#include "auxiliary_functions.h"
#define _USE_MATH_DEFINES
#ifndef M_PI
#define M_PI	3.14159265358979323846f
#endif

Mat drawLines(Mat img, double coefficients[], double coefficients2[], double coefficients3[]) {
    for (int X = 0; X < IMAGE_HEIGHT; X++) {
        int Y = int(coefficients[3] * X * X * X + coefficients[2] * X * X + coefficients[1] * X + coefficients[0]);
        if (Y < IMAGE_WIDTH - 2 && Y >= 0) {
            img.at<uchar>(X, Y) = 255;
            //cout << X << ", " << Y << endl;
            img.at<uchar>(X, Y + 1) = 255;
            img.at<uchar>(X, Y + 2) = 255;
        }
    }
    for (int X2 = 0; X2 < IMAGE_HEIGHT; X2++) {
        int Y2 = int(coefficients2[3] * X2 * X2 * X2 + coefficients2[2] * X2 * X2 + coefficients2[1] * X2 + coefficients2[0]);
        if (Y2 < IMAGE_WIDTH - 2 && Y2 >= 0) {
            img.at<uchar>(X2, Y2) = 255;
            //cout << X << ", " << Y2 << endl;
            img.at<uchar>(X2, Y2 + 1) = 255;
            img.at<uchar>(X2, Y2 + 2) = 255;
        }
    }
    for (int X3 = 0; X3 < IMAGE_HEIGHT; X3++) {
        int Y3 = int(coefficients3[3] * X3 * X3 * X3 + coefficients3[2] * X3 * X3 + coefficients3[1] * X3 + coefficients3[0]);
        if (Y3 < IMAGE_WIDTH - 2 && Y3 >= 0) {
            img.at<uchar>(X3, Y3) = 255;
            //cout << X << ", " << Y2 << endl;
            img.at<uchar>(X3, Y3 + 1) = 255;
            img.at<uchar>(X3, Y3 + 2) = 255;
        }
    }

    return img;
}

float check_pixels(Mat* img, double coefficients1[], double coefficients2[], double coefficients3[], int height, bool show, int mode, int pixels) {
    // create a line where the pixels which need to be checked are on
    // y = c*x + d -> x = (y-d)/c
    // c = -1/f'(x) , d = f(x)-c*x
    // Because of the orientation of the line it is easier to calculate the y-values instead of the x-values
    int x = height;
    float c = 0, v = 0, start_y = 0;
    double m;

    // define stoping conditions
    double stop_condition = 2000;

    if (*coefficients2 == (0, 0, 0, 0)) {
        m = -1 / (3 * coefficients3[3] * x * x + 2 * coefficients3[2] * x + coefficients3[1]);
        stop_condition = 0;

        pixels = abs(TRACK_WIDTH * cos(M_PI / 2 - atan(m)));
    }
    else {
        if (mode == 23) {
            stop_condition = (coefficients2[3] * x * x * x + coefficients2[2] * x * x + coefficients2[1] * x + coefficients2[0]);
        }
        else if (mode == 12) {
            stop_condition = (coefficients1[3] * x * x * x + coefficients1[2] * x * x + coefficients1[1] * x + coefficients1[0]);
        }
        else {
            cout << "no permissible mode in the check_pixels fuction" << endl;
        }
    }

    start_y = coefficients3[3] * x * x * x + coefficients3[2] * x * x + coefficients3[1] * x + coefficients3[0];
    // This query is necessary because c can be zero if the function is a straight line
    if ((3 * coefficients3[3] * x * x + 2 * coefficients3[2] * x + coefficients3[1]) < 0.001) {
        c = 1000000; //set c to a high number
    }
    else {
        c = -1 / (3 * coefficients3[3] * x * x + 2 * coefficients3[2] * x + coefficients3[1]);
    }
    v = (3 * coefficients3[3] * x * x + 2 * coefficients3[2] * x + coefficients3[1]);



    float d = start_y - (c * x); 
    double y = 0;
    //define starting conditions

    y = start_y - double(DISTANCE_FROM_LINE); //Start on the right line


    int brightness_pixel, bright_pixel = 0, amount_pixel = 0;




    //While pixels are on the right lane
    while (y - double(DISTANCE_FROM_LINE) > stop_condition&& pixels > 0) {
        if (*coefficients2 == (0, 0, 0, 0)) {}
        else
        {
            if (mode == 23) {
                stop_condition = (coefficients2[3] * x * x * x + coefficients2[2] * x * x + coefficients2[1] * x + coefficients2[0]);
            }
            else if (mode == 12) {
                stop_condition = (coefficients1[3] * x * x * x + coefficients1[2] * x * x + coefficients1[1] * x + coefficients1[0]);
            }
            else {
                cout << "no permissible mode in the check_pixels fuction" << endl;
            }
        }

        x = (y - d) / c;
        y--;
        pixels--;
        if (mode == 12) {
            // Wait till you are behind the middle line to start counting
            if (y + double(DISTANCE_FROM_LINE) < coefficients2[3] * x * x * x + coefficients2[2] * x * x + coefficients2[1] * x + coefficients2[0])
            {
                if (x < 0 || x > 480 || y < 0 || y > 1480) {
                    cout << "outside";
                }
                else {
                    brightness_pixel = (*img).at<uchar>(x, y);
                    if (brightness_pixel > TRESHOLD) {
                        bright_pixel++;
                    }
                    amount_pixel++;
                    if (show)
                    {
                        (*img).at<uchar>(x, y) = 255;
                    }
                }
            }
        }
        else {
            if (x < 0 || x > 480 || y < 0 || y > 1480) {
                cout << "outside";
            }
            else {
                brightness_pixel = (*img).at<uchar>(x, y);
                if (brightness_pixel > TRESHOLD) {
                    bright_pixel++;
                }
                amount_pixel++;
                if (show)
                {
                    (*img).at<uchar>(x, y) = 255;
                }
            }
        }
    }
    return (float(bright_pixel) / amount_pixel);
}

