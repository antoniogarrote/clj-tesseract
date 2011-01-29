(ns clj-tesseract.test.core
  (:use [clj-tesseract.core] :reload)
  (:use [clojure.test])
  (:use [vision.core]))

(deftest should-recognize-a-simple-test
  (let [api (make-tesseract "./tmp")
        img (load-image (.getAbsolutePath (java.io.File. "./test/adam.png")) :grayscale)]
    (is (= "Adam\n\n" (capture api img)))
    (clear api)
    (is (= "Adam\n\n" (capture api img)))
    (end api)))


(deftest should-recognize-return-text
  (let [api (make-tesseract "./tmp")
        img (load-image (.getAbsolutePath (java.io.File. "./test/adam.png")) :grayscale)
        _ (set-image api img)]
    (is (= "Adam\n\n" (get-text api)))
    (end api)))
