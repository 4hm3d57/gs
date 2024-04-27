//#ifndef _TEXTURE_H
//#define _TEXTURE_H

#pragma once

#include "../glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

class Texture{
public:
  void load_texture(unsigned int &texture) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    //texture wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    //texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    //loading the image to be used for texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    static const char* texturePath = "assets/textures/tsodin.png";
    unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
    if(data){
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
      std::cout << "failed to load texture" << texturePath << std::endl;
    }
    
    
    stbi_image_free(data);
  }
  
};


//#endif
