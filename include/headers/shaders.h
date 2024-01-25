#ifndef _SHADER_H
#define _SHADER_H

#include "../glad/glad.h"

#include <iostream>
#include <fstream>
#include <string>

struct vba {
  unsigned int vbo;
  unsigned int vao;
  unsigned int ebo;
};

void shaders(const char* vertexPath, const char* fragmentPath, unsigned int &shaderprogram){
  std::ifstream vShaderFile(vertexPath), fShaderFile(fragmentPath);

  if(!vShaderFile.is_open() || !fShaderFile.is_open()){
    std::cout << "could not open the shader files" << std::endl;
    return;
  }

  std::string vertexCode((std::istreambuf_iterator<char>(vShaderFile)), std::istreambuf_iterator<char>());
  std::string fragmentCode((std::istreambuf_iterator<char>(fShaderFile)), std::istreambuf_iterator<char>());

  const char* vShaderSource = vertexCode.c_str();
  const char* fShaderSource = fragmentCode.c_str();
  
  unsigned int vertexshader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexshader, 1, &vShaderSource, NULL);
  glCompileShader(vertexshader);

  unsigned int fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentshader, 1, &fShaderSource, NULL);
  glCompileShader(fragmentshader);

  shaderprogram = glCreateProgram();
  glAttachShader(shaderprogram, vertexshader);
  glAttachShader(shaderprogram, fragmentshader);
  glLinkProgram(shaderprogram);
}



void vertex_buffer_arr_stuff(vba all, float vert[], int vert_size, unsigned int ind[], int ind_size) {
  glGenVertexArrays(1, &all.vao);
  glGenBuffers(1, &all.vbo);
  glGenBuffers(1, &all.ebo);

  glBindVertexArray(all.vao);

  glBindBuffer(GL_ARRAY_BUFFER, all.vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vert_size, vert, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, all.ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * ind_size, ind, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);
}


#endif
