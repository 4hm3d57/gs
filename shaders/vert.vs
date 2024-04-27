#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 texCoord;

uniform mat4 move;
uniform mat4 rotation;
uniform mat4 lookat;
uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position = projection * view * lookat * move * rotation * vec4(aPos, 1.0f);
    texCoord = vec2(aTexCoord.x, aTexCoord.y);
}
