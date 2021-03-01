#version 410

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

out vec3 Normal;
out vec3 FragPos;

void main() {
   gl_Position = projection * view * model * vec4(pos, 1.0f);
   FragPos = vec3(model * vec4(pos, 1.0));
   Normal = normal;

   // Calculate the normal vector against the world matrix only.
   Normal = normalize(mat3(model) * normal);
}
