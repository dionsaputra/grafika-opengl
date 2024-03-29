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
    vec3 origin;
    int type;   // 0: rain, 1: smoke
    int life = 1000;

    float random(float start, float end) {
        float f = (rand() % 100)/100.0;
        double result = start + f * (end - start);
        return result;
    }

    Particle(vec3 offset, vec3 speed, vec4 color, int type, vec3 origin) {
        this->offset = offset;
        this->speed = speed;
        this->color = color;
        this->type = type;
        this->origin = origin;
        if (type == PARTICLE_RAIN) {
            this->life = (int) random(1000, 2000);
        } else {
            this->life = (int) random(200, 500);
        }
        
    }

    void updateSmoke() {
        offset += speed; life --; 
        if(life > 0){
            color.a -= (1/life);
        }
        if(life <= 0 ) {
            offset = origin;
            life = (int) random(200, 500);
        };
    }

    void updateRain() {
        offset += speed; life--; color.a -= 0.1;
        if (life <= 0.0f) {
            offset.y = 5.0f;
            life = 1000;
            color.a = 1.0f;
        }
        if (offset.y <= -5.0f) offset.y = 5.0f;
        if (offset.x >= 5.0f) offset.x = -5.0f;
        if (offset.z >= 5.0f) offset.z = -5.0f;
    }

};

class ParticleGenerator {
public:
    vector<Particle> particles;
    unsigned int VAO, VBO;
    int amount;
    Shader shader;
    vec4 color;
    mat4 model;
    mat4 view;
    mat4 projection;
    mat4 transform;

    ParticleGenerator(int amount, int type, vec3 origin=vec3(-1.0f, 1.0f, 0.0f)) {
        Shader particleShader;
        particleShader = Shader("particle.vs", "particle.fs");
        this->shader = particleShader;
        this->amount = amount;
        this->model = mat4(1.0f);
        this->transform = mat4(1.0f);

        if (type == PARTICLE_RAIN) {
            generateRain();
        } else {
            generateSmoke(origin);
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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    float random(float start, float end) {
        float f = (rand() % 100)/100.0;
        double result = start + f * (end - start);
        return result;
    }

    void generateRain() {
        for (int i=0; i<amount; i++) {
            float x = random(-5.0f, 5.0f);
            float y = 1.0f;
            float z = random(-5.0f, 5.0f);

            vec3 offset(x, y, z);           
            color = vec4(0.0f, 0.47f, 0.75f, 1.0f);
            float vx, vy, vz;
            vx = 0.001f;
            vy = random(-0.015f, -0.001f);
            vz = random(-0.001f, 0.001f);
            
            vec3 speed(vx, vy, vz);

            particles.push_back(Particle(offset, speed, color, 0, vec3(-5, 5, 5)));
        }

    }

    void generateSmoke(vec3 origin) {
        for (int i=0; i<amount; i++) {
            float x = random(-0.01, 0.01);
            float y = random(-0.01, 0.01);
            float z = random(-0.01, 0.01);

            vec3 offset(x, y, z);           
            color = vec4(0.75f, 0.75f, 0.75f, 1.0f);
            float vx, vy, vz;
            vx = random(-0.001f, 0.001f);
            vy = random(0.001f, 0.002f);
            vz = random(-0.002f, -0.001f);
            
            vec3 speed(vx, vy, vz);

            particles.push_back(Particle(origin + offset, speed, color, 1, origin));
        }

    }

    void draw() {
        shader.use();

        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.setVec4("color", color);
        shader.setMat4("transform", transform);
        glBindVertexArray(VAO);

        for (int i=0; i<amount; i++) {
            shader.setVec3("offset", particles[i].offset);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            if (particles[i].type == PARTICLE_RAIN) {
                particles[i].updateRain();
            } else {
                particles[i].updateSmoke();
            }
        }
    }
};

#endif