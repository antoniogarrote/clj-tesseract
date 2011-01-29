#include "camera.h"

Camera::Camera() {
  p_capture = NULL;
  p_image   = NULL;
}

Camera::~Camera() {
  if(p_capture != NULL) {
    cvReleaseCapture(&p_capture);
  }
}

void Camera::takeSnapshot() {
  if(p_capture != NULL) {
    cvReleaseCapture(&p_capture);
  }
  p_capture = cvCreateCameraCapture(0);
}

Image* Camera::getImage(){
  Image* img = new Image(cvQueryFrame(p_capture));
  return img;
}
