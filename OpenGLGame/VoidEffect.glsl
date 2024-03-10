#version 330 core
out vec4 pixelColor;
uniform vec4 tintColor;
in vec4 vertexColor;

uniform float time;
uniform vec3 cameraPos;
in vec3 FragPos;  
in vec3 Normal;


void main()
{
    vec3 cameraPos = vec3(8,2,5);
    vec3 lightColor = sin(time) * vec3(0.3,0.8,0.8);
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(cameraPos - FragPos);  

     float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;


    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
   
    float interval = sin(sin(time));

    vec3 result = ((ambientStrength + diff) * lightColor * vertexColor.rgb);

    pixelColor = vec4(result, 1.0);

    //pixelColor = vec4(Normal.x, Normal.y, Normal.z, 1);
}
