#version 330 core
layout (location = 0) in vec2 vertex;
layout (location = 1) in vec3 aColor;
out vec3 ourColor;

uniform mat4 projection;

void main(){
    float scale = 10.0f;
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
    ourColor = aColor;
}