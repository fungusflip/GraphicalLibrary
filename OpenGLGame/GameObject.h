#pragma once

#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "Matrix4x4.h"'
#include "GLFW/glfw3.h"

class GameObject
{
    const Mesh* mesh;
    Material* material;
    Texture* texture;
    

public:

    //More wizardry
    Vector3 position = Vector3(0, 0, 0);
    Vector3 rotation = Vector3(0, 0, 0);
    Vector3 LightningPos = Vector3(1,2,2);

    GameObject (Material* _material, const Mesh* _mesh, Texture*_texture = nullptr) {
        mesh = _mesh;
        material = _material;
        texture = _texture;
    }

    void render() {

        material->use();

        Matrix4x4 matTranslation = Matrix4x4::Translation(position);
        Matrix4x4 matRotation = Matrix4x4::Rotation(rotation);



        //Transform matrix
        Matrix4x4 transform = matTranslation * matRotation;
        int transformLocation = glGetUniformLocation(
            material->shaderProgram, "transform");
        glUniformMatrix4fv(transformLocation, 1, GL_TRUE, &transform.m11);



        //Model matrix
        Matrix4x4 model = Matrix4x4::Translation(position) * Matrix4x4::Rotation(rotation);
        int modelLocation = glGetUniformLocation(
            material->shaderProgram, "model");
        glUniformMatrix4fv(modelLocation, 1, GL_TRUE, &model.m11);



        const float radius = 10.0f;
        float time = glfwGetTime();
        float camX = radius;
        float camZ = radius;


        //Wizardry
        Vector3 cameraDirection = Vector3(0, 0, 0);
        Vector3 up = Vector3(0, 1, 0);

        // Initialize Cameraright and CameraUp using Vector3 and Matrix4x4 functions
        Vector3 Cameraright = Vector3::Cross(up, cameraDirection).Normalize();
        Vector3 CameraUp = Vector3::Cross(cameraDirection, Cameraright);


        //View Matrix
        Matrix4x4 view = Matrix4x4::LookAt(Vector3(camX, 0.0, camZ), Vector3(0,0,0), Vector3(0.0, 1.0, 0.0)).Inverse();
        int ViewLocation = glGetUniformLocation(
            material->shaderProgram, "view");
        glUniformMatrix4fv(ViewLocation, 1, GL_TRUE, &view.m11);

        Vector3 extractedCameraPosition(view.m14, view.m24, view.m34);

        //Projection Matrix
        Matrix4x4 projection = Matrix4x4::Perspective(45, 800 / 600, 0.1, 100.0f);
        int projectionLocation = glGetUniformLocation(
            material->shaderProgram, "projection");
        glUniformMatrix4fv(projectionLocation, 1, GL_TRUE, &projection.m11);


        int CameraPosLocation = glGetUniformLocation(material->shaderProgram, "cameraPos");
        glUniform3f(CameraPosLocation, extractedCameraPosition.x, extractedCameraPosition.y, extractedCameraPosition.z);

        // Lightning uniform
        int LightningLocation = glGetUniformLocation(material->shaderProgram, "LightningPos");
        glUniform3f(LightningLocation, LightningPos.x, LightningPos.y, LightningPos.z);

        int timeLocation = glGetUniformLocation(material->shaderProgram, "time");
        glUniform1f(timeLocation, time);

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