#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 lightPos; 
uniform vec3 lightPos2; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 lightColor2;
uniform vec3 objectColor;
uniform vec3 objectColor2;
uniform float Ka = 0.3f;

void main()
{
    vec3 ambient = Ka * (lightColor + lightColor2);
    FragColor = vec4(objectColor * ambient, 1.0);
}
