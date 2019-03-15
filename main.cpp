#include <SDL.h>
#include <stdio.h>
#include <GL/gl.h>
#include <math.h>

void krasota(float a,float b){
    glBegin(GL_TRIANGLES);
    for(float i=0;i<=6.28;i+=0.1){
        glBegin(GL_TRIANGLES);
        glVertex2f(a+cos(i)*0.5,b+sin(i)*0.5);
        glVertex2f(a+cos(i)*0.5,a+0.01);
        glVertex2f(b+0.01,b+sin(i)*0.5);
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

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow(
        "SDL2/OpenGL Demo", 60, 60, 480, 480,
        SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
        SDL_GL_CreateContext(window);
    glClearColor(0,0,1,1);
    if (window == NULL)
    {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
    float x = 0;
    float y = 0;
    float r = 0.15;
    float sp = 0.000175;
    while (1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                return 1;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'd')
            {
                right = true;
            }
            if (event.type == SDL_KEYUP && event.key.keysym.sym == 'd')
            {
                right = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'a')
            {
                left = true;
            }
            if (event.type == SDL_KEYUP && event.key.keysym.sym == 'a')
            {
                left = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'w')
            {
                up = true;
            }
            if (event.type == SDL_KEYUP && event.key.keysym.sym == 'w')
            {
                up = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == 's')
            {
                down = true;
            }
            if (event.type == SDL_KEYUP && event.key.keysym.sym == 's')
            {
                down = false;
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
            if (y > 1 - r){
                y = 1 - r;
            }
        }
        if (down == true){
            y -= sp;
            if (y < -1 + r){
                y = -1 + r;
            }
        }
        glClear(GL_COLOR_BUFFER_BIT);

        circle(x,y,r);
        SDL_GL_SwapWindow(window);
    }
    SDL_Quit();
    return 0;
}
