#version 410

in vec3 FragPos;
in vec3 Normal;

uniform vec3 color;
uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 diffusePos;

out vec4 frag_color;

void main() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(diffusePos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * diffuseColor;
    vec3 ambient = 0.005 * ambientColor;

    vec3 result = (ambient + diffuse) * color;
    frag_color = vec4(result, 1.0);
}
