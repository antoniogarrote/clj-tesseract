#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "cv.h"
#include "highgui.h"
#include "image.h"

using namespace std;

class Camera
{

  CvCapture* p_capture;
  IplImage*  p_image;

 public:

  Camera();
  ~Camera();

  void takeSnapshot();
  Image* getImage();
  //  void saveToFile();
};

#endif // CAMERA_H
