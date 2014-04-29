// Initial Experimentation for Pupil Detection in Eye Videos
//----------------------------------------------------------
// Author: Dushyant Mehta
//         mehtadushy@gmail.com
// Date: 18th April 2014
//----------------------------------------------------------
// The following is an initial attempt at detecting/extracting
// pupils of the human eye from a decent quality video stream
// of the human eye. Since the video only contains the eye,
// there is no need for any advanced feature detection methods
// to first find a bounding box for the eye itself.
// Each frame is treated individually and hough transform is
// used for extracting the pupil, which is assumed to be a
// circle and not an ellipse, which holds under the restriction
// of the video having been captured head on and not from an
// extreme angle relative to the forward direction of the face.

// Additional Comments: The implementation makes use of OpenCV

// Implementation Details: <To come after the implementation>
// Pass the video file name through the command line
// Display the video in one window
// Put out results of experimentation to a second window

#include <QtCore/QCoreApplication>
#include<cv.h>
#include<highgui.h>
#include<iostream>
#include "PupilDetection_Hough_Circular.h"
using namespace std;

int main(int argc, char *argv[])
{
    cv::VideoCapture videoFile;
    cv::VideoWriter outputVideo;
    if(argc<3)
    {
        cout<<"Video in/out filename missing!!!\n";
        exit(EXIT_FAILURE);
    }
    else
    {
        videoFile.open(argv[1]);
        if(!videoFile.isOpened())
        {
            cout<<"Input Video File could not be opened\n";
            exit(EXIT_FAILURE);
        }

        //Get codec type of input. Use the same codec for the output
        int ex = static_cast<int>(videoFile.get(CV_CAP_PROP_FOURCC));
        //Get frame size of the input video and use the same for output
        Size S = Size((int)videoFile.get(CV_CAP_PROP_FRAME_WIDTH),
                      (int)videoFile.get(CV_CAP_PROP_FRAME_HEIGHT));

        outputVideo.open(argv[2],ex,videoFile.get(CV_CAP_PROP_FPS),S,true);
        if(!outputVideo.isOpened())
        {
            cout<<"Output Video File could not be opened\n";
            exit(EXIT_FAILURE);
        }
    }

    double frame_rate= videoFile.get(CV_CAP_PROP_FPS);
    int delay_bw_frames = 1000/frame_rate;   //in ms

    cv::Mat currFrame;
    cv::Mat processedFrame;
    cv::namedWindow("Video Input");
    cv::namedWindow("Processed Output");

    bool stop_flag(false);

    // Iterate over frames
    while(!stop_flag)
    {
        if(!videoFile.read(currFrame))
            break;
        cv::imshow("Video Input", currFrame);

        PupilDetection_Hough_Circular(currFrame, processedFrame);
        cv::imshow("Processed Output", processedFrame);
        outputVideo<<processedFrame;

        if(cv::waitKey(delay_bw_frames) >= 0)
            stop_flag = true;
    }


}


