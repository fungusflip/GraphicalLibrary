#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "../Maths/Matrix4x4.h"

class GameObject
{
    const Mesh* mesh;
    Material* material;
    Texture* texture;

public:
    float red;
    Vector3 position = Vector3(0,0,0);
    Vector3 rotation = Vector3(0,0,0);
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


        //TODO ADD REFERENCE TO WINDOW for aspect ratio 
        Matrix4x4 projection = Matrix4x4::Perspective(45, 800 / 600, 0.1, 100.0f);
        
        Matrix4x4 view = Matrix4x4::Translation(Vector3(0, 0, -3));

        int transformLocation = glGetUniformLocation(
            material->shaderProgram, "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_TRUE, &transform.m11);


        int ViewLocation = glGetUniformLocation(
            material->shaderProgram, "view");
        glUniformMatrix4fv(ViewLocation, 1, GL_TRUE, &view.m11);


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
