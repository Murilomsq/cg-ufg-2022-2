#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<GL/glut.h>
void reshape (int w, int h);

int xstart, ystart, xend, yend;

void init()
{
    glViewport(0,0, 500, 500);
    gluOrtho2D(0, 500, 0, 500);
}

void draw_pixel(int x, int y)
{
	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}


void LineBres(int xstart, int ystart, int xend, int yend)
{
	int dx = fabs(xend - xstart);
	int dy = fabs(yend - ystart);
	int twody = 2 * dy, twodyminusdx = 2 * (dy - dx);
	int p = 2 * dy - dx;
	int x, y;

	if (xstart > xend)
	{
		x = xend;
		y = yend;
		xend = xstart;
	}
	else
	{
		x = xstart;
		y = ystart;

	}
	draw_pixel(x, y);


	while (x < xend)
	{
		x++;
		if (p < 0)
			p += twody;
		else
		{
			y++;
			p += twodyminusdx;

		}
		draw_pixel(x, y);
	}

}


void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);

	LineBres(xstart, ystart, xend, yend);
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{

	printf("Enter 2 points");
	scanf("%d%d%d%d", &xstart, &ystart, &xend, &yend);
	glutInit(&argc, argv);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(500, 500);
	glutCreateWindow(".Line.");
	init();
	glutDisplayFunc(Display);
    glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
void reshape (int w, int h)
{
   printf("%d\n", w);
   printf("%d\n", h);
   glViewport (0, 0, w, h); 
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   gluOrtho2D(0, w, 0, h);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   Display();
}