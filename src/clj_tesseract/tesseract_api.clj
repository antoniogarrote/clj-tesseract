(ns clj-tesseract.tesseract-api)

(gen-interface
 :name jna.tesseract_api
 :extends [com.sun.jna.Library]
 :methods [[tessproxy_initialize [String] com.sun.jna.Pointer]
           [tessproxy_initialize_with_lang [String String] com.sun.jna.Pointer]
           [tessproxy_capture [com.sun.jna.Pointer com.sun.jna.Pointer int int int int int int] com.sun.jna.Pointer]
           [tessproxy_bytes_per_pixel [com.sun.jna.Pointer] int]
           [tessproxy_bytes_per_line [com.sun.jna.Pointer] int]
           [tessproxy_set_image [com.sun.jna.Pointer com.sun.jna.Pointer int int int int] void]
           [tessproxy_set_rectangle [com.sun.jna.Pointer int int int int] void]
           [tessproxy_clear [com.sun.jna.Pointer] void]
           [tessproxy_end [com.sun.jna.Pointer] void]
           [tessproxy_get_text [com.sun.jna.Pointer] String]])
