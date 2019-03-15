#include <SDL.h>
#include <stdio.h>
#include <GL/gl.h>

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow(
                             "SDL2/OpenGL Demo", 30, 30, 640, 480,
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
    float sp = 0.00015;
    while (1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                return 1;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'd')
            {
                left = true;
            }
            if (event.type == SDL_KEYUP && event.key.keysym.sym == 'd')
            {
                left = false;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'a')
            {
                right = true;
            }
            if (event.type == SDL_KEYUP && event.key.keysym.sym == 'a')
            {
                right = false;
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

        if (left == true){
            x += sp;
            if (x > 0.7){
                x = 0.7;
            }
        }
        if (right == true){
            x -= sp;
            if (x < -0.7){
                x = -0.7;
            }
        }
        if (up == true){
            y += sp;
            if (y > 0.6){
                y = 0.6;
            }
        }
        if (down == true){
            y -= sp;
            if (y < -0.8){
                y = -0.8;
            }
        }
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
        glVertex2f(x+0.3,y-0.2);
        glVertex2f(x-0.3,y-0.2);
        glVertex2f(x,y+0.4);
        glEnd();

        SDL_GL_SwapWindow(window);
    }
    SDL_Quit();
    return 0;
}
