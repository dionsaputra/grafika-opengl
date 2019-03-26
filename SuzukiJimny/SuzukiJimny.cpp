/* sudo apt-get install libglm-dev */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include "../Util/Core.hpp"
#include "../Util/Shader.hpp"
#include "../Util/Parser.hpp"

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

const float screenWidth = 800;
const float screenHeight = 800;

int main() {
    GLFWwindow* window = Core::createWindow(screenWidth, screenHeight, "Multicolor Pentagon");
    Shader shader("VertexShader.glsl", "FragmentShader.glsl");
    glEnable(GL_DEPTH_TEST);

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

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0,0,0,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();

        mat4 model = mat4(1.0f);
        mat4 view = mat4(1.0f);
        mat4 projection = mat4(1.0f);

        view = translate(view, vec3(0.0f,0.0f,-3.0f));
        projection = perspective(radians(45.0f), screenWidth/screenHeight, 0.1f, 100.0f);
    
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