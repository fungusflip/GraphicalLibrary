#include "Mesh.h"

const Color Color::red{ 1,0,0,1 };
const Color Color::green{ 0,1,0,1 };
const Color Color::blue{ 0,0,1,1 };
const Color Color::yellow{ 1,1,0,1 };

// NEW: define vertices
const Vertex Mesh::quadVertices[6]{
    // positions                           // colors        // texture coords
    Vertex{Vector3{ 0.5f,  0.5f, 0.0f},  Color::red,     Vector2{ 1.0f, 1.0f }},   // top right
    Vertex{Vector3{ 0.5f, -0.5f, 0.0f},  Color::green,   Vector2{ 1.0f, 0.0f }},   // bottom right
    Vertex{Vector3{-0.5f, -0.5f, 0.0f},  Color::blue,    Vector2{ 0.0f, 0.0f }},   // bottom left
    Vertex{Vector3{-0.5f,  0.5f, 0.0f},  Color::yellow,  Vector2{ 0.0f, 1.0f }},    // top left
    Vertex{Vector3{ 0.5f,  0.5f, 0.0f},  Color::red,     Vector2{ 1.0f, 1.0f }},   // top right
    Vertex{Vector3{-0.5f, -0.5f, 0.0f},  Color::blue,    Vector2{ 0.0f, 0.0f }},   // bottom left
};

// NEW: initialize the quad mesh as null
Mesh* Mesh::quadMesh{};

const Vertex Mesh::triangleVertices[3]{
    Vertex{Vector3{-0.5f, -0.5f, 0.0f}, Color::red},
    Vertex{Vector3{ 0.0f,  0.5f, 0.0f}, Color::green},
    Vertex{Vector3{ 0.5f, -0.5f, 0.0f}, Color::blue}
};

Mesh* Mesh::triangleMesh{};

