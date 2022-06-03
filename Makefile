build:
	g++ -I./Classes/ -std=c++17 main.cpp Classes/*.cpp
	./a.out > image.ppm