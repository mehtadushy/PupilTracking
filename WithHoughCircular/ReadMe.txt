Usage:

./PupilTracking <input_video_filename> <output_video_filename>

Uses OpenCV.
This implementation treats each frame of the video separately. The input frame is thresholded so that only 10% of the darkest pixels remain. The frame is then passed through a median filter and then through erosion and dilation operations before the inbuilt HoughCircular function of OpenCV processes the frame to find out circles in the image.
The output frame has the circle estimates overlaid over the input frame. If one desires to see the actual frame passed to HoughCircular, one must set show_processing_frame to true in Pupil_Detection_Hough_Circular.cpp
