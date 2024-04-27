#include "../include/headers/camera.h"

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float fov = 45.0f;



glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


void Camera::see(unsigned int &shaderprog){
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -20.0f));


    glm::mat4 lookat = glm::mat4(1.0f);
    lookat = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);


    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(fov), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

    unsigned int viewLoc = glGetUniformLocation(shaderprog, "view");
    unsigned int lookatLoc = glGetUniformLocation(shaderprog, "lookat");
    unsigned int projectionLoc = glGetUniformLocation(shaderprog, "projection");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(lookatLoc, 1, GL_FALSE, glm::value_ptr(lookat));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos){
    //position of the cursor set in the window
    float lastX = (float)WIDTH / 2;
    float lastY = (float)HEIGHT / 2;

    if(firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    //calculating the position of the cursor in the window
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    //sensitivity
    const float sensitivity = 0.001f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    //updating the yaw and pitch values
    yaw += xoffset;
    pitch += yoffset;

    //correcting pitch above 89.0f and -89.0f
    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = 89.0f;
    
    //direction right and left and up and down
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    cameraFront = glm::normalize(direction);

}

//zooming
void Camera::scroll_back(GLFWwindow* window, double xoffset, double yoffset){
    fov -= (float)yoffset;
    if(fov > 45.0f)
        fov = 45.0f;
    if(fov < 1.0f)
        fov = 1.0f;
}
