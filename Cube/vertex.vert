#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 eyeNormal;
out vec3 eyePos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    eyeNormal = normalize((view * model * vec4(aNormal, 1.0)).xyz);   
    eyePos = (view * model * vec4(aPos, 1.0)).xyz;   
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}