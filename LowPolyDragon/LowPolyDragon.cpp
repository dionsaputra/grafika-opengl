#include "../Util/Core.hpp"
#include "../Util/Shader.hpp"
#include "../Util/Parser.hpp"

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    GLFWwindow* window = Core::createWindow(600, 600, "Multicolor Pentagon");

    Shader shader("VertexShader.glsl", "FragmentShader.glsl");
    
    vector<float> verticesVector = Parser::loadPoints("Vertices.txt");
    vector<unsigned int> indicesVector = Parser::loadIndices("Indices.txt");

    float vertices[verticesVector.size() + 1];
    unsigned int indices[indicesVector.size() + 1];

    for (int i=0; i<verticesVector.size(); i++) vertices[i] = verticesVector[i];
    for (int i=0; i<indicesVector.size(); i++) indices[i] = indicesVector[i];
    
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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
        glClear(GL_COLOR_BUFFER_BIT);
        // glUseProgram(shaderProgram);
        shader.use();
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