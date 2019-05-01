#include "ParticleGenerator.hpp"

ParticleGenerator::ParticleGenerator(Shader shader, /*Texture2D texture,*/ int amount) {
    this->shader = shader;
    // this->texture = texture;
    this->amount = amount;
    this->init();
}

// TODO: GameObject will be implemented later
void ParticleGenerator::update(float deltaTime, vec2 objectPosition, vec2 objectVelocity, int newParticles, vec2 offset) {
    for (int i=0; i<newParticles; i++) {
        int unusedParticle = firstUnusedParticle();
        respawnParticle(particles[unusedParticle], objectPosition, objectVelocity, offset);
    }

    for (int i=0; i<amount; i++) {
        Particle &particle = particles[i];
        particle.life -= deltaTime;
        if (particle.life > 0.0f) {
            particle.position -= particle.velocity * deltaTime;
            particle.color.a -= deltaTime * 2.5f;
        }
    }
}

void ParticleGenerator::draw() {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    shader.use();
    for (Particle particle : particles) {
        if (particle.life > 0.0f) {
            shader.setVec4("color", particle.color);
            // cout<<particle.position.x<<endl;
            shader.setVec2("offset", particle.position);
            // texture.bind();
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);             
        }
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGenerator::init() {
    unsigned int VBO;
    float particleQuad[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particleQuad), particleQuad, GL_STATIC_DRAW);
    
    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    // glBindVertexArray(0);

    for (int i=0; i<amount; i++) {
        particles.push_back(Particle());
    }
}

int ParticleGenerator::firstUnusedParticle() {
    for (int i=lastUsedParticle; i<amount; i++) {
        if (particles[i].life <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }

    for (int i=0; i<lastUsedParticle; i++) {
        if (particles[i].life <= 0.0f) {
            lastUsedParticle = i;
            return i;
        }
    }

    lastUsedParticle = 0;
    return 0;
}

void ParticleGenerator::respawnParticle(Particle &particle, vec2 objectPosition, vec2 objectVelocity, vec2 offset) {
    float random = ((rand()%100) - 50) / 20.0f;
    float red = 0.2 + ((rand()%100) / 100.0f);
    float green = 0.3 + ((rand()%100) / 100.0f);
    float blue = 0.5 + ((rand()%100) / 100.0f);
    particle.position = objectPosition + vec2(random) + offset;
    particle.color = vec4(red, green, blue, 1.0f);
    particle.life = 1.0f;
    particle.velocity = objectVelocity * 0.1f;
}
