#include "image.h"

Image::Image(IplImage* p_img) {
  this -> p_img = p_img;
}

Image::~Image() {
  // nothing yet
}

Image* Image::toGrayScale() {
  Image* other = this -> cloneEmpty();
  cvCvtColor(p_img,
             other -> toIplImage(),
             CV_RGB2GRAY);

  return other;
}

Image* Image::threshold(int degree=3) {
  Image* other = this -> cloneEmpty();
  cvAdaptiveThreshold(p_img,
                      other -> toIplImage(),
                      255, //double maxValue,
                      CV_ADAPTIVE_THRESH_MEAN_C,
                      CV_THRESH_BINARY,
                      degree,
                      0);
  return other;
}

IplImage* Image::toIplImage() {
  return this -> p_img;
}

Image* Image::optimizeThreshold() {
  int degree = 3;
  Image* tmp = this -> threshold(degree);
  Image* old = tmp;
  int oldCount = tmp -> numberContours();
  float variation = 100;
  int iteration = 1;

  while(variation > 50.0 || iteration < 9) {
    printf("%d) degree: %d -> counturs %d",iteration, degree, oldCount);
    iteration++;
    degree = (degree * 2) + 1;

    tmp = this -> threshold(degree);
    int newCount = tmp -> numberContours();

    if (newCount <= oldCount) {
      break;
    } else {
      delete old;
      variation = (newCount * 100 / oldCount) - 100.0;
      old = tmp;
    }
  }

  return old;
}

Image* Image::cloneEmpty() {
  int width = this -> p_img -> width;
  int height = this -> p_img -> height;
  int depth = this -> p_img -> depth;
  int nChannels = this -> p_img -> nChannels;

  IplImage* nImage = cvCreateImage(cvSize(width,height),
                                   depth,
                                   1);

  Image* cloned = new Image(nImage);
  return cloned;
}

Image* Image::loadImage(string filePath) {
  IplImage* loaded = cvLoadImage(filePath.c_str(),
                                 CV_LOAD_IMAGE_GRAYSCALE);

  return new Image(loaded);
}

char* Image::rawData() {
  return this -> p_img -> imageData;
}

int Image::width() {
  return this -> p_img -> width;
}

int Image::height() {
  return this -> p_img -> height;
}

int Image::bytesPerPixel() {
  int nbytes = 0;
  switch(this -> p_img -> depth) {
    case IPL_DEPTH_8U: nbytes = 1; break;
    case IPL_DEPTH_8S: nbytes = 1; break;
    case IPL_DEPTH_16U: nbytes = 2; break;
    case IPL_DEPTH_16S: nbytes = 2; break;
    case IPL_DEPTH_32S: nbytes = 4; break;
    case IPL_DEPTH_32F: nbytes = 4; break;
    case IPL_DEPTH_64F: nbytes = 8; break;
  }

  return nbytes;
}

void Image::drawContours() {
  IplImage* src = this -> toIplImage();
  IplImage* dst =  this -> cloneEmpty() -> toIplImage();

  CvMemStorage* storage = cvCreateMemStorage(0);
  CvSeq* contour = 0;

  cvThreshold( src, src, 1, 255, CV_THRESH_BINARY );

  cvNamedWindow( "Source", 1 );
  cvShowImage( "Source", src );
  
  cvFindContours( src, storage, &contour, sizeof(CvContour),
                  CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

  cvZero( dst );

  for( ; contour != 0; contour = contour->h_next ) 
    {
      CvScalar color = CV_RGB( rand()&255, rand()&255, rand()&255 );
      /* replace CV_FILLED with 1 to see the outlines */
      cvDrawContours( dst, contour, color, color, -1, CV_FILLED, 8 );
    }
  cvNamedWindow( "Components", 1 );
  cvShowImage( "Components", dst );
  cvWaitKey(0);  
}

int Image::numberContours() {
  IplImage* src = this -> toIplImage();
  IplImage* dst =  this -> cloneEmpty() -> toIplImage();

  CvMemStorage* storage = cvCreateMemStorage(0);
  CvSeq* contour = 0;

  cvFindContours(src, 
                 storage, 
                 &contour, 
                 sizeof(CvContour),
                 CV_RETR_CCOMP, 
                 CV_CHAIN_APPROX_SIMPLE);

  int numContours = cvSliceLength(CV_WHOLE_SEQ, contour);
  

  //  delete contour;
  
  return numContours;
}

int Image::bytesPerLine() {
  return this -> p_img -> widthStep;
}
