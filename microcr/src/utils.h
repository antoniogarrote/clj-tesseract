#ifndef __UTILS_H__
#define __UTILS_H__

#include <cv.h>
#include <highgui.h>
#include "image.h"

class Window
{
  char* p_winName;

 public:

  Window(char* p_winName);
  ~Window();

  static void waitForKey();

  void showImage(Image* img);
  void closeWindow();
};

#endif // __UTILS__
