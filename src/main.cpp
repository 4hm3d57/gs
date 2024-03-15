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
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void exit_key(GLFWwindow *window);

float squareX = 0.0f;
float squareY = 0.0f;
float moveSpeed = 0.5f;

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
  glfwSetKeyCallback(window, key_callback);

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

  ourshader.vfshaders("shaders/default.vert", "shaders/default.frag", shaderProgram);

  int verticeSize = sizeof(vertices) / sizeof(vertices[0]);
  int indicesSize = sizeof(indices) / sizeof(indices[0]);

  Texture test;
  unsigned int Texture;
  test.textures(Texture);

  ourshader.vertex_attrib_stuff(all, vertices, verticeSize, indices, indicesSize);

  glUseProgram(shaderProgram);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    exit_key(window);

    //float rotate_time = glfwGetTime();
    //glm::mat4 trans = glm::mat4(1.0f);
    //trans = glm::rotate(trans, rotate_time, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(squareX, squareY, 0.0f));

    glUseProgram(shaderProgram);
    //unsigned int transLoc = glGetUniformLocation(shaderProgram, "transform");
    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    //glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(action == GLFW_PRESS || action == GLFW_REPEAT){
        switch(key){
            case GLFW_KEY_UP:
                squareY += moveSpeed;
                break;
            case GLFW_KEY_DOWN:
                squareY -= moveSpeed;
                break;
            case GLFW_KEY_LEFT:
                squareX -= moveSpeed;
                break;
            case GLFW_KEY_RIGHT:
                squareX += moveSpeed;
                break;
            default:
                break;
        }
    }
}

void exit_key(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
