#include "utils.h"

Window::Window(char* p_winName) {
  this -> p_winName = p_winName;
  cvNamedWindow(p_winName, CV_WINDOW_AUTOSIZE);
}

Window::~Window() {
  cvDestroyWindow(this -> p_winName);
}

void Window::waitForKey() {
  cvWaitKey(0);  
}

void Window::showImage(Image* img) {
  cvShowImage(this -> p_winName, img -> toIplImage());
}

void Window::closeWindow() {
  cvDestroyWindow(this -> p_winName);
}
