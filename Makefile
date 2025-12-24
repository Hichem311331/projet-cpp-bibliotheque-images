CXX = g++
CXXFLAGS = -std=c++11 -Wall -I/usr/include/opencv4 -I/usr/include/opencv2
LIBS= -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

all: main

main: src/main.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp -o main $(LIBS)

clean:
	rm -f main

test: main
	./main

.PHONY: all clean test
