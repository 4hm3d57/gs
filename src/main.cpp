#include "../include/glad/glad.h"

#include "../include/GLFW/glfw3.h"

#include "../include/headers/shaders.h"
#include "../include/headers/texture.h"

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

#include <iostream>

#define WIDTH 800
#define HEIGHT 600

void resize_func(GLFWwindow *window, int width, int height);
void exit_key(GLFWwindow *window);

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "test", NULL, NULL);
  if (window == NULL) {
    std::cout << "failed to load window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, resize_func);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "glad failed" << std::endl;
    return -1;
  }


  float vertices[] = {
      // positions          // texture coords
      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, // top right
      0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom left
      -0.5f, 0.5f,  0.0f, 0.0f, 0.0f  // top left
  };

  unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };

  vba all;
  unsigned int shaderProgram;
  Shaders ourshader;

  ourshader.shaders("shaders/default.vert", "shaders/default.frag", shaderProgram);

  int verticeSize = sizeof(vertices) / sizeof(vertices[0]);
  int indicesSize = sizeof(indices) / sizeof(indices[0]);

  unsigned int Texture;
  textures(Texture);

  ourshader.vertex_attrib_stuff(all, vertices, verticeSize, indices, indicesSize);

  glUseProgram(shaderProgram);

  while (!glfwWindowShouldClose(window)) {
    exit_key(window);
    float current_time = glfwGetTime();
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, current_time, glm::vec3(0.0f, 0.0f, 1.0f));
    glUseProgram(shaderProgram);
    unsigned int transLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));
    glBindTexture(GL_TEXTURE_2D, Texture);
    glBindVertexArray(all.vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &all.vao);
  glDeleteBuffers(1, &all.vbo);
  glDeleteBuffers(1, &all.ebo);

  glfwTerminate();
  return 0;
}

void resize_func(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void exit_key(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
