#ifndef __SHADER__
#define __SHADER__

#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
using namespace std;
using namespace glm;

class Shader { 
public:
    unsigned int id;
    Shader();
    Shader(const string vertexPath, const string fragmentPath);
    void use();
    void setBool(const string &name, bool value) const;
    void setInt(const string &name, int value) const;
    void setFloat(const string &name, float value) const;
    void setMat4(const GLchar* name, mat4 value);
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
private:
    void checkCompileErrors(unsigned int shader, string type);
};

#endif
