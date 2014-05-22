INCLUDES = -I/usr/local/Cellar/tesseract/3.00/include/tesseract `pkg-config --cflags opencv`
LIBS = -L/usr/local/Cellar/tesseract/3.00/lib -ltesseract_api `pkg-config --libs opencv`
DYLIB = -arch x86_64 -dynamiclib -o libmicrocr.dylib
INSTALL_PATH = -install_name /usr/local/lib/microcr/libmicrocr.dylib
CC = g++

all: libmicrocr microcr clean_obj

libmicrocr: tesseract_api.o
	$(CC) $(DYLIB) tesseract_api.o image.o utils.o tesseract_proxy.o $(INSTALL_PATH) $(LIBS)

microcr: main.o camera.o
	$(CC) tesseract_api.o main.o camera.o image.o utils.o tesseract_proxy.o -o microcr $(LIBS)

main.o:  tesseract_api.o
	$(CC) $(INCLUDES) -c src/main.cpp

tesseract_api.o: utils.o image.o tesseract_proxy.o
	$(CC) $(INCLUDES) -c src/tesseract_api.cpp

camera.o:
	$(CC) $(INCLUDES) -c src/camera.cpp

image.o:
	$(CC) $(INCLUDES) -c src/image.cpp

utils.o:
	$(CC) $(INCLUDES) -c src/utils.cpp

tesseract_proxy.o:
	$(CC) $(INCLUDES) -c src/tesseract_proxy.cpp

clean_obj:
	rm -rf *.o

clean: clean_obj
	rm -rf microcr *.dylib *.so
