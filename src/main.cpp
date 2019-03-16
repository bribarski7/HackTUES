#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <GL/gl.h>
#include <cmath>
#include <assert.h>

using namespace std;


void krasota(float a,float b,float r){
    glBegin(GL_TRIANGLES);
    for(float i=0;i<=6.28;i+=0.1){
        glBegin(GL_TRIANGLES);
        glVertex2f(a+cos(i)*r,b+sin(i)*r);
        glVertex2f(a+cos(i)*r,a+0.01);
        glVertex2f(b+0.01,b+sin(i)*r);
        glEnd();
    }
}

float window_w=1366;
float window_h=768;

void circle(float x,float y,float r){
    int n=32;
    float step=M_PI/(n/2);
    glBegin(GL_TRIANGLES);
    for(int i=0;i<n;i++){
        float a=step*i;
        float a2=step*(i+1);
        glBegin(GL_TRIANGLES);
        glVertex2f(x+cos(a)*r,y+sin(a)*r*(window_w/window_h));
        glVertex2f(x+cos(a2)*r,y+sin(a2)*r*(window_w/window_h));
        glVertex2f(x,y);
        glEnd();
    }
}

void rectangle(float x,float y,float w,float h){
    w /= 2;
    h /= 2;
    h*=(window_w/window_h);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(x - w, (y - h));
    glVertex2f(x - w, (y + h));
    glVertex2f(x + w, (y - h));
    glVertex2f(x + w, (y + h));
    glEnd();
}

void load_image(const char *filepath){
    SDL_Surface *image = IMG_Load (filepath);
    assert(image);
    //cout<<image->format->format<<endl;
    //cout<<SDL_PIXELFORMAT_RGBA8888<<endl;
    //assert(image->format->format==SDL_PIXELFORMAT_RGBA8888);

    GLuint texture_id;
    glGenTextures(1,&texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image->w, image->h,0,GL_RGBA,GL_UNSIGNED_BYTE,image->pixels);
    SDL_FreeSurface(image);
}

float abs(float a,float b){
    if(a > b){
        return a-b;
    }
    else{
        return b-a;
    }
}

void show_symbol(char c, float x, float y, float h){
    float tw = 95*6;
    h /= 2;
    float w = 5 / 10.0 * h;
    int n=(c-32)*6;
    h*=(window_w/window_h);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(n/tw,1);
    glVertex2f(x - w, (y - h));
    glTexCoord2f(n/tw,0);
    glVertex2f(x - w, (y + h));
    glTexCoord2f((n+6)/tw,1);
    glVertex2f(x + w, (y - h));
    glTexCoord2f((n+6)/tw,0);
    glVertex2f(x + w, (y + h));
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void show_text(string text, float x, float y, float h){
    float w = 3.0 / 5 * h;
    for(size_t i=0;i<text.size();i++){
        show_symbol(text[i], x+i*w, y, h);
    }
}

void show_text_centered(string text, float x, float y, float h){
    float w = 3.0 / 5 * h;
    x -= text.size()*w/2;
    for(size_t i=0;i<text.size();i++){
        show_symbol(text[i], x+i*w, y, h);
    }
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow(
        "SDL2/OpenGL Demo", 0, 30, window_w, window_h,
        SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE|SDL_WINDOW_FULLSCREEN);

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

    while (1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                return 1;
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
        if(abs(x,x1)<r+w/2 && abs(y,y1)<r+w/2){
            break;
        }
        glClear(GL_COLOR_BUFFER_BIT);
        rectangle(x1, y1, w, h);
        circle(x,y,r);
        show_text_centered("~daskalo~", 0, 0, 0.03);
        show_text("PL1", x, y,0.03);
        show_text("PL2",x1,y1,0.03);
        SDL_GL_SwapWindow(window);
    }
    SDL_Quit();
    return 0;
}
