#version 330 core
out vec4 pixelColor;
uniform vec4 tintColor;
in vec4 vertexColor;

uniform vec3 lightPos;  
in vec3 FragPos;  
in vec3 Normal;

void main()
{

    vec3 lightColor = vec3(0.5, 0.5, 0.5);

    float ambientStrength = 0.8;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * vertexColor.rgb;
    pixelColor = vec4(result, 1.0);
    //pixelColor = vec4(Normal.x, Normal.y, Normal.z, 1);
}
