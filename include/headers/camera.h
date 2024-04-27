#pragma once

#include "../glad/glad.h"
#include "../GLFW/glfw3.h"

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

#define WIDTH 800
#define HEIGHT 600

class Camera{
    public:
        void see(unsigned int &shaderprog);
        void static mouse_callback(GLFWwindow* window, double xpos, double ypos);
        void static  scroll_back(GLFWwindow* window, double xoffset, double yoffset);
};
