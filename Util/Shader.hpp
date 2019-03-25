#ifndef __SHADER__
#define __SHADER__

#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

class Shader {
public:
    unsigned int id;
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void use();
    void setBool(const string &name, bool value) const;
    void setInt(const string &name, int value) const;
    void setFloat(const string &name, float value) const;

private:
    void checkCompileErrors(unsigned int shader, string type);
};

#endif
