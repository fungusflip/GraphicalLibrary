#version 330 core
out vec4 pixelColor;
uniform vec4 tintColor;
in vec4 vertexColor;

uniform vec3 lightPos;  
in vec3 Normal;  

void main()
{
    pixelColor = vertexColor;
}
