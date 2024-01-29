#ifndef _SHADER_H
#define _SHADER_H

#include "../glad/glad.h"

#include <iostream>
#include <fstream>
#include <string>


struct vba {
  unsigned int vao;
  unsigned int vbo;
  unsigned int ebo;
};


void shaders(const char *vertexPath, const char *fragmentPath, unsigned int &shaderprogram){
  std::ifstream vshaderFile(vertexPath), fshaderFile(fragmentPath);

  if(!vshaderFile.is_open() || !fshaderFile.is_open()){
    std::cout << "failed to open the shader files" << std::endl;
    return;
  }

  //turning the shader files to string to be compiled
  std::string vertexcode((std::istreambuf_iterator<char>(vshaderFile)), std::istreambuf_iterator<char>());
  std::string fragmentcode((std::istreambuf_iterator<char>(fshaderFile)), std::istreambuf_iterator<char>());

  const char* vShaderSource = vertexcode.c_str();
  const char* fShaderSource = fragmentcode.c_str();
  
  unsigned int vertexshader;
  vertexshader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexshader, 1, &vShaderSource, NULL);
  glCompileShader(vertexshader);

  unsigned int fragmentshader;
  fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentshader, 1, &fShaderSource, NULL);
  glCompileShader(fragmentshader);

  shaderprogram = glCreateProgram();
  glAttachShader(shaderprogram, vertexshader);
  glAttachShader(shaderprogram, fragmentshader);
  glLinkProgram(shaderprogram);
}



void vertex_attrib_stuff(vba& all, float vert[], int vertsize, unsigned int ind[], int indsize){
  glGenVertexArrays(1, &all.vao);

  glGenBuffers(1, &all.vbo);
  glGenBuffers(1, &all.ebo);

  glBindVertexArray(all.vao);

  glBindBuffer(GL_ARRAY_BUFFER, all.vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertsize, vert, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, all.ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indsize, ind, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}


#endif
