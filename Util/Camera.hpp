#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

using namespace glm;

enum CameraMovement {
    FORWARD, BACKWARD, LEFT, RIGH
};

class Camera {
public:
    vec3 position;
    vec3 front;
    vec3 up;
    vec3 rigth;
    vec3 worldUp;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    Camera();
    mat4 getViewMatrix();
    void processKeyboard();
    void processMouseMovement();
    void processMouseScroll();

private:
    void updateCameraVectors();
};
#endif
