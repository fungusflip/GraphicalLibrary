#version 330 core

out vec4 pixelColor;

uniform vec4 tintColor;
uniform sampler2D diffuseTexture;
uniform sampler2D blendTexture;

in vec4 vertexColor;
in vec2 texCoord;

void main()
{
    //pixelColor = vertexColor * texture(diffuseTexture, texCoord);
    pixelColor = mix(texture(diffuseTexture, texCoord),
                    texture(blendTexture, texCoord), 0.5);
    //pixelColor = vertexColor;
}
