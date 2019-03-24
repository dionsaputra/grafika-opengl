#include "../Core/Core.hpp"

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    GLFWwindow* window = Core::createWindow(600, 600, "Multicolor Pentagon");

    unsigned int vertexShader, fragmentShader, shaderProgram;
    if (!Core::compileShader(&vertexShader, true)) {
        return -1;
        perror("Error compiling vertex shader");
    }

    if (!Core::compileShader(&fragmentShader, false)) {
        return -1;
        perror("Error compiling fragment shader");
    }
    
    if (!Core::createShader(&shaderProgram, vertexShader, fragmentShader)) {
        return -1;
        perror("Error link in shader program");
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    float vertices[] = {
        -0.6, -0.9, 0,
        0.6, -0.9, 0,
        0.97, 0.14, 0,
        0, 0.85f, 0,
        -0.97, 0.14, 0
    }; 

    unsigned int indices[] = {
        0,1,2,
        2,3,4,
        4,0,2,
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}