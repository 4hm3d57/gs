#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "../glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

void textures(unsigned int &textures) {
  glGenTextures(1, &textures);
  glBindTexture(GL_TEXTURE_2D, textures);

  //texture wrapping
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

  //texture filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  //getting the image to be used for texturing
  int width, height, nrChannels;
  static const char* texturePath = "assets/tsodin.png";
  unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
  if(data){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else{
    std::cout << "Failed to load texture" << std::endl;
  }

  stbi_image_free(data);
  
}

#endif
