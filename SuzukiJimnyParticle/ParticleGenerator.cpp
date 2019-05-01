#ifndef __PARTICLE_GENERATOR__
#define __PARTICLE_GENERATOR__

#include "../Util/Shader.hpp"
#include <bits/stdc++.h>
using namespace std;

#define PARTICLE_RAIN 0
#define PARTICLE_SMOKE 1

class Particle {
public:
    vec3 offset;
    vec3 speed;
    vec4 color;
    int type;   // 0: rain, 1: smoke

    Particle(vec3 offset, vec3 speed, vec4 color, int type) {
        this->offset = offset;
        this->speed = speed;
        this->color = color;
        this->type = type;
    }

    void update() {
        offset += speed;
    }
};

class ParticleGenerator {
public:
    vector<Particle> particles;
    unsigned int VAO, VBO;
    int amount;
    Shader shader;
    vec4 color;

    ParticleGenerator(int amount, int type, vec3 origin=vec3(0.0f, 0.0f, 0.0f)) {
        Shader particleShader;
        particleShader = Shader("particle.vs", "particle.fs");
        this->shader = particleShader;
        this->amount = amount;

        for (int i=0; i<amount; i++) {
            float x = (rand() % 100)/100;
            float y = (rand() % 100)/100;
            float z = (rand() % 100)/100;
            vec3 offset(x, y, z);

            float r, g, b;
            if (type == PARTICLE_RAIN) {
                r = 0.0f; g = 0.47f; b = 0.75f;
            } else if (type == PARTICLE_SMOKE) {
                r = 0.96f; g = 0.96f; b = 0.96f;
            }
            this->color = vec4(r, g, b, 1.0f);

            float vx, vy, vz;
            if (type == PARTICLE_RAIN) {
                vx = 0.001f; vy = -0.01f; vz = 0.001f;
            } else if (type == PARTICLE_SMOKE) {
                vx = 0.001f; vy = 0.001f; vz = 0.01f;
            }
            vec3 speed(vx, vy, vz);

            particles.push_back(Particle(offset+origin, speed, color, type));
        }

        float particle[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,

            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.0f, 0.5f, 0.5f
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(particle), particle, GL_STREAM_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);
    }

    void draw() {
        shader.use();

        mat4 model(1.0f);
        mat4 view(1.0f);
        mat4 projection(1.0f);

        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.setVec4("color", color);
        glBindVertexArray(VAO);

        for (int i=0; i<amount; i++) {
            shader.setVec3("offset", particles[i].offset);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            particles[i].update();
        }
    }
};

#endif