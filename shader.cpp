#include "shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vCode, fCode;
    std::ifstream vFile(vertexPath), fFile(fragmentPath);
    std::stringstream vStream, fStream;
    vStream << vFile.rdbuf(); fStream << fFile.rdbuf();
    vCode = vStream.str(); fCode = fStream.str();
    const char* vSrc = vCode.c_str();
    const char* fSrc = fCode.c_str();

    unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vSrc, nullptr);
    glCompileShader(vShader);

    unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fSrc, nullptr);
    glCompileShader(fShader);

    ID = glCreateProgram();
    glAttachShader(ID, vShader);
    glAttachShader(ID, fShader);
    glLinkProgram(ID);
    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

void Shader::use() { glUseProgram(ID); }

void Shader::setMat4(const std::string& name, const float* value) {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value);
}

Shader::~Shader() { glDeleteProgram(ID); }
