#ifndef __CORE__
#define __CORE__

#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Core {
private:
    static const char* vertexShaderSource;
    static const char* fragmentShaderSource;
public:
    static GLFWwindow* createWindow(int width, int height, const char* title);
    static bool compileShader(unsigned int* shader, bool isVertexShader);
    static bool createShader(unsigned int* shaderProgram, unsigned int vertexShader, unsigned int fragmentShader);
};

#endif