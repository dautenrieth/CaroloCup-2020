#include "object_detection.h"
#include "auxiliary_functions.h"

extern obstacle myobstacle;
extern startline mystartline;
extern stopline mystopline;
extern obstacle_left myleftobstacle;


void object_detection(Mat* img, double coefficients1[], double coefficients2[], double coefficients3[]) {
    //Tracking
    if (myobstacle.get_tracking_status()) {
        myobstacle.track(img, coefficients1, coefficients2, coefficients3);
        putText(*img, "Tracking Obstacle", cvPoint(30, 400), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
    }
    if (mystartline.get_tracking_status()) {
        mystartline.track(img, coefficients1, coefficients2, coefficients3);
        putText(*img, "Tracking Startline", cvPoint(30, 430), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
    }
    if (mystopline.get_tracking_status()) {
        mystopline.track(img, coefficients1, coefficients2, coefficients3);
        putText(*img, "Tracking Stopline", cvPoint(30, 460), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
    }
    if (myleftobstacle.get_tracking_status()) {
        myleftobstacle.track(img, coefficients1, coefficients2, coefficients3, false);
        putText(*img, "Tracking Left-Obstacle", cvPoint(30, 370), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA);
    }

    //triggerline check
    float perc = check_pixels(img, coefficients1, coefficients2, coefficients3, START_HEIGHT, true);
    putText(*img, to_string(perc), cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA); //Show percentage of white in triggerline
    if (perc > TRIGGER_PERC) {
        // Just start detecting objects when the currently tracked object is out of the way
        if (myobstacle.get_out_of_start() && mystartline.get_out_of_start() && mystopline.get_out_of_start()) { // All old objects out of the way
            
            if (!myobstacle.detection(img, coefficients1, coefficients2, coefficients3)) { // Check for Obstacle
                if (!mystartline.detection(img, coefficients1, coefficients2, coefficients3)) { // If not an Obstacle check for startline
                    mystopline.detection(img, coefficients1, coefficients2, coefficients3); // if not an Obstacle and no startline it has to be a stopline
                }
            }
        }
    }
    else {
        // Reset the out_of_start variable
        myobstacle.set_out_of_start(true);
        mystopline.set_out_of_start(true);
        mystartline.set_out_of_start(true);
    }

    //same logic for the left lane but just for the obstacle
    float perc2 = check_pixels(img, coefficients1, coefficients2, coefficients3, START_HEIGHT, true, 12);
    putText(*img, to_string(perc2), cvPoint(30, 50), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200, 200, 250), 1, CV_AA); //Show percentage of white in triggerline
    if (perc2 > TRIGGER_PERC) {
        // Just start detecting objects when the currently tracked object is out of the way
        if (myleftobstacle.get_out_of_start()) { // All old objects out of the way
            if (myobstacle.get_tracking_status()) { // if an obstacle on the other track is tracked this can indicate that the activation of the detection function is due to that obstacle
                cout << "Checking for overlapping Right-Obstacle" << endl;
                //check_overlapping_obstacle(img, coefficients1, coefficients2, coefficients3);
            }
            myleftobstacle.detection(img, coefficients1, coefficients2, coefficients3);
        }
    }
    else {
        // Reset the out_of_start variable when necessary
        // Just writing more efficient?
        myleftobstacle.set_out_of_start(true);
    }


    *img = drawLines(*img, coefficients1, coefficients2, coefficients3);
    imshow("Draw", *img);
}