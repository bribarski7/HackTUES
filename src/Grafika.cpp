#define SYMBOL_W 6
#define SYMBOL_H 10

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

void rectangle(float x, float y, float w, float h){
    w /= 2;
    h /= 2;
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(x - w, y - h);
    glVertex2f(x - w, y + h);
    glVertex2f(x + w, y - h);
    glVertex2f(x + w, y + h);
    glEnd();
}

void show_symbol(char c, float x, float y, float h,float w){
    float tw = 95*6;
    h /= 2;
    w /= 2;
    int n=(c-32)*6;
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

void show_text(string text, float x, float y, int s){
    float h = s * 10;
    float w = s * 6;
    for(size_t i=0;i<text.size();i++){
        show_symbol(text[i], x+i*w, y, h,w);
    }
}

void show_text_centered(string text, float x, float y, int s){
    float h = s * 10.0;
    float w = s * 6.0;
    x -= (text.size() - 1) * w / 2;
    for(size_t i=0;i<text.size();i++){
        show_symbol(text[i], x+i*w, y, h,w);
    }
}

void show_text_centered_box (string text, float x, float y, int s) {
    int h_padding = 5*2;
    int v_padding = 4*2;
    int char_w = SYMBOL_W * s;
    int w = text.size() * char_w + h_padding;
    int h = SYMBOL_H * s + v_padding;
    rectangle(x, y, w, h);
    show_text_centered(text, x, y-s, s);
}

void show_question(Question q, string answers[3]){
    show_text_centered_box(q.question, 0, 200, 2);
    show_text_centered_box("1) " + answers[0], 0, 165, 2);
    show_text_centered_box("2) " + answers[1], 0, 130, 2);
    show_text_centered_box("3) " + answers[2], 0, 95, 2);
}
