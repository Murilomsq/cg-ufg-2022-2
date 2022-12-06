#include <GL/glut.h>
#include <stdio.h>

#define SCREEN_WIDHT 1000
#define SCREEN_HEIGHT 1000

void writepixel(int x, int y, int r, int g, int b, int size);
void traceline(int x1, int y1, int x2, int y2, int r, int g, int b, int size);
void reshape (int w, int h);
void mouseCallback(int button, int state, int x, int y);
void tracelinecompleteY(int x1, int y1, int x2, int y2, int r, int g, int b, int size);
void tracelinecompleteX(int x1, int y1, int x2, int y2, int r, int g, int b, int size);


int w_size;
int h_size;

void init()
{
    glClearColor(0,0,0,0);
    glViewport(0,0,SCREEN_WIDHT,SCREEN_HEIGHT);
    gluOrtho2D(0.0,SCREEN_WIDHT,0,SCREEN_HEIGHT);//estabeleca a area de visualizacao
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}
int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(SCREEN_WIDHT,SCREEN_HEIGHT);
    glutInitWindowPosition(10,50);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("Transformacoes");
    init();
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseCallback);
    glutMainLoop();
}
void tracelinecompleteY(int x1, int y1, int x2, int y2, int r, int g, int b, int size){
    int dx, dy, incE, incNE, d, x, y;
    int yi = 1;

    dx = x2-x1;
    dy = y2-y1;

    if(dy < 0){
        yi = -1;
        dy = -dy;
    }

    d = 2 * dy - dx;
    incE = 2 * dy;
    incNE = 2 * (dy - dx);

    x = x1;
    y = y1;
    
    writepixel(x, y, r, g, b, size);

    while(x < x2){
        if(d <= 0){
            d = d + incE;
            x++;
        }
        else{
            d = d + incNE;
            x++;
            y += yi;
        }
        writepixel(x, y, r, g, b, size);
    }

}

void tracelinecompleteX(int x1, int y1, int x2, int y2, int r, int g, int b, int size){
    int dx, dy, incE, incNE, d, x, y;
    int xi = 1;

    dx = x2-x1;
    dy = y2-y1;

    if(dx < 0){
        xi = -1;
        dx = -dx;
    }

    d = 2 * dx - dy;
    incE = 2 * dx;
    incNE = 2 * (dx - dy);

    x = x1;
    y = y1;
    
    writepixel(x, y, r, g, b, size);

    while(y < y2){
        if(d <= 0){
            d = d + incE;
            y++;
        }
        else{
            d = d + incNE;
            y++;
            x += xi;
        }
        writepixel(x, y, r, g, b, size);
    }

}

void traceline(int x0, int y0, int x1, int y1, int r, int g, int b, int size){
    if(abs(y1 - y0) < abs(x1 - x0)){
        if(x0 > x1){
            tracelinecompleteY(x1, y1, x0, y0,1,1,1,1);
        }
        else{
            tracelinecompleteY(x0, y0, x1, y1,1,1,1,1);
        }
    }
    else{
        if(y0 > y1){
            tracelinecompleteX(x1, y1, x0, y0,1,1,1,1);
        }
        else{
            tracelinecompleteX(x0, y0, x1, y1,1,1,1,1);
        }
    }

}
void writepixel(int x, int y, int r, int g, int b, int brushSize){

    glBegin(GL_POINTS);
        glColor3f(r,g,b);
        glVertex2i(x,y);
    glEnd();
    glFlush();
    
    /*for(int i = 1; i < brushSize; i++){
        writepixel(x+1, y, r,g,b, brushSize - 1);
        writepixel(x, y+1, r,g,b, brushSize - 1);
        writepixel(x-1, y, r,g,b, brushSize - 1);
        writepixel(x, y-1, r,g,b, brushSize - 1);
    }*/

}
void reshape (int w, int h)
{
   w_size = w;
   h_size = h;
   printf("%d\n", w);
   printf("%d\n", h);
   glViewport (0, 0, w, h); 
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   gluOrtho2D(0, w, 0, h);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   display();
}
void mouseCallback(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        printf("%d ||| %d \n", x, y);
        glClear(GL_COLOR_BUFFER_BIT);
        traceline(SCREEN_WIDHT/2, SCREEN_HEIGHT/2,x, h_size - y, 1,1,1, 1);
    }
}