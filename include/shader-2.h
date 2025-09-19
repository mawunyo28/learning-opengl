#pragma once
#include "glad/glad.h"
#include "glm/ext/matrix_float4x4.hpp"

#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
public:
  // the program ID;
  unsigned int ID;

  // Constructor reads and builds shaders
  Shader(const char *vertexPath, const char *fragmentPath);

  void use(); // use /activate the shader

  // utility uniform functions
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  float getFloat(const std::string &name) const;
  void setMat4(const std::string &name, glm::mat4 matrix) const;
};
