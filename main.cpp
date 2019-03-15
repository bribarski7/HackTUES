#include <SDL.h>
#include <stdio.h>
#include <GL/gl.h>
#include <math.h>

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

void circle(float x,float y,float r){
    int n=32;
    float step=M_PI/(n/2);
    glBegin(GL_TRIANGLES);
    for(int i=0;i<n;i++){
        float a=step*i;
        float a2=step*(i+1);
        glBegin(GL_TRIANGLES);
        glVertex2f(x+cos(a)*r,y+sin(a)*r);
        glVertex2f(x+cos(a2)*r,y+sin(a2)*r);
        glVertex2f(x,y);
        glEnd();
    }
}

void rectangle(float x,float y,float w,float h){
    w /= 2;
    h /= 2;
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(x - w, y - h);
    glVertex2f(x - w, y + h);
    glVertex2f(x + w, y - h);
    glVertex2f(x + w, y + h);
    glEnd();
}



int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);SDL_Window *window = SDL_CreateWindow(
        "SDL2/OpenGL Demo", 30, 30, 480, 480,
        SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
        SDL_GL_CreateContext(window);
    glClearColor(0,0,1,1);
    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    float x=0;
    float y=0;
    float a=0.2;
    float b=0.2;
    float w=0.2;
    float h=0.3;
    while (1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
                if(event.type == SDL_QUIT)
                    return 1;
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'd'){
                    x+=0.01;
                }
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'a'){
                    x-=0.01;
                }
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'w'){
                    y+=0.01;
                }
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == 's'){
                    y-=0.01;
                }
        }
        glClear(GL_COLOR_BUFFER_BIT);

        float r=0.2;
        rectangle(x, y, w, h);
        //circle(x,y,r);
        SDL_GL_SwapWindow(window);
    }
    SDL_Quit();
    return 0;
}
