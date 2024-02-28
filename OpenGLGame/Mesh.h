#pragma once

#include "glad/glad.h"
#include <cstddef>
#include "../Maths/Vector3.h"
#include <algorithm>
#include <vector>
#include <cmath>

struct Vector2 {
    float x, y;
};

struct Color {

    static const Color red;
    static const Color green;
    static const Color blue;
    static const Color yellow;

    float r, g, b, a;
};

struct Vertex {
    Vector3 pos;
    Color col{ 1,1,1,1 };
    Vector2 uv; // texture coordinates
};

class Mesh
{
    unsigned int VAO;
    int vertexCount;

    const static Vertex quadVertices[6]; // NEW: declare vertices
    static Mesh* quadMesh; // NEW: declare quadMesh

    const static Vertex triangleVertices[3];
    static Mesh* triangleMesh;

    const static Vertex cubeVertices[36];
    static Mesh* cubeMesh;

    static std::vector<Vertex> cylinderVertices;
    static Mesh* cylinderMesh;
public:



    // public static method to create a quad mesh
    static const Mesh* createQuad() { // NEW: function to create (or get) a quad mesh
        if (quadMesh == nullptr) { // NEW: initialize, if not happened, yet
            quadMesh = new Mesh{ Mesh::quadVertices, std::size(Mesh::quadVertices) };
        }
        return quadMesh; // NEW: return quad mesh
    }

    static const Mesh* createTriangle() { // NEW: function to create (or get) a quad mesh
        if (triangleMesh == nullptr) { // NEW: initialize, if not happened, yet
            triangleMesh = new Mesh{ Mesh::triangleVertices, std::size(Mesh::triangleVertices) };
        }
        return triangleMesh; // NEW: return quad mesh
    }


    static const Mesh* createCylinder(float radius, float height, int segments) {
        const float PI = 3.14159265358979323846;
        const int vertexCount = segments * 6; // Two triangles per segment, 3 vertices per triangle

        // Allocate memory for the vertices array
        Vertex* vertices = new Vertex[vertexCount];

        // Create vertices for the side of the cylinder
        for (int i = 0; i < segments; ++i) {
            float theta1 = (2.0f * PI / segments) * i;
            float theta2 = (2.0f * PI / segments) * (i + 1);
            float x1 = radius * cos(theta1);
            float z1 = radius * sin(theta1);
            float x2 = radius * cos(theta2);
            float z2 = radius * sin(theta2);

            // Top triangle
            vertices[i * 6] = Vertex{ Vector3{x1, height / 2.0f, z1}, Color{1.0f, 0.0f, 0.0f}, Vector2{0.5f + x1 / (2.0f * radius), 0.5f + z1 / (2.0f * radius)} };
            vertices[i * 6 + 1] = Vertex{ Vector3{x1, -height / 2.0f, z1}, Color{0.0f, 0.0f, 1.0f}, Vector2{0.5f + x1 / (2.0f * radius), 0.5f + z1 / (2.0f * radius)} };
            vertices[i * 6 + 2] = Vertex{ Vector3{x2, height / 2.0f, z2}, Color{1.0f, 0.0f, 0.0f}, Vector2{0.5f + x2 / (2.0f * radius), 0.5f + z2 / (2.0f * radius)} };

            // Bottom triangle
            vertices[i * 6 + 3] = Vertex{ Vector3{x2, height / 2.0f, z2}, Color{1.0f, 0.0f, 0.0f}, Vector2{0.5f + x2 / (2.0f * radius), 0.5f + z2 / (2.0f * radius)} };
            vertices[i * 6 + 4] = Vertex{ Vector3{x1, -height / 2.0f, z1}, Color{0.0f, 0.0f, 1.0f}, Vector2{0.5f + x1 / (2.0f * radius), 0.5f + z1 / (2.0f * radius)} };
            vertices[i * 6 + 5] = Vertex{ Vector3{x2, -height / 2.0f, z2}, Color{0.0f, 0.0f, 1.0f}, Vector2{0.5f + x2 / (2.0f * radius), 0.5f + z2 / (2.0f * radius)} };
        }

        // Create a mesh object using the generated vertices
        const Mesh* cylinderMesh = new Mesh(vertices, vertexCount);

        // Deallocate the vertices array
        delete[] vertices;

        return cylinderMesh;
    }

