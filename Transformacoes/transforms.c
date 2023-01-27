#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

int dt;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); // Define a cor vermelha para o objeto

    glMatrixMode(GL_MODELVIEW); // Seleciona a matriz de modelo de visualização
    glLoadIdentity(); // Carrega a matriz identidade


    glPushMatrix();
    glTranslatef(0.5, 0.5, 0.0); // Translada o objeto em 0.5 unidades no eixo x e 0.5 unidades no eixo y
    glScalef(0.5, 0.5, 0.5); // Reduz o tamanho do objeto para metade

    //Animação
    //printf("%f\n",(float)glutGet(GLUT_ELAPSED_TIME)/1000.0 );
    glRotatef(10*((float)glutGet(GLUT_ELAPSED_TIME)/1000.0), 0.0, 0.0, 1.0);
    //glScalef(0.5, 0.5, 0.5); // Reduz o tamanho do objeto para metade

    
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.0, 0.5);
    glEnd();

    glPopMatrix();

    glPushMatrix();

    glTranslatef(0, -0.5, 0.0); // Translada o objeto em 0.5 unidades no eixo x e 0.5 unidades no eixo y
    glScalef(cos((float)glutGet(GLUT_ELAPSED_TIME)/1000.0), cos((float)glutGet(GLUT_ELAPSED_TIME)/1000.0), 0.0); // Gira o objeto em 45 graus no eixo z

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.0, 0.5);
    glEnd();

    glPopMatrix();
    
    glTranslatef(-0.2, (cos((float)glutGet(GLUT_ELAPSED_TIME)/1000.0)/5) +1, 0.0); // Translada o objeto em 0.5 unidades no eixo x e 0.5 unidades no eixo y
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.0, 0.5);
    glEnd();


    glFlush();
    glutPostRedisplay();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Define a cor de fundo como branca
    glMatrixMode(GL_PROJECTION); // Seleciona a matriz de projeção
    glLoadIdentity(); // Carrega a matriz identidade
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Define o volume de visualização 2D
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Transformações 2D");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}