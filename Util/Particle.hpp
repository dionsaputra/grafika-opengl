#ifndef __PARTICLE__
#define __PARTICLE__

#include <glm/glm.hpp>
using namespace glm;

class Particle {
public:
    vec3 offset;
    vec3 speed;
    int type;       // 0: Rain, 1: Smoke

    Particle(vec3 offset, vec3 speed, int type);
    void update();
};

#endif