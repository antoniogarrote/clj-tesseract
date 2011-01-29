#ifndef __TESSERACT_PROXY_H__
#define __TESSERACT_PROXY_H__

#include <iostream>
#include "baseapi.h"
#include "image.h"

using namespace tesseract;

class TessProxy {

  TessBaseAPI *	p_tessAPI;   // API object pointer
  char* p_dataPath;          // image inputn file path
  char* p_outputPath;
  char* p_lang;              // trained lang

public:

  TessProxy(std::string  dataPath, std::string lang);
  TessProxy(std::string  dataPath);
  ~TessProxy();

  char* captureImage(Image* img);

  char* captureImage(const unsigned char* data,
                     int bytesPerPixel,
                     int bytesPerLine,
                     int left,
                     int top,
                     int width,
                     int height);

  void setImage(const unsigned char* data,
                int bytesPerPixel,
                int bytesPerLine,
                int width,
                int height);

  void setImage(Image* img);

  void setRectangle(int left, int top, int width, int height);

  void clearAdaptativeClassifier(void);

  void clear();

  void end();

  char* getText();

protected:

  void initializeTessAPI();
};


#endif // __TESSERACT_PROXY_H__
