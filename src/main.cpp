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

#define P1X -200
#define P1Y  200
#define P2X  200
#define P2Y -200
#define GAME_WIDTH  500
#define GAME_HEIGHT 500

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

void set_matrix(){
    float w = 2 / window_w;
    float h = 2 / window_h;

    float matrix[16]={
        w,0,0,0,
        0,h,0,0,
        0,0,1,0,
        0,0,0,1,
    };
    glLoadMatrixf(matrix);

}

int main(int argc, char* argv[]) {
    vector<Category> cats = load_questions();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow(
        "Catch me", 0, 30, window_w, window_h,
        SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE|SDL_WINDOW_FULLSCREEN_DESKTOP);

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

    set_matrix();

    float w=40;
    float h=40;
    float x = P1X;
    float y = P1Y;
    float r = 20;
    float sp = 0.1;
    float x1 = P2X;
    float y1 = P2Y;
    int score_circle = 0;
    int score_square = 0;

    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;

    bool left1 = false;
    bool right1 = false;
    bool up1 = false;
    bool down1 = false;

    int answer = 0;
    bool showq = false;
    Question question;
    string answers[3];

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
                set_matrix();
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == '\e'){ // \e == escape
                return 0;
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
                answer = 1;
            }
            if (event.type == SDL_KEYUP && event.key.keysym.sym == 'b'){
                answer = 2;
            }
            if (event.type == SDL_KEYUP && event.key.keysym.sym == 'c'){
                answer = 3;
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
                if (x < -GAME_WIDTH/2 + r){
                    x = -GAME_WIDTH/2 + r;
                }
            }
            if (right){
                x += sp;
                if (x > GAME_WIDTH/2 - r){
                    x = GAME_WIDTH/2 - r;
                }
            }
            if (up == true){
                y += sp;
                if (y > GAME_HEIGHT/2 - r){
                    y = GAME_HEIGHT/2 - r;
                }
            }
            if (down == true){
                y -= sp;
                if (y < -GAME_HEIGHT/2 + r){
                    y = -GAME_HEIGHT/2 + r;
                }
            }

            if (left1 == true){
                x1 -= sp;
                if (x1 < -GAME_WIDTH/2 + w/2){
                    x1 = -GAME_WIDTH/2 + w/2;
                }
            }
            if (right1 == true){
                x1 += sp;
                if (x1 > GAME_WIDTH/2 - w/2){
                    x1 = GAME_WIDTH/2 - w/2;
                }
            }
            if (up1 == true){
                y1 += sp;
                if (y1 > GAME_HEIGHT/2 - w/2){
                    y1 = GAME_HEIGHT/2 - w/2;
                }
            }
            if (down1 == true){
                y1 -= sp;
                if (y1 < -GAME_HEIGHT/2 + w/2){
                    y1 = -GAME_HEIGHT/2 + w/2;
                }
            }
			if(abs(x,x1)<r+w/2 && abs(y,y1)<r+w/2){
				showq = true;
				question = getRandomQuestion(cats);

                answers[0]=question.answers[0];
                answers[1]=question.answers[1];
                answers[2]=question.answers[2];
                for(int i=0;i<3;i++){
                    int r = rand()%3;
                    string swaps = answers[i];
                    answers[i]=answers[r];
                    answers[r]=swaps;
                }

				answer=0;
				x=P1X;
				y=P1Y;
				x1=P2X;
				y1=P2Y;
			}
		}

        glClear(GL_COLOR_BUFFER_BIT);

        if (showq){
            show_question(question, answers);
            if(answer==1){
                if(answers[0]==question.answers[0]){
                    score_circle++;
                }
                showq=false;
            }
            else if(answer==2){
                if(answers[1]==question.answers[0]){
                    score_circle++;
                }
                showq=false;
            }
            else if(answer==3){
                if(answers[2]==question.answers[0]){
                    score_circle++;
                }
                showq=false;
            }
        }
        else{
            glColor3f(1,0.1,0.1);
            rectangle(x1, y1, w, h);
            glColor3f(1,1,1);
            circle(x,y,r);
            show_text_centered("P1",  x,  y, 1);
            show_text_centered("P2", x1, y1, 1);
        }

        show_text_centered(to_string(score_circle),-GAME_WIDTH/2, 0, 2);
        show_text_centered(to_string(score_square), GAME_WIDTH/2, 0, 2);

        SDL_GL_SwapWindow(window);
    }
    SDL_Quit();
    return 0;
}
