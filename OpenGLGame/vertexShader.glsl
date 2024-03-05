#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aCol;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

out vec3 FragPos;
out vec4 vertexColor;
out vec2 texCoord;
out vec3 Normal;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 LightningPos;


void main()
{
    gl_Position = projection * view * model * vec4(aPos.xyz, 1);

    vertexColor = aCol;

    FragPos = vec3(model * vec4(aPos, 1.0));

    Normal = aNormal;

    //texCoord = vec2(aPos.x + horizontalOffset, aPos.y); // we do output the value
    texCoord = aTexCoord;
}
