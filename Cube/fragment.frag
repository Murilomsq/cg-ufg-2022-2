#version 330 core
out vec4 FragColor;

in vec3 eyeNormal;
in vec3 eyePos;

void main()
{    
    vec3 view = normalize(-eyePos);
    if(dot(eyeNormal, view) > 0 ){
        discard;
    } 
    FragColor = vec4(1.0, 0.4, 0.8, 1.0);
}