#include "Window.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include "GameObject.h"
#include "Material.h"

// Forward declaration of Object class if necessary

class Camera{

    Window* window;

public:
    Camera(Window* window : window{window});
    Material* material;

    Vector3 cameraPos = Vector3(0.0f, 0.0f, 3.0f);                                                      //CameraPos

    Vector3 cameraFront = Vector3(0.0f, 0.0f, -1.0f);                                                  //CameraFront

    Vector3 cameraUp = Vector3(0.0f, 1.0f, 0.0f);                                                    //CameraFront

    Matrix4x4 view = Matrix4x4::LookAt(cameraPos, cameraPos + cameraFront, cameraUp);     

    /*
    int ViewLocation = glGetUniformLocation(
        GameObject::material->shaderProgram, "view");
    glUniformMatrix4fv(ViewLocation, 1, GL_TRUE, &view.m11);//Reversed front
    */

};


