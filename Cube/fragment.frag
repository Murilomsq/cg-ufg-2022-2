#version 330 core
out vec4 FragColor;

in vec3 eyeNormal;
in vec3 eyePos;
in vec3 CamPos;

void main()
{    
    vec3 view = normalize(CamPos-eyePos);
    if(dot(eyeNormal, view) < 0 ){
        discard;
    } 
    
    FragColor = vec4(abs(eyeNormal)*vec3(1.0),1.0);
}