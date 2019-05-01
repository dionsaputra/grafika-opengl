#include "Particle.hpp"

Particle::Particle(vec3 offset, vec3 speed, int type) {
    this->offset = offset;
    this->speed = speed;
    this->type = type;
}

void Particle::update() {
    this->offset += this->speed;
}
