#ifndef __C_TESSERACT_API_C__
#define __C_TESSERACT_API_C__

#include "tesseract_proxy.h"
#include "camera.h"
#include "image.h"

extern "C" {
  TessProxy* tessproxy_initialize(char* dataPath) {
    string dpath = string(dataPath);
    TessProxy* proxy = new TessProxy(dpath);

    return proxy;
  }

  TessProxy* tessproxy_initialize_with_lang(char* dataPath, char* lang) {
    string dpath = string(dataPath);
    string dlang = string(lang);
    TessProxy* proxy = new TessProxy(dpath,lang);

    return proxy;
  }

  char* tessproxy_capture(TessProxy* proxy, IplImage* p_img, int bytesPerPixel, int bytesPerLine, int left, int top, int width, int height) {
    char* result = proxy -> captureImage((const unsigned char*) p_img -> imageData,
                                         bytesPerPixel, bytesPerLine, left, top, width, height);
    return result;
  }

  int tessproxy_bytes_per_pixel(IplImage* p_img) {
    Image* img = new Image(p_img);
    return img -> bytesPerPixel();
  }

  int tessproxy_bytes_per_line(IplImage* p_img) {
    Image* img = new Image(p_img);
    return img -> bytesPerLine();
  }

  void tessproxy_set_image(TessProxy* proxy, IplImage* p_img, int bytesPerPixel, int bytesPerLine, int width, int height) {
    proxy -> setImage((const unsigned char*) p_img -> imageData,
                      bytesPerPixel, bytesPerLine, width, height);
  }

  void tessproxy_set_rectangle(TessProxy* proxy, int left, int top, int width, int height) {
    proxy -> setRectangle(left, top, width, height);
  }

  void tessproxy_clear(TessProxy* proxy) {
    proxy -> clear();
  }

  void tessproxy_end(TessProxy* proxy) {
    proxy -> end();
    delete proxy;
  }

  char* tessproxy_get_text(TessProxy* proxy) {
    return proxy -> getText();
  }

}
#endif // __C_TESSERACT_API_C__