const Vertex Mesh::cubeVertices[36]{
    // BACK SIDE
    Vertex{Vector3{ 0.5f,  0.5f, -0.5f},  Color::red,     Vector2{ 1.0f, 1.0f }},   // back top right
    Vertex{Vector3{ 0.5f, -0.5f, -0.5f},  Color::green,   Vector2{ 1.0f, 0.0f }},   // back bottom right
    Vertex{Vector3{-0.5f, -0.5f, -0.5f},  Color::blue,    Vector2{ 0.0f, 0.0f }},   // back bottom left
    Vertex{Vector3{-0.5f,  0.5f, -0.5f},  Color::yellow,  Vector2{ 0.0f, 1.0f }},    // back top left
    Vertex{Vector3{ 0.5f,  0.5f, -0.5f},  Color::red,     Vector2{ 1.0f, 1.0f }},   // back top right
    Vertex{Vector3{-0.5f, -0.5f, -0.5f},  Color::blue,    Vector2{ 0.0f, 0.0f }},   // back bottom left
    // FRONT SIDE
    Vertex{Vector3{ 0.5f,  0.5f, 0.5f},  Color::red,     Vector2{ 1.0f, 1.0f }},   // front top right
    Vertex{Vector3{ 0.5f, -0.5f, 0.5f},  Color::green,   Vector2{ 1.0f, 0.0f }},   // front bottom right
    Vertex{Vector3{-0.5f, -0.5f, 0.5f},  Color::blue,    Vector2{ 0.0f, 0.0f }},   // front bottom left
    Vertex{Vector3{-0.5f,  0.5f, 0.5f},  Color::yellow,  Vector2{ 0.0f, 1.0f }},    // front top left
    Vertex{Vector3{ 0.5f,  0.5f, 0.5f},  Color::red,     Vector2{ 1.0f, 1.0f }},   // front top right
    Vertex{Vector3{-0.5f, -0.5f, 0.5f},  Color::blue,    Vector2{ 0.0f, 0.0f }},   // front bottom left
    // TOP SIDE
    Vertex{Vector3{ 0.5f,  0.5f, -0.5f},  Color::red,     Vector2{ 1.0f, 1.0f }},   // back top right
    Vertex{Vector3{-0.5f,  0.5f, -0.5f},  Color::yellow,  Vector2{ 0.0f, 1.0f }},    // back top left
    Vertex{Vector3{ 0.5f,  0.5f, 0.5f},  Color::red,     Vector2{ 1.0f, 1.0f }},   // front top right
    Vertex{Vector3{ 0.5f,  0.5f, 0.5f},  Color::red,     Vector2{ 1.0f, 1.0f }},   // front top right
    Vertex{Vector3{-0.5f,  0.5f, 0.5f},  Color::yellow,  Vector2{ 0.0f, 1.0f }},    // front top left
    Vertex{Vector3{-0.5f,  0.5f, -0.5f},  Color::yellow,  Vector2{ 0.0f, 1.0f }},    // back top left
    // BOTTOM SIDE
    Vertex{Vector3{ 0.5f, -0.5f, -0.5f},  Color::red,     Vector2{ 1.0f, 1.0f }},   // back bottom right
    Vertex{Vector3{-0.5f, -0.5f, -0.5f},  Color::yellow,  Vector2{ 0.0f, 1.0f }},    // back bottom left
    Vertex{Vector3{ 0.5f, -0.5f, 0.5f},  Color::red,     Vector2{ 1.0f, 1.0f }},   // front bottom right
    Vertex{Vector3{ 0.5f, -0.5f, 0.5f},  Color::red,     Vector2{ 1.0f, 1.0f }},   // front bottom right
    Vertex{Vector3{-0.5f, -0.5f, 0.5f},  Color::yellow,  Vector2{ 0.0f, 1.0f }},    // front bottom left
    Vertex{Vector3{-0.5f, -0.5f, -0.5f},  Color::yellow,  Vector2{ 0.0f, 1.0f }},    // back bottom left
    // LEFT SIDE
    Vertex{Vector3{-0.5f,  0.5f, 0.5f},  Color::yellow,  Vector2{ 0.0f, 1.0f }},    // front top left
    Vertex{Vector3{-0.5f, -0.5f, 0.5f},  Color::blue,    Vector2{ 0.0f, 0.0f }},   // front bottom left
    Vertex{Vector3{-0.5f,  0.5f, -0.5f},  Color::yellow,  Vector2{ 0.0f, 1.0f }},    // back top left
    Vertex{Vector3{-0.5f, -0.5f, 0.5f},  Color::blue,    Vector2{ 0.0f, 0.0f }},   // front bottom left
    Vertex{Vector3{-0.5f,  0.5f, -0.5f},  Color::yellow,  Vector2{ 0.0f, 1.0f }},    // back top left
    Vertex{Vector3{-0.5f, -0.5f, -0.5f},  Color::blue,    Vector2{ 0.0f, 0.0f }},   // back bottom left
    // RIGHT SIDE
    Vertex{Vector3{0.5f,  0.5f, 0.5f},  Color::yellow,  Vector2{ 0.0f, 0.0f }},    // front top right
    Vertex{Vector3{0.5f, -0.5f, 0.5f},  Color::blue,    Vector2{ 0.0f, 0.0f }},   // front bottom right
    Vertex{Vector3{0.5f,  0.5f, -0.5f},  Color::yellow,  Vector2{ 0.0f, 0.0f }},    // back top right
    Vertex{Vector3{0.5f, -0.5f, 0.5f},  Color::blue,    Vector2{ 0.0f, 0.0f }},   // front bottom right
    Vertex{Vector3{0.5f,  0.5f, -0.5f},  Color::yellow,  Vector2{ 0.0f, 0.0f }},    // back top right
    Vertex{Vector3{0.5f, -0.5f, -0.5f},  Color::blue,    Vector2{ 0.0f, 0.0f }},   // back bottom right
};

Mesh* Mesh::cubeMesh{};