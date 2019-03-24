#include "Core.hpp"

const char* Core::vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* Core::fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

void framebufferSizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

GLFWwindow* Core::createWindow(int width, int height, const char* title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glewInit();
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    return window;
}

bool Core::compileShader(unsigned int* shader, bool isVertexShader) {
    *shader = isVertexShader ? glCreateShader(GL_VERTEX_SHADER) : glCreateShader(GL_FRAGMENT_SHADER);
    const char* shaderSource = isVertexShader ? vertexShaderSource : fragmentShaderSource;
    glShaderSource(*shader, 1, &shaderSource, NULL);
    glCompileShader(*shader);

    int success;
    char infoLog[512];
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(*shader, 512, NULL, infoLog);
        
        const char* shaderType = "vertex";
        if (!isVertexShader) {
            shaderType = "fragment";
        }

        std::cout << "Error compiling " << shaderType << "shader\n" << infoLog << std::endl; 
        return false;
    }
    return true;
}

bool Core::createShader(unsigned int* shaderProgram, unsigned int vertexShader, unsigned int fragmentShader) {
    *shaderProgram = glCreateProgram();
    glAttachShader(*shaderProgram, vertexShader);
    glAttachShader(*shaderProgram, fragmentShader);
    glLinkProgram(*shaderProgram);

    int success;
    char infoLog[512];
    glGetShaderiv(*shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
        std::cout << "Error creating shader\n" << infoLog << std::endl;
        return false;
    }

    return true;
}