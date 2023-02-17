#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 eyeNormal;
out vec3 eyePos;
out vec3 CamPos;

uniform vec3 camPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    CamPos = (model * vec4(camPos, 1.0)).xyz;
    eyeNormal = aNormal.xyz;   
    eyePos = (model * vec4(aPos, 1.0)).xyz;   
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}