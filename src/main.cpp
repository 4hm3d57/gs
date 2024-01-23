#include "../include/glad/glad.h"
#include "../include/GLFW/glfw3.h"

#include <iostream>

#define WIDTH 800
#define HEIGHT 600

void resize_func(GLFWwindow *window, int width, int height);
void exit_key(GLFWwindow *window);

const char *vertexShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "layout (location = 1) in vec3 aColor;\n"
  "out vec3 ourColor;\n"
  "void main()\n"
  "{\n"
  "  gl_Position = vec4(aPos, 1.0);\n"
  "  ourColor = aColor;\n"
  "}\n\0";

const char *fragmentShaderSource = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "in vec3 ourColor;\n"
  "void main()\n"
  "{\n"
  "  FragColor = vec4(ourColor, 1.0f);\n"
  "}\n\0";

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

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);


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

  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  while(!glfwWindowShouldClose(window)){
    exit_key(window);
    glUseProgram(shaderProgram);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(VAO);
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
