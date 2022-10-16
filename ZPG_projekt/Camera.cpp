#include "Camera.h"

glm::mat4 Camera::getCamera()
{
    return glm::lookAt(glm::vec3( 1.f ), glm::vec3( 1.f ), glm::vec3( 1.f ));
}
