hacktues: src/main.cpp
	g++ -Wall -o $@ $< $(shell pkg-config --cflags --libs SDL2) -lopengl32 -mwindows
