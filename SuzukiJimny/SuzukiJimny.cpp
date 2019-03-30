/* sudo apt-get install libglm-dev */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include "../Util/Core.hpp"
#include "../Util/Shader.hpp"
#include "../Util/Parser.hpp"

vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void processInput(GLFWwindow *window){
    float cameraSpeed = 2.5f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraFront;
    }
        
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
        cameraPos -= cameraSpeed * cameraFront;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
        cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
        cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
    
}

const float screenWidth = 800;
const float screenHeight = 800;

bool firstMouse = true;
float lastX = 400, lastY = 300;
float myYaw = -90.0f, myPitch = 0.0f;
float fov = 45.0f;

void mouseCallback(GLFWwindow* window, double xPos, double yPos) {    
    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    float sensitivity = 0.05f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    myYaw += xOffset;
    myPitch += yOffset;

    if (myPitch > 89.0f) myPitch = 89.0f;
    if (myPitch < -89.0f) myPitch = -89.0f;

    vec3 front = vec3(
        cos(radians(myPitch)) * cos(radians(myYaw)),
        sin(radians(myPitch)),
        cos(radians(myPitch)) * sin(radians(myYaw))
    );
    cameraFront = normalize(front);
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    if (fov >= 1.0f && fov <= 45.0f) fov -= yOffset;
    if (fov <= 1.0f) fov = 1.0f;
    if (fov >= 45.0f) fov = 45.0f;
}

int main() {
    GLFWwindow* window = Core::createWindow(screenWidth, screenHeight, "Multicolor Pentagon");
    Shader shader("VertexShader.glsl", "FragmentShader.glsl");
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback); 

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,
    };
    
    vec3 cubePositions[] = {
        vec3( 0.0f,  0.0f,  0.0f), 
        vec3( 2.0f,  5.0f, -15.0f), 
        vec3(-1.5f, -2.2f, -2.5f),  
        vec3(-3.8f, -2.0f, -12.3f),  
        vec3( 2.4f, -0.4f, -3.5f),  
        vec3(-1.7f,  3.0f, -7.5f),  
        vec3( 1.3f, -2.0f, -2.5f),  
        vec3( 1.5f,  2.0f, -2.5f), 
        vec3( 1.5f,  0.2f, -1.5f), 
        vec3(-1.3f,  1.0f, -1.5f)  
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

    // position attribute    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    float radius = 10.0f;

    while (!glfwWindowShouldClose(window)) {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        glClearColor(0,0,0,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();

        mat4 model = mat4(1.0f);
        mat4 projection = mat4(1.0f);
        mat4 view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        projection = perspective(radians(fov), screenWidth/screenHeight, 0.1f, 100.0f);
    
        int modelLoc = glGetUniformLocation(shader.id, "model");
        int viewLoc = glGetUniformLocation(shader.id, "view");
        int projLoc = glGetUniformLocation(shader.id, "projection");

        glBindVertexArray(VAO);
        for (int i=0; i<10; i++) {
            mat4 model = mat4(1.0f);
            model = translate(model, cubePositions[i]);
            float angle = 20.0f * (i+1);
            model = rotate(model, (float)glfwGetTime()*radians(angle), vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(projection));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}