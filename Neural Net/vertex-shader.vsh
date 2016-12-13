#version 150

uniform mat4 camera;
uniform mat4 model;

in vec3 vertex;
in vec2 UV;

out vec2 fragTexCoord;

void main() {
    // Pass the tex coord straight through to the fragment shader
    fragTexCoord = UV;
    
    // Apply all matrix transformations to vert
    gl_Position = camera * model * vec4(vertex, 1);
}