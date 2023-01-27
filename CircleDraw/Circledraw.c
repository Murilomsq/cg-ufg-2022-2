#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define SCREEN_WIDHT 1000
#define SCREEN_HEIGHT 1000

void writepixel(int x, int y, int r, int g, int b);
void reshape (int w, int h);
void mouseCallback(int button, int state, int x, int y);
void midPointCircle(int r, int color);
void writeCircle(int x,int y);


int w_size;
int h_size;

void init()
{
    glClearColor(0.2,0.2,0,0);
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

void midPointCircle(int r, int color){
    int x = 0;
    int y = r;
    float d = 5/4 - r;

    writeCircle(x, y);

    while(y>x){
        if(d < 0){
            d = d+2*x+3;  //E
            x++;
        }
        else{
            d = d+2*(x-y)+5; //SE
            x++;
            y--;
        }
        writeCircle(x, y);
    }
    
}

void writeCircle(int x,int y){
    writepixel(x + SCREEN_WIDHT/2, y + SCREEN_HEIGHT/2, 1,1,1);
    writepixel(x + SCREEN_WIDHT/2, -y + SCREEN_HEIGHT/2, 1,1,1);
    writepixel(-x + SCREEN_WIDHT/2, y + SCREEN_HEIGHT/2, 1,1,1);
    writepixel(-x + SCREEN_WIDHT/2, -y + SCREEN_HEIGHT/2, 1,1,1);
    writepixel(y + SCREEN_WIDHT/2, x + SCREEN_HEIGHT/2, 1,1,1);
    writepixel(y + SCREEN_WIDHT/2, -x + SCREEN_HEIGHT/2, 1,1,1);
    writepixel(-y + SCREEN_WIDHT/2, x + SCREEN_HEIGHT/2, 1,1,1);
    writepixel(-y + SCREEN_WIDHT/2, -x + SCREEN_HEIGHT/2, 1,1,1);
}
void writepixel(int x, int y, int r, int g, int b){

    glBegin(GL_POINTS);
        glColor3f(r,g,b);
        glVertex2i(x,y);
    glEnd();
    glFlush();


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
        midPointCircle(sqrt((SCREEN_WIDHT/2 - x)*(SCREEN_WIDHT/2 - x)+(SCREEN_HEIGHT/2 - y)*(SCREEN_HEIGHT/2 - y)), 1);
        writeCircle( x  , h_size - y);
        //printf("%d ||| %d \n", x, y);
        glClear(GL_COLOR_BUFFER_BIT);
        //traceline(SCREEN_WIDHT/2, SCREEN_HEIGHT/2,x, h_size - y, 1,1,1, 1);
    }
}