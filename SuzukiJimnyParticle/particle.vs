#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 offset;
uniform mat4 transform;

void main() {
    float scale = 0.01f;
    gl_Position = projection * vec4((aPos.xy * scale) + offset.xy, 0.0, 1.0);
}