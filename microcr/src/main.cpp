#include <stdio.h>
#include <iostream>

#include "camera.h"
#include "utils.h"
#include "image.h"
#include "tesseract_proxy.h"

using namespace std;

int main(int argc, char** argv) {

  // Capture an image from camera and
  // attempts OCR after transformation


  Camera* camera = new Camera();
  Window* win = new Window((char*)"test image");
  string response;
  Image* img;

  bool shouldContinue = true;

  while(shouldContinue) {
    cout << "Taking a picture when striking a key to continue..." << endl;
    cin >> response;
    camera -> takeSnapshot();

    cout << "Showing the picture, strike a key to continue..." << endl;
    img = camera -> getImage();
    win -> showImage(img);

    cout << "Is the picture ok (y/n) ? " << endl;
    cin >> response;
    cout << "[response " << response  << "]" << endl;
    if(response.compare("y") == 0) {
      shouldContinue = false;
    }

    win -> closeWindow();
  }

  win = new Window((char*)"gray  image");
  cout << "Showing the picture in grayscale, strike a key over the window to continue..." << endl;
  Image* grayImg = img -> toGrayScale();
  win -> showImage(grayImg);
  Window::waitForKey();
  win -> closeWindow();

  //  Image* thrImg = grayImg -> optimizeThreshold();
  Image* thrImg = grayImg -> threshold(61);
  win -> closeWindow();
  win -> showImage(thrImg);
  cout << "Showing the picture in grayscale, strike a key over the window to continue..." << endl;
  Window::waitForKey();

  TessProxy* ocr = new TessProxy("/tmp");
  char* result = ocr -> captureImage(thrImg);

  cout << "result: " << string(result);


  // Read Image from file and attempts OCR
  /*
  Window* win = new Window((char*)"test image");
  string input;

  string filename = string(argv[1]);
  Image* img = Image::loadImage(filename) -> threshold();

  cout << "Showing read image, press key to continue..." << endl;
  win -> showImage(img);
  cin >> input;

  cout << "Attempting OCR..." << endl;
  TessProxy* ocr = new TessProxy("/tmp");
  char* result = ocr -> captureImage(img);
  cout << "result: " << string(result);

  cout << "testing contours" << endl;
  img -> drawContours();
  */
  return 0;
}
