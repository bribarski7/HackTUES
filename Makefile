hacktues: src/main.cpp src/Questions.cpp src/Grafika.cpp
	g++ -Wall -o $@ $< $(shell pkg-config --cflags --libs SDL2 SDL2_image) -lopengl32 -mwindows
