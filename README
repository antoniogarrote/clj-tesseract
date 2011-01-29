# clj-tesseract

A Clojure wrapper for the Tesseract OCR software.

## Installation

 1. Install OpenCV and Tesseract for you target platform

    In OSX this can be accomplished using MacPorts.

 2. Install Nakkaya's Vision library for Clojure

    Instructions can be found here: http://nakkaya.com/vision.html
    You need to copy the Vision .jar file to the clj-tesseract project
    lib directory.

 3. Compile clj-tesseract native shared library.

    $ cd microcr && make
    $ sudo cp libmicrocr.dylib /usr/local/lib/libmicrocr.dylib

 4. Compile clj-tesseract classes

    $ lein compile

 5. Run the tests to check that everything is ok

   $ lein test

 6. Fire swank/SLIME

    $ lein swank


## Usage

;; Load the library
(use 'clj-tesseract.core)

;; Load vision
(use 'vision.core)

;; Start tesseract

(def *api* (make-tesseract "/tmp"))

;; Retrieve an image from the
;; the standard webcam

(def *capture* (capture-from-cam 0))
(def *frame* (query-frame *capture*))

;; try capture

(def *text* (capture *api* *frame*))
(println (str "Captured: " *text*))

;; release resources

(clear *api*)
(release *capture*)

;; load image from file

(def *img* (load-image "./test/adam.png" :grayscale))
(view :test *img*) ; show the image in a Frame

;; try capture and clear

(println (str "Captured:"  (capture *api* *img*)))
(clear *api*)

;; release Tesseract

(end *api*)


## License

Copyright (C) 2010 Antonio Garrote

Distributed under the Eclipse Public License, the same as Clojure.
