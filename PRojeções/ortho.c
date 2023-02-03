#include <GL/glut.h>
#include <stdio.h>

int dt;

float* transformPointOrtho(float* vec3, float nearPlane);

float vertices[] = {
    1.0f,1.0f,1.0f,
    -1.0f,1.0f,2.0f,
    0.0f,-1.0f,3.0f,
};

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);


    glEnable(GL_LIGHTING);
    
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity(); // Carrega a matriz identidade

    glRotatef(45, 1, 1,0);
    glScalef(0.5,0.5,0.5);


    GLfloat diffuseColor2[] = {0.5, 0, 0.0, 1};
    GLfloat ambient2[] = {0.2, 0, 0.0, 1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseColor2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient2);
    glutSolidCube(1);


    glDisable(GL_LIGHTING);
    glLoadIdentity();   
    glColor4f(1,1,1,0.5);
    
    
    glBegin(GL_TRIANGLES);
    glVertex3f(10.0f, 10.0f, 0.0f);
    glVertex3f(-10.0f, 10.0f, 0.0f);
    glVertex3f(0.0f, -10.0f, 0.0f);
    glEnd();

    glLoadIdentity();   
    glScalef(0.2, 0.2, 0.2);
    glTranslatef(0,3,0);
    glColor4f(0,0,1,1.0f);

    float* p1 = transformPointOrtho(&vertices[0], 0.1);
    float* p2 = transformPointOrtho(&vertices[3], 0.1);
    float* p3 = transformPointOrtho(&vertices[6], 0.1);
    
    glBegin(GL_TRIANGLES);
    //glVertex3f(1.0f, 1.0f, 0.1f);
    //glVertex3f(-1.0f, 1.0f, 0.1f);
    //glVertex3f(0.0f, -1.0f, 0.1f);

    glVertex3f(p1[0],p1[1],p1[2]);
    glVertex3f(p2[0],p2[1],p2[2]);
    glVertex3f(p3[0],p3[1],p3[2]);
    glEnd();

    printf("%f   %f    %f\n", p1[0], p1[1], p1[2]);
    printf("%f   %f    %f\n", p2[0], p2[1], p2[2]);
    printf("%f   %f    %f\n", p3[0], p3[1], p3[2]);
    
    
    glutSwapBuffers();
}


float* transformPointOrtho(float* vec3, float nearPlane){
    vec3[2] = nearPlane;
    return vec3;
};


void init() {
    glEnable(GL_BLEND);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);
    GLfloat ambient1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
    GLfloat diffuse1[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    GLfloat specular1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
    GLfloat light_position1[] = { -1.0f, 0.5f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);



    glClearColor(0.0, 0.0, 0.0, 0.0); // Define a cor    de fundo como branca
    glMatrixMode(GL_PROJECTION); // Seleciona a matriz de projeção



    glLoadIdentity(); // Carrega a matriz identidade
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Define o volume de visualização 2D
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Transformações 2D");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}