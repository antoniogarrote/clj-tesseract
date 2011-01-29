(defproject clj-tesseract "1.0.0-SNAPSHOT"
  :description "Cojure wrapper for the Tesseract OCR software"
  :dependencies [[org.clojure/clojure "1.2.0"]
                 [org.clojure/clojure-contrib "1.2.0"]
                 [clj-native "0.9.1-SNAPSHOT"]]
  :jvm-opts ["-Djna.library.path=/usr/local/lib"]
  :native-path "/usr/local/lib:/opt/local/lib:/usr/lib"
  :aot [clj-tesseract.tesseract-api]
  :dev-dependencies [[leiningen/lein-swank "1.2.0-SNAPSHOT"]
                     [cdt "1.2"]])
