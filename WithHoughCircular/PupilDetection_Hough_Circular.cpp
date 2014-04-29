#include<cv.h>
#include "PupilDetection_Hough_Circular.h"

#define DEBUG_PUPIL 0

void PupilDetection_Hough_Circular(cv::Mat & img, cv::Mat & out)
{
    //Convert to gray
   cv::cvtColor(img,out, CV_BGR2GRAY);

   //Get Histogram and find the value that covers 10% of the pixels
   //from the darker side (the darkest 10% pixels)

   cv::Mat hist;
   float range[]={0.0, 255.0};
   const float * histrange[] = {range};
   int channels[1];
   int hist_size[1];
   hist_size[0]=50;
   channels[0]=0;
   cv::calcHist(&out, 1,channels , cv::Mat(), hist, 1, hist_size,histrange);
   normalize(hist, hist, 1.0, 0, NORM_L1);
  //Get the threshold value corresponding to 10% darkest pixels
   float thresh_percent=10.0/100.0;
   float accum=0;
   int thresh_value;
   for(thresh_value=0; thresh_value<hist_size[0]; thresh_value++)
   {
       accum+= hist.at<float>(thresh_value);
       if(accum > thresh_percent)
           break;
   }
#if DEBUG_PUPIL
   std::cout<<"Thresh Percent "<<thresh_percent<<std::endl;
   std::cout<<"Thresh Value"<<thresh_value<<", "<<(thresh_value)*(255.0/hist_size[0])<<std::endl;
   std::cout<<hist;
#endif

  //Threshold the image
  cv::threshold(out,out,(thresh_value)*(255.0/hist_size[0]),255,THRESH_BINARY_INV);


  //Run the image through a median filter
  medianBlur(out,out,7);

  out=255-out;

  //Do some morphological magic
  //Erode, then dialate
  Mat element = getStructuringElement(MORPH_ELLIPSE,Size(15,15));
  erode(out,out,element);
  dilate(out,out,element);  vector<Vec3f> circles;

  // Extract all circles from the image
  HoughCircles(out,circles,CV_HOUGH_GRADIENT,1,30, 200,20,min(out.rows,out.cols)/20, min(out.rows,out.cols)/4);


  std::cout<<"Number of Circles Detected "<<circles.size()<<std::endl;
  // Draw the circles detected
  for( size_t i = 0; i < circles.size(); i++ )
  {
      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);
      // circle center
      circle( img, center, 3, Scalar(0,255,0), -1, 8, 0 );
      // circle outline
      circle(img, center, radius, Scalar(0,0,255), 3, 8, 0 );
   }

  bool show_processing_frame = false;
  if(!show_processing_frame)
  {
      out=img;
  }

}


// The first approach would be to search individual frames for circles
// Later on, a tracking based approach can be used, that does a full search
// in the first frame and then subsequently upon losing track of the iris,
// with the search beginning at the last known location of the iris in that
// case.
