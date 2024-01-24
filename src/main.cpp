#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"

#include <iostream>
#include "../include/headers/shaders.h"

#define WIDTH 800
#define HEIGHT 600


void resize_func(GLFWwindow *window, int width, int height);
void exit_key(GLFWwindow *window);


int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "title", NULL, NULL);
  if(window == NULL){
    std::cout << "failed to load window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, resize_func);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "glad failed" << std::endl;
    return -1;
  }

  vba all;

  unsigned int shaderProgram;
  shaders("shaders/default.vert", "shaders/default.frag", shaderProgram);

  

  float vertices[] = {
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f
  };

  unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
  };

  
  int vertices_size = sizeof(vertices) / sizeof(vertices[0]);
  int indices_size = sizeof(indices) / sizeof(indices[0]);
  vertex_buffer_arr_stuff(all, vertices, vertices_size, indices, indices_size);

  while(!glfwWindowShouldClose(window)){
    exit_key(window);
    glUseProgram(shaderProgram);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(all.vao);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  return 0;
}

void resize_func(GLFWwindow *window, int width, int height) {
  glViewport(width, height, 0, 0);
}

void exit_key(GLFWwindow *window) {
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
    glfwSetWindowShouldClose(window, true);
  }
}
