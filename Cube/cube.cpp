#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Camera.h"
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLuint program;
unsigned int VBO, cubeVAO;
glm::vec3 cameraPos = glm::vec3(1.0f, 1.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float* transformPointOrtho(float* vec3, float nearPlane);

float vertices[] = {
    
    // positions          // normals         
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  
    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   
    0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  


    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 
    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 


};

void keyboard(unsigned char key, int x, int y) {
    float cameraSpeed = 0.1f * deltaTime;
    switch (key) {
    case 'w':
      cameraPos += cameraSpeed * cameraFront;
      break;
    case 's':
      cameraPos -= cameraSpeed * cameraFront;
      break;
    case 'a':
      cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
      break;
    case 'd':
      cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
      break;
    case 'c':
        cameraFront *= -1;
    break;
    }
}

char* read_file(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Error: Failed to open file %s\n", filename);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* buffer = (char*) malloc(length + 1);
    if (!buffer) {
        printf("Error: Failed to allocate memory for file %s\n", filename);
        fclose(file);
        return NULL;
    }
    size_t size = fread(buffer, 1, length, file);
    buffer[size] = '\0';
    fclose(file);
    return buffer;
}



void display() {

    float currentFrame = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClear(GL_DEPTH_BUFFER_BIT);

    
    glClearColor(0.12f, 0.22f, 0.22f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 


    
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glm::mat4 model = glm::mat4(1.0f);

    

    glUseProgram(program);
    
    unsigned int modelLoc = glGetUniformLocation(program, "model");
    unsigned int viewLoc = glGetUniformLocation(program, "view");
    unsigned int projectionLoc = glGetUniformLocation(program, "projection");
    unsigned int camPosLoc = glGetUniformLocation(program, "camPos");

    
    

    // Set the values of the uniform variables
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);
    glUniform3fv(camPosLoc, 1, &cameraPos[0]);
    
    
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 24);
    glutPostRedisplay();
    glutSwapBuffers();
}


void init() {

    char* vertex_source = read_file("vertex.vert");
    char* fragment_source = read_file("fragment.frag");

    glClearColor(1.0, 1.0, 1.0, 1.0); // Define a cor    de fundo como branca

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    



    // Create the shader program
    program = glCreateProgram();
    

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, (const GLchar**)&vertex_source, NULL);
    glCompileShader(vertexShader);

    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("Shader compilation failed: %s\n", infoLog);
    }   

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (const GLchar**)&fragment_source, NULL);
    glCompileShader(fragmentShader);
    

    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("Shader compilation failed: %s\n", infoLog);
    }   

    // Attach the shaders to the program and link the program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    

}

int main(int argc, char** argv) {

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cube");
    

    // Initialize GLEW
    glewInit();
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}