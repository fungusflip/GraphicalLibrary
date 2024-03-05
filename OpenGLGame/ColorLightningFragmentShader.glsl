#version 330 core
out vec4 pixelColor;
uniform vec4 tintColor;
in vec4 vertexColor;

uniform vec3 lightPos;  
in vec3 Normal;  
in vec3 FragPos;  

void main()
{
    vec3 lightColor = vec3( 1,1,1);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 result = (ambient + diffuse) * pixelColor.rgb;
    pixelColor = vec4(result, 1.0);


    pixelColor = vertexColor;

}
