#include "Window.h"
#include "Vector3.h"
#include "Matrix4x4.h"
#include "GameObject.h"

// Forward declaration of Object class if necessary
class Object;

class Camera {


    //Todo either reference view somehow. Or put this in gameobject. CameraClass could maybe be an alternative with position and rotation of it's own? It wouldn't need to render so that's good and yeah that would be  good sincne it only needs the numbers.
    const float radius = 10.0f;
    float time = glfwGetTime();
    float camX = sin(time) * radius;
    float camZ = cos(time) * radius;

    Vector3 cameraPos = Vector3(0.0f, 0.0f, 3.0f);
    Vector3 cameraTarget = Vector3(0, 0, 0);
    Vector3 cameraDirection = Vector3(0, 0, 0);
    Vector3 up = Vector3(0, 1, 0);

    // Initialize Cameraright and CameraUp using Vector3 and Matrix4x4 functions
    Vector3 Cameraright = Vector3::Cross(up, cameraDirection).Normalize();
    Vector3 CameraUp = Vector3::Cross(cameraDirection, Cameraright);

    

};


