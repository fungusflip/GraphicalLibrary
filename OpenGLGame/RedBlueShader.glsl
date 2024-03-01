#version 330 core
out vec4 pixelColor;
uniform vec4 tintColor;
in vec4 vertexColor;
uniform float time;

void main()
{

    pixelColor = vertexColor + new vec4(sin(time) * 0.5,0,0,0);;
}
