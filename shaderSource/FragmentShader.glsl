#version 330 core

// input
in vec3 passColor;
// Ouput data
out vec4 color;

void main()
{ 
    color = vec4(passColor, 1.0);

}