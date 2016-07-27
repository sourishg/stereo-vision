#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char const *argv[])
{
  cv::Mat K1, K2;
  cv::Vec4d D1, D2;
  cv::Mat img1 = imread("/home/sourish/vision/FisheyeStereo/scene_imgs/12/left5.jpg", CV_LOAD_IMAGE_COLOR);
  cv::Mat img2 = imread("/home/sourish/vision/FisheyeStereo/scene_imgs/12/right5.jpg", CV_LOAD_IMAGE_COLOR);

  cv::FileStorage fs1("/home/sourish/vision/FisheyeStereo/build/cam_left.yml", cv::FileStorage::READ);
  cv::FileStorage fs2("/home/sourish/vision/FisheyeStereo/build/cam_right.yml", cv::FileStorage::READ);
  fs1["K1"] >> K1;
  fs1["D1"] >> D1;
  fs2["K1"] >> K2;
  fs2["D1"] >> D2;
  
  cv::Mat imgU1, imgU2;

  Matx33d K1new = Matx33d(K1); 
  //K1new(0, 0) = 1; K1new(1, 1) = 1; K1new(2, 2) = 1;
  Matx33d K2new = Matx33d(K2); 
  //K2new(0, 0) = 1; K2new(1, 1) = 1; K2new(2, 2) = 1;

  cv::fisheye::undistortImage(img1, imgU1, Matx33d(K1), Mat(D1), K1new);
  cv::fisheye::undistortImage(img2, imgU2, Matx33d(K2), Mat(D2), K2new);
  imshow("image1", imgU1);
  imshow("image2", imgU2);
  int k = waitKey(0);
  if (k > 0) {
		cout << "writing to file..." << endl;
    imwrite("left.jpg", imgU1);
    imwrite("right.jpg", imgU2);
  }
  return 0;
}
