#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "GameObject.h"
#include "stb_image.h"
#include "Texture.h"
#include <vector>

using namespace std;

void processInput(GLFWwindow*);

int main() {


    Window window{ 800,600 }; // GLFW, GLAD, glViewport

    Texture container{ "container.jpg", GL_TEXTURE0 };
    Texture wall{ "wall.jpg", GL_TEXTURE1 };
    Texture face{ "awesomeface.png", GL_TEXTURE0 };

    Shader vertexShader{ "vertexShader.glsl", GL_VERTEX_SHADER };
    Shader textureShader{ "textureFragmentShader.glsl", GL_FRAGMENT_SHADER };
    Shader ColorShader{ "orangeFragmentShader.glsl", GL_FRAGMENT_SHADER };

    // -------- Create Orange Shader Program (Render Pipeline) ---------
    Material textured{ vertexShader, ColorShader };

    //Material textured{ textured, ColorShader };

    GameObject cube{ &textured, Mesh::createCylinder(4.0f, 10.0f, 10),};

    // Define chain parameters
    const int numCylinders = 10;
    const float cylinderSpacing = 2.0f;

    // Create a vector to hold the chain of cylinders


    // While the User doesn't want to Quit (X Button, Alt+F4)
    while (!window.shouldClose()) // window -> window.window
    {
        window.processInput();

        cube.position.x = glfwGetTime() * 1;

        cube.position.z = glfwGetTime() * -1;

        cube.rotation.z = glfwGetTime() * -1;

        cube.rotation.x = glfwGetTime() * -1;

        window.clear();

        cube.render();

        window.present();
    }
    // Cleans up all the GLFW stuff
    glfwTerminate();
    return 0;
}