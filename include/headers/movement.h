#pragma once


#include "../glad/glad.h"
#include "../GLFW/glfw3.h"

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"


class Movement{
    public:
        void songa(float x, float y, float z, unsigned int &shaderprog);
};

inline void Movement::songa(float x, float y, float z, unsigned int &shaderprog){
    float rotate_time = glfwGetTime();
    
    glm::mat4 move = glm::mat4(1.0f);
    move = glm::translate(move, glm::vec3(x, y, z));

    glm::mat4 rotation = glm::mat4(1.0f);
    rotation = glm::rotate(rotation, rotate_time, glm::vec3(1.0f, 1.0f, 1.0f));

    unsigned int moveLoc = glGetUniformLocation(shaderprog, "move");
    unsigned int rotationLoc = glGetUniformLocation(shaderprog, "rotation");
    glUniformMatrix4fv(moveLoc, 1, GL_FALSE, glm::value_ptr(move));
    glUniformMatrix4fv(rotationLoc, 1, GL_FALSE, glm::value_ptr(rotation));

}
