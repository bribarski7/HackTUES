hacktues: src/main.cpp src/Questions.cpp src/Grafika.cpp Catch_me.res
	g++ -Wall -o $@ $< Catch_me.res $(shell pkg-config --cflags --libs SDL2 SDL2_image) -lopengl32 -mwindows

Catch_me.res: res/Catch_me.rc res/Catch_me.ico
	windres $< -O coff -o $@