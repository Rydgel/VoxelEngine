#version 440 core

in vec3 FragPos;
in vec3 Normal;
in vec3 TexCoord;

out vec4 color;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform sampler2DArray ourTexture;

// move that to uniform if still needed
const vec4 fogColor = vec4(0.73, 0.82, 0.89, 1.0);

void main()
{
    float fog_factor =  1.0 - (gl_FragCoord.z / gl_FragCoord.w) / 300.0;
    fog_factor = clamp(fog_factor, 0.0, 1.0);

    /*
    // color = mix(fogColor, texture(ourTexture, TexCoord), fog_factor);
    //color = mix(fogColor, colorDraw, fog_factor);
    // color = texture(ourTexture, TexCoord);
    // color = cubeColor;
    // color = colorDraw;
    // Ambient
    float ambientStrength = 0.5f;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.1f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec4 result = vec4(ambient + diffuse + specular, 1.0f) * texture(ourTexture, TexCoord);
    color = mix(fogColor, result, fog_factor);*/
    // color = texture(ourTexture, TexCoord);
    color = mix(fogColor, texture(ourTexture, TexCoord), fog_factor);
}