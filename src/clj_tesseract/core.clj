(ns clj-tesseract.core
  (:import [com.sun.jna Native]
           (com.sun.jna Function Pointer)
           (com.sun.jna.ptr ByReference IntByReference FloatByReference)
           (java.awt.image BufferedImage ColorModel Raster DataBufferInt))
  (:use [vision.core]))

(def *tesseract-api* (Native/loadLibrary "microcr" jna.tesseract_api))

(defn make-tesseract
  "Starts tesseract, a data path and an optional language can be passed as arguments.
   The lang parameter will be used to access the lang training data from the system
   tesseract setup."
  ([path]
     (.tessproxy_initialize *tesseract-api* path))
  ([path lang]
     (.tessproxy_initialize *tesseract-api* path lang)))


(defn to-grayscale
  "Transforms an image to grayscale using OpenCV"
  ([image]
     (condp = (:color-space image)
         :bgr (convert-color image :bgr-gray)
         :grayscale image
         :hsv (-> image
                  (convert-color :hsv-bgr)
                  (convert-color :bgr-gray))
         (throw (Exception. (str "Cannot convert " (:color-space image) " color space to grayscale"))))))

(defn preprocess-image
  "Converts into grayscale and applies a default or provided threshold"
  ([image]
     (preprocess-image image 111))
  ([image thresh]
     (threshold (to-grayscale image) thresh :binary)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; These functions have been extracted from vision.core

(defmacro call [f arg & args]
  (if (empty? args)
    `(.invoke (Function/getFunction "vision" (name ~f)) (to-array ~arg))
    `(.invoke (Function/getFunction "vision" (name ~f)) ~arg (to-array ~@args))))

(defmacro with-pointer
  [binding & body]
  {:pre [(vector? binding) (= 2 (count binding))]}
  `(if-let [ref# ~(second binding)]
     (try
       (let [~(first binding) (.getPointer ref#)]
         ~@body)
       (finally
        (release ref#)))))

(defn pixels [image]
  (let [p (:pointer image)
        cs (:color-space image)
        t (cond (= cs :bgr) 1
                (= cs :binary) 2
                (= cs :hsv) 3
                (= cs :rgb) 4
                (= cs :grayscale) 5)]
    (with-pointer [ptr (call :pixels IntByReference [p t])]
      (let [[width height] (image-size p)]
        (.getIntArray ptr 0 (* width height))))))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defn width [image]
  "Returns the width of an image in px"
  (first (image-size image)))

(defn height [image]
  "Returns the height of an image in px"
  (second (image-size image)))


(defn bytes-per-pixel [image]
  "Number of bytes per pixel"
  (.tessproxy_bytes_per_pixel *tesseract-api* (:pointer image)))


(defn bytes-per-line [image]
  "Number of bytes per image line"
  (.tessproxy_bytes_per_line *tesseract-api* (:pointer image)))


(defn capture-no-preprocess [proxy image]
  "Tries to extract text from an image without preprocessing the image"
  (let [pxs (:pointer image)
        per-pixel (bytes-per-pixel image)
        per-line (bytes-per-line image)
        w (width image)
        h (height image)]
    (.getString (.tessproxy_capture *tesseract-api*
                                    proxy
                                    pxs
                                    per-pixel
                                    per-line
                                    0
                                    0
                                    w
                                    h)
                0)))

(defn capture [proxy image]
  "Tries to extract text from an image applying a standard transformation:
   grayscale -> threshold"
  (let [image (preprocess-image image)]
    (capture-no-preprocess proxy image)))


(defn clear
  "Clears memory in the Tesseract API instance, the instance is still valid for
   further use"
  ([proxy]
     (.tessproxy_clear *tesseract-api* proxy)))

(defn end
  "Releases all memory associated to the Tesseract API instance. The instance
   cannot be longer used"
  ([proxy]
     (.tessproxy_end *tesseract-api* proxy)))

(defn set-image-no-preprocess
  "Sets the image that will be used by the Tesseract API without any furter
   preprocessing"
  ([proxy image]
     (let [pxs (:pointer image)
           per-pixel (bytes-per-pixel image)
           per-line (bytes-per-line image)
           w (width image)
           h (height image)]
       (.tessproxy_set_image *tesseract-api* proxy pxs per-pixel per-line w h))))

(defn set-image
  "Sets the image to be used by the Tesseract API and applies a standard
   transformation: grayscale -> threshold"
  [proxy image]
  (let [image (preprocess-image image)]
    (set-image-no-preprocess proxy image)))

(defn set-rectangle
  "Sets the boundaries of a rectangle where text capture will be attempted"
  ([proxy left top width height]
     (.tessproxy_set_image *tesseract-api* proxy left top width height)))

(defn get-text
  "Retrieves the captured text by the Tesseract API instance"
  ([proxy]
     (.tessproxy_get_text *tesseract-api* proxy)))
