#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <time.h>
#include <GL/gl.h>
#include <cmath>
#include <assert.h>
using namespace std;

float window_w=640;
float window_h=480;

#include "Questions.cpp"
#include "Grafika.cpp"


float abs(float a,float b){
    if(a > b){
        return a-b;
    }
    else{
        return b-a;
    }
}

int main(int argc, char* argv[]) {
    vector<Category> cats = load_questions();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow(
        "Catch me", 0, 30, window_w, window_h,
        SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);

    if (window == NULL)
    {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    SDL_GL_CreateContext(window);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0,0.9,0.3,1);
    load_image("res/ASCIIforHACKTUES.png");

    float w=0.04;
    float h=0.04;
    float x = -0.978;
    float y = 0.964;
    float r = 0.02;
    float sp = 0.0005;

    float x1 = 0.978;
    float y1 = -0.964;

    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;

    bool left1 = false;
    bool right1 = false;
    bool up1 = false;
    bool down1 = false;

    bool showq = false;
    Question question;

    while (1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                return 1;

            if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
                window_w = event.window.data1;
                window_h = event.window.data2;
                glViewport(0,0,window_w,window_h);
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'd'){
                right = true;
            }
            if (event.type == SDL_KEYUP && event.key.keysym.sym == 'd'){
                right = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'a'){
                left = true;
            }
            if (event.type == SDL_KEYUP && event.key.keysym.sym == 'a'){
                left = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'w'){
                up = true;
            }
            if (event.type == SDL_KEYUP && event.key.keysym.sym == 'w'){
                up = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == 's'){
                down = true;
            }
            if (event.type == SDL_KEYUP && event.key.keysym.sym == 's'){
                down = false;
            }


            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'l'){
                right1 = true;
            }
            if (event.type == SDL_KEYUP && event.key.keysym.sym == 'l'){
                right1 = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'j'){
                left1 = true;
            }
            if (event.type == SDL_KEYUP && event.key.keysym.sym == 'j'){
                left1 = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'i'){
                up1 = true;
            }
            if (event.type == SDL_KEYUP && event.key.keysym.sym == 'i'){
                up1 = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'k'){
                down1 = true;
            }
            if (event.type == SDL_KEYUP && event.key.keysym.sym == 'k'){
                down1 = false;
            }
        }

        if (!showq){
            if (left){
                x -= sp;
                if (x < -1 + r){
                    x = -1 + r;
                }
            }
            if (right){
                x += sp;
                if (x > 1 - r){
                    x = 1 - r;
                }
            }
            if (up == true){
                y += sp;
                if (y > 1 - 2*r){
                    y = 1 - 2*r;
                }
            }
            if (down == true){
                y -= sp;
                if (y < -1 + 2*r){
                    y = -1 + 2*r;
                }
            }

            if (left1 == true){
                x1 -= sp;
                if (x1 < -1 + w/2){
                    x1 = -1 + w/2;
                }
            }
            if (right1 == true){
                x1 += sp;
                if (x1 > 1 - w/2){
                    x1 = 1 - w/2;
                }
            }
            if (up1 == true){
                y1 += sp;
                if (y1 > 1 - w){
                    y1 = 1 - w;
                }
            }
            if (down1 == true){
                y1 -= sp;
                if (y1 < -1 + w){
                    y1 = -1 + w;
                }
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        if(abs(x,x1)<r+w/2 && abs(y,y1)<r+w/2){
            showq = true;
            question = cats[0].packs[0].questions[0];
        }

        if (showq){
            show_question(question);
        }

        rectangle(x1, y1, w, h);
        circle(x,y,r);
        show_text_centered("P1",  x,  y, 1);
        show_text_centered("P2", x1, y1, 1);
        SDL_GL_SwapWindow(window);
    }
    SDL_Quit();
    return 0;
}
