build:
	g++ -I./common/ -std=c++17 main.cpp common/vec3.cpp common/color.cpp
	./a.out > image.ppm