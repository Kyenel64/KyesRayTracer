build:
	g++ -I./Classes/ -I./vendor/ -g -Wall -std=c++17 main.cpp Classes/*.cpp -o bin/app
	bin/app.out