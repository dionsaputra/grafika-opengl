#include "Shader.hpp"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
    
    // read shader from file
    string vertexCode;
    string fragmentCode;
    ifstream vertexShaderFile;
    ifstream fragmentShaderFile;

    vertexShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    fragmentShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

    try {
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);

        stringstream vertexShaderStream, fragmentShaderStream;
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        vertexCode = vertexShaderStream.str();
        fragmentCode = fragmentShaderStream.str();

    } catch (ifstream::failure e) {
        cout<<"Error shader, file not successfully read" << endl;
    }
    
    const char* vertexShaderCode = vertexCode.c_str();
    const char* fragmentShaderCode = fragmentCode.c_str();

    // compile shader
    unsigned int vertexShader, fragmentShader;
    
    // vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");

    // fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, & fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");

    // shader program
    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);
    checkCompileErrors(id, "PROGRAM");

    // delete vertexShader and fragmentShader
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::checkCompileErrors(unsigned int shader, string type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            cout<<"Error compiling " << type << "fragment \n" << infoLog << endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            cout<<"Error linking shader program\n" << infoLog << endl;
        }
    }
}

void Shader::use() {
    glUseProgram(id);
}

void Shader::setMat4(const GLchar* name, mat4 value) {
    int location = glGetUniformLocation(id, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(value));
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const { 
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]); 
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const { 
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z); 
}