    static const Mesh* createChainLink(float majorRadius, float minorRadius, int majorSegments, int minorSegments) {
        const float PI = 3.14159265358979323846f;
        const int vertexCount = majorSegments * minorSegments * 6; // Two triangles per segment, 3 vertices per triangle

        // Allocate memory for the vertices array
        Vertex* vertices = new Vertex[vertexCount];

        // Create vertices for the torus
        for (int i = 0; i < majorSegments; ++i) {
            float theta1 = (2.0f * PI / majorSegments) * i;
            float theta2 = (2.0f * PI / majorSegments) * ((i + 1) % majorSegments);
            float x1 = majorRadius * cos(theta1);
            float z1 = majorRadius * sin(theta1);
            float x2 = majorRadius * cos(theta2);
            float z2 = majorRadius * sin(theta2);

            for (int j = 0; j < minorSegments; ++j) {
                float phi1 = (2.0f * PI / minorSegments) * j;
                float phi2 = (2.0f * PI / minorSegments) * ((j + 1) % minorSegments);
                float y1 = minorRadius * cos(phi1);
                float y2 = minorRadius * cos(phi2);
                float y3 = minorRadius * sin(phi1);
                float y4 = minorRadius * sin(phi2);

                // Top triangle
                vertices[(i * minorSegments + j) * 6] = Vertex{ Vector3{x1 + y1, y3, z1 + y1}, Color{1.0f, 0.0f, 0.0f}, Vector2{(float)i / majorSegments, (float)j / minorSegments} };
                vertices[(i * minorSegments + j) * 6 + 1] = Vertex{ Vector3{x1 + y2, y3, z1 + y2}, Color{0.0f, 0.0f, 1.0f}, Vector2{(float)i / majorSegments, (float)(j + 1) / minorSegments} };
                vertices[(i * minorSegments + j) * 6 + 2] = Vertex{ Vector3{x2 + y1, y4, z2 + y1}, Color{1.0f, 0.0f, 0.0f}, Vector2{(float)(i + 1) / majorSegments, (float)j / minorSegments} };

                // Bottom triangle
                vertices[(i * minorSegments + j) * 6 + 3] = Vertex{ Vector3{x2 + y1, y4, z2 + y1}, Color{1.0f, 0.0f, 0.0f}, Vector2{(float)(i + 1) / majorSegments, (float)j / minorSegments} };
                vertices[(i * minorSegments + j) * 6 + 4] = Vertex{ Vector3{x1 + y2, y3, z1 + y2}, Color{0.0f, 0.0f, 1.0f}, Vector2{(float)i / majorSegments, (float)(j + 1) / minorSegments} };
                vertices[(i * minorSegments + j) * 6 + 5] = Vertex{ Vector3{x2 + y2, y4, z2 + y2}, Color{0.0f, 0.0f, 1.0f}, Vector2{(float)(i + 1) / majorSegments, (float)(j + 1) / minorSegments} };
            }
        }

        // Create a mesh object using the generated vertices
        const Mesh* torusMesh = new Mesh(vertices, vertexCount);

        // Deallocate the vertices array
        delete[] vertices;

        return torusMesh;
    }


    static const Mesh* createCube() { // NEW: function to create (or get) a quad mesh
        if (!cubeMesh) { // NEW: initialize, if not happened, yet
            cubeMesh = new Mesh{ Mesh::cubeVertices, std::size(Mesh::cubeVertices) };
        }
        return cubeMesh; // NEW: return quad mesh
    }

    void render() const {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }

    Mesh(const Vertex* vertices, size_t count) {
        vertexCount = count;
        // ----- Create Vertex Array Object, which makes changing between VBOs easier -----
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // ----- Create Array Buffer on the GPU and copy our vertices to GPU -------
        unsigned int VBO; // variable to store buffer id
        glGenBuffers(1, &VBO); // ask open gl to create a buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO); // tell gl to use this buffer
        glBufferData(GL_ARRAY_BUFFER, // copy our vertices to the buffer
            sizeof(Vertex) * count, vertices, GL_STATIC_DRAW);

        // ------ configure vertex attribute(s) (currently it's just one, the position) -----
        // so the vertex shader understands, where to find the input attributes, in this case position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
            sizeof(Vertex), (void*)offsetof(Vertex, pos));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
            sizeof(Vertex), (void*)offsetof(Vertex, col));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
            sizeof(Vertex), (void*)offsetof(Vertex, uv));
        glEnableVertexAttribArray(2);
    }
};