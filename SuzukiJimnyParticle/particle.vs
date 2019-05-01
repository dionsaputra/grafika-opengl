#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 offset;
uniform mat4 transform;

void main() {
    float scale = 0.01f;
    gl_Position = projection * view * model * (transform * vec4(aPos, 1.0) * scale + vec4(offset, 1.0));
}