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



void main()
{
    gl_Position = projection * view * model * vec4(aPos.xyz, 1);

    vertexColor = aCol;

    FragPos = vec3(model * vec4(aPos, 1.0));

   // Calculate transformed normal using inverse transpose of the model matrix
    vec3 transformedNormal = vec3(model * vec4(aNormal, 1.0));


    Normal = aNormal;

    texCoord = aTexCoord;
}
