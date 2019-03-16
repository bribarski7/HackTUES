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
#define GAME_WIDTH  700
#define GAME_HEIGHT 700

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
    float p1_x = P1X;
    float p1_y = P1Y;
    float r = 20;
    float sp = 500;
    float p2_x = P2X;
    float p2_y = P2Y;
    int score_p1 = 0;
    int score_p2 = 0;

    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;

    bool left1 = false;
    bool right1 = false;
    bool up1 = false;
    bool down1 = false;

    bool p2_goni = true;

    int answer = 0;
    bool showq = false;
    Question question;
    string answers[3];

    Uint32 last_time = SDL_GetTicks ();

    while (1)
    {
        Uint32 current_time = SDL_GetTicks ();
        double dt = (current_time - last_time) / 1000.0;
        last_time = current_time;

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
            }
            if (event.type == SDL_KEYUP && event.key.keysym.sym == '1'){
                answer = 2;
            }
            if (event.type == SDL_KEYUP && event.key.keysym.sym == '2'){
                answer = 2;
            }
            if (event.type == SDL_KEYUP && event.key.keysym.sym == '3'){
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
                p1_x -= sp * dt;
                if (p1_x < -GAME_WIDTH/2 + r){
                    p1_x = -GAME_WIDTH/2 + r;
                }
            }
            if (right){
                p1_x += sp * dt;
                if (p1_x > GAME_WIDTH/2 - r){
                    p1_x = GAME_WIDTH/2 - r;
                }
            }
            if (up == true){
                p1_y += sp * dt;
                if (p1_y > GAME_HEIGHT/2 - r){
                    p1_y = GAME_HEIGHT/2 - r;
                }
            }
            if (down == true){
                p1_y -= sp * dt;
                if (p1_y < -GAME_HEIGHT/2 + r){
                    p1_y = -GAME_HEIGHT/2 + r;
                }
            }

            if (left1 == true){
                p2_x -= sp * dt;
                if (p2_x < -GAME_WIDTH/2 + w/2){
                    p2_x = -GAME_WIDTH/2 + w/2;
                }
            }
            if (right1 == true){
                p2_x += sp * dt;
                if (p2_x > GAME_WIDTH/2 - w/2){
                    p2_x = GAME_WIDTH/2 - w/2;
                }
            }
            if (up1 == true){
                p2_y += sp * dt;
                if (p2_y > GAME_HEIGHT/2 - w/2){
                    p2_y = GAME_HEIGHT/2 - w/2;
                }
            }
            if (down1 == true){
                p2_y -= sp * dt;
                if (p2_y < -GAME_HEIGHT/2 + w/2){
                    p2_y = -GAME_HEIGHT/2 + w/2;
                }
            }

			if(abs(p1_x,p2_x)<r+w/2 && abs(p1_y,p2_y)<r+w/2){
				showq = true;
				question = getRandomQuestion(cats);

				if(p2_goni){
                    score_p2++;
				}
				else{
                    score_p1++;
				}

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
				p1_x=P1X;
				p1_y=P1Y;
				p2_x=P2X;
				p2_y=P2Y;
			}
		}

        glClear(GL_COLOR_BUFFER_BIT);

        if (showq){
            show_question(question, answers);

            if (answer){
                if (answers[answer-1] == question.answers[0]){
                    if (p2_goni) {
                        score_p1++;
                    }
                    else {
                        score_p2++;
                    }
                }
                else {
                    if (p2_goni) {
                        score_p2++;
                    }
                    else {
                        score_p1++;
                    }
                }

                p2_goni = !p2_goni;
                showq=false;
            }
        }
        else{
            if(p2_goni){
                glColor3f(1,0.1,0.1);
                rectangle(p2_x, p2_y, w, h);
                glColor3f(1,1,1);
                circle(p1_x,p1_y,r);
            }
            else{
                glColor3f(1,0.1,0.1);
                circle(p1_x,p1_y,r);
                glColor3f(1,1,1);
                rectangle(p2_x, p2_y, w, h);
            }
            show_text_centered("P1", p1_x, p1_y, 1);
            show_text_centered("P2", p2_x, p2_y, 1);
        }

        show_text_centered(to_string(score_p1), P1X, 0, 2);
        show_text_centered(to_string(score_p2), P2X, 0, 2);

        SDL_GL_SwapWindow(window);
    }
    SDL_Quit();
    return 0;
}
