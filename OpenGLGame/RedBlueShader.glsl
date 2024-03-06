#version 330 core
out vec4 pixelColor;
uniform vec4 tintColor;
in vec4 vertexColor;
uniform float time;

void main()
{

    pixelColor = vertexColor + vec4(sin(time) * 1,0,0,0);;
}
