#include "Body/Cube.h"
#include "math/Math.h"
void Cube::initialize(void)
{
    _vertex = CreateCubeVertices(_dimenstion, math::Vec3(0.0f));
    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    glGenBuffers(1, &_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);//size 열의 개수
    glBufferData(GL_ARRAY_BUFFER, sizeof(math::Vec4) * _vertex.size(), _vertex.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    std::vector<math::Vec3> colors;
    colors.resize(_vertex.size(), _color);
    glGenBuffers(1, &_VCO);
    glBindBuffer(GL_ARRAY_BUFFER, _VCO);
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);//size 열의 개수
    glBufferData(GL_ARRAY_BUFFER, sizeof(math::Vec3) * colors.size(), colors.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    _buffer = _vertex;
}

void Cube::update(void)
{
    for (uint32 i = 0; i < _buffer.size(); ++i)
    {
        _buffer[i] = _translate * math::toMat4(_rot) * _vertex[i];
    }
}

void Cube::draw(void)
{
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(math::Vec4) * _buffer.size(), _buffer.data(), GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

std::vector<math::Vec4> Cube::CreateCubeVertices(const math::Vec3& dimensions, const math::Vec3& position) {
    float halfWidth = dimensions.x / 2.0f;
    float halfHeight = dimensions.y / 2.0f;
    float halfDepth = dimensions.z / 2.0f;

    std::vector<math::Vec4> vertices;
    vertices.reserve(36);

    math::Vec4 cubeVertices[8] = {
        math::Vec4(position.x - halfWidth, position.y - halfHeight, position.z - halfDepth, 1.0f),
        math::Vec4(position.x - halfWidth, position.y - halfHeight, position.z + halfDepth, 1.0f),
        math::Vec4(position.x - halfWidth, position.y + halfHeight, position.z + halfDepth, 1.0f),
        math::Vec4(position.x - halfWidth, position.y + halfHeight, position.z - halfDepth, 1.0f),
        math::Vec4(position.x + halfWidth, position.y - halfHeight, position.z - halfDepth, 1.0f),
        math::Vec4(position.x + halfWidth, position.y - halfHeight, position.z + halfDepth, 1.0f),
        math::Vec4(position.x + halfWidth, position.y + halfHeight, position.z + halfDepth, 1.0f),
        math::Vec4(position.x + halfWidth, position.y + halfHeight, position.z - halfDepth, 1.0f)
    };

    int indices[] = {
        1, 5, 6,  6, 2, 1,  // Front face
        4, 0, 3,  3, 7, 4,  // Back face
        0, 1, 2,  2, 3, 0,  // Left face
        5, 4, 7,  7, 6, 5,  // Right face
        2, 6, 7,  7, 3, 2,  // Top face
        5, 1, 0,  0, 4, 5   // Bottom face
    };

    for (int i = 0; i < 36; i++) {
        vertices.push_back(cubeVertices[indices[i]]);
    }

    return vertices;
}