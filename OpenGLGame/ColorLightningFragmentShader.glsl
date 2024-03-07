#version 330 core
out vec4 pixelColor;
uniform vec4 tintColor;
in vec4 vertexColor;

uniform vec3 lightPos;  
in vec3 FragPos;  
in vec3 Normal;

void main()
{

    pixelColor = vec4(FragPos * vertexColor.rgb, 1.0);
    //pixelColor = vec4(Normal.x, Normal.y, Normal.z, 1);
}
