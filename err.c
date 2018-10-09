#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
//Open the default video camera
VideoCapture cap(0);
 // if not success, exit program
if (cap.isOpened() == false)  
{
cout << "Cannot open the video camera" << endl;
cin.get(); //wait for any key press
return -1;
} 
double dWidth = cap.get(CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;
string window_name = "My Camera Feed";
//namedWindow(window_name); //create a window called "My Camera Feed"
int frame_width=   cap.get(CV_CAP_PROP_FRAME_WIDTH);
   int frame_height=   cap.get(CV_CAP_PROP_FRAME_HEIGHT);
   VideoWriter video("outputVid.avi",CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height),true);
while (true)
{

Mat frame;
Mat gray;
Mat blurred;
Mat thresh;
Mat lab;
bool bSuccess = cap.read(frame); // read a new frame from video 
Mat copy = frame.clone();

cvtColor(frame,gray,CV_BGR2GRAY);
cvtColor(frame,lab,CV_BGR2Luv);
GaussianBlur(gray,blurred,Size(11,11),0);

threshold(blurred,thresh, 250, 255, THRESH_BINARY);
double i = 0;
double j = 0;
for(i=0;i<dWidth;i++)
{
for(j=0;j<dHeight;j++)
{

Scalar color = lab.at<uchar>(Point(i,j));
if(colour.val[0] > 200)
{
frame.at<Vec3b>(Point(i,j)) = frame.at<Vec3b>(Point(i,j))/3;
}

}
}

//Breaking the while loop if the frames cannot be captured
if (bSuccess == false) 
{
cout << "Video camera is disconnected" << endl;
cin.get(); //Wait for any key press
break;
}

  //show the frame in the created window
imshow("Frame", frame);
video.write(frame);
//imshow("gray", gray);
//imshow("blurred",blurred);
imshow("thresh",thresh);
imshow("Original", copy);
imshow("Lab",lab);
//wait for for 10 ms until any key is pressed.  
//If the 'Esc' key is pressed, break the while loop.
//If the any other key is pressed, continue the loop 
//If any key is not pressed withing 10 ms, continue the loop 
if (waitKey(10) == 27)
{
cout << "Esc key is pressed by user. Stopping the video" << endl;
break;
}
}

return 0;

}
