#ifndef __CORE__
#define __CORE__

#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Core {
public:
    static GLFWwindow* createWindow(int width, int height, const char* title);
};

#endif