#include "tesseract_proxy.h"

TessProxy::TessProxy(std::string dataPath, std::string lang) {
  p_dataPath   = (char*) dataPath.c_str();

  // this value will be used to build the path to the
  // training data for the provided lang
  // e.g. for value 'eng' it will look for directory
  // /usr/local/path_to_tesseract/eng.traineddata
  p_lang = (char*) lang.c_str();
  p_tessAPI    = new TessBaseAPI;

  initializeTessAPI();
};

TessProxy::TessProxy(std::string dataPath) {
  p_dataPath   = (char*) dataPath.c_str();

  // this value will be used to build the path to the
  // training data for the provided lang
  // e.g. for value 'eng' it will look for directory
  // /usr/local/path_to_tesseract/eng.traineddata
  p_lang       = NULL;
  p_tessAPI    = new TessBaseAPI;

  initializeTessAPI();
};

TessProxy::~TessProxy() {
  delete p_tessAPI;
}

void TessProxy::initializeTessAPI() {
  if (p_tessAPI -> Init(p_dataPath, p_lang) != 0) {
    throw("Error initializing Tesseract");
  }
}

char* TessProxy::captureImage(Image* img) {
  char* result = this -> captureImage((const unsigned char*) img -> rawData(),
                                      img -> bytesPerPixel(),
                                      img -> bytesPerLine(),
                                      0,
                                      0,
                                      img -> width(),
                                      img -> height());
  return result;
}

char* TessProxy::captureImage(const unsigned char* data,
                              int bytesPerPixel,
                              int bytesPerLine,
                              int left,
                              int top,
                              int width,
                              int height) {

  char* result = p_tessAPI -> TesseractRect(data,
                                            bytesPerPixel,
                                            bytesPerLine,
                                            left,
                                            top,
                                            width,
                                            height);
  return result;
}


void TessProxy::clearAdaptativeClassifier() {
  p_tessAPI -> ClearAdaptiveClassifier();
}


void TessProxy::setImage(const unsigned char* data,
                         int bytesPerPixel,
                         int bytesPerLine,
                         int width,
                         int height) {
  p_tessAPI -> SetImage(data, width, height, bytesPerPixel, bytesPerLine);
}


void TessProxy::setImage(Image* img) {
  p_tessAPI -> SetImage((const unsigned char*) img -> rawData(),
                        img -> width(),
                        img -> height(),
                        img -> bytesPerPixel(),
                        img -> bytesPerLine());
}

void TessProxy::setRectangle(int left, int top, int width, int height) {
  p_tessAPI -> SetRectangle(left, top, width, height);
}

char* TessProxy::getText() {
  return p_tessAPI -> GetUTF8Text();
}

void TessProxy::clear() {
  p_tessAPI -> Clear();
}

void TessProxy::end() {
  p_tessAPI -> End();
}
