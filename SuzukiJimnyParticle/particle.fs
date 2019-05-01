#version 330 core
// in vec2 TexCoords;
out vec4 ParticleColor;
uniform vec4 color;

// uniform sampler2D sprite;

void main() {
    ParticleColor = color;
}