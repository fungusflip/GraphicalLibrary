#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "Matrix4x4.h"'

class GameObject
{
    const Mesh* mesh;
    Material* material;
    Texture* texture;

public:
    float red;
    Vector3 position = Vector3(0,0,0);
    Vector3 rotation = Vector3(0,0,0);

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

    GameObject (Material* _material, const Mesh* _mesh, Texture*_texture = nullptr) {
        mesh = _mesh;
        material = _material;
        texture = _texture;
    }

    void render() {

        material->use();

        Matrix4x4 matTranslation = Matrix4x4::Translation(position);
        Matrix4x4 matRotation = Matrix4x4::Rotation(rotation);



        Matrix4x4 transform = matTranslation * matRotation;
        int transformLocation = glGetUniformLocation(
            material->shaderProgram, "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_TRUE, &transform.m11);



        Matrix4x4 model = Matrix4x4::Translation(position) * Matrix4x4::Rotation(rotation);
        int modelLocation = glGetUniformLocation(
            material->shaderProgram, "model");
        glUniformMatrix4fv(modelLocation, 1, GL_TRUE, &model.m11);


        Matrix4x4 view = Matrix4x4::Translation(Vector3(0, 0, -3));
        int ViewLocation = glGetUniformLocation(
            material->shaderProgram, "view");
        glUniformMatrix4fv(ViewLocation, 1, GL_TRUE, &view.m11);

        Matrix4x4 projection = Matrix4x4::Perspective(45, 800 / 600, 0.1, 100.0f);
        int projectionLocation = glGetUniformLocation(
            material->shaderProgram, "projection");
        glUniformMatrix4fv(projectionLocation, 1, GL_TRUE, &projection.m11);



        glActiveTexture(GL_TEXTURE0);

        if (texture != nullptr) {
            glBindTexture(GL_TEXTURE_2D, texture->textureId);
        }
        else{
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        mesh->render();
    }
};

// extend the triangle to have data members (fields)
//    - red, green, blue CHECK
//    - pass those data members to your uniform
// in your main function:
//    - pass in red color (1,0,0) for the first CHECK
//    - and green color (0,1,0) for the second CHECK

// result: one red, one green triangle
//         both using the same shader (like in Unity)

// if done early: play around with meshes
// can you make any polygon?
// triangle, square, pentagon, hexagon, ...
