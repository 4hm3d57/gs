#version 330 core

out vec4 Fragcolor;

in vec2 texCoord;

uniform sampler2D ourTexture;

void main(){
  Fragcolor = texture(ourTexture, texCoord);
}
