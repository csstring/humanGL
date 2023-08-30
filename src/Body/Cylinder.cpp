#include "Body/Cylinder.h"
#include <cmath>
#include "EnumHeader.h"
#include "math/Math.h"
void Cylinder::initialize(math::Vec3 color, uint32 VBC, BONEID ID)
{
    const float angleStep = 2.0f * PI / static_cast<float>(_numSlices);
    float curAngle = 0.0f;
    std::vector<math::Vec3> cylinderPos;
    if (ID == BONEID::HEAD)
    {
        _transForm = math::rotate(_transForm, math::radians(45.0f), math::Vec3(0,0,1));
    }
    cylinderPos.reserve(_numSlices);
    for (uint32 i = 0; i <= _numSlices; ++i)
    {
        math::Vec3 pos;

        pos.x = cos(curAngle) * _radius;
        pos.y = sin(curAngle) * _radius;
        cylinderPos.push_back(pos);
        curAngle += angleStep;
    }

    _vertices.reserve(_numVerticesTotal);
    for (const math::Vec3& pos : cylinderPos)
    {
        math::Vec4 vertexTop(pos.x, pos.y , -0 ,1);
        math::Vec4 vertexBottom(pos.x, pos.y, _heigth, 1);

        _vertices.push_back(_transForm * vertexTop);
        _vertices.push_back(_transForm * vertexBottom);
    }

    math::Vec4 topCenter(0, 0, -0, 1);
    _vertices.push_back(_transForm * topCenter);
    for (const math::Vec3& pos :cylinderPos)
    {
        math::Vec4 vertexTop(pos.x, pos.y , -0 ,1);
        _vertices.push_back(_transForm * vertexTop);
    }

    math::Vec4 bottomCenter(0, 0, _heigth, 1);
    _vertices.push_back(_transForm * bottomCenter);
    for (const math::Vec3& pos :cylinderPos)
    {
        math::Vec4 vertexBottom(pos.x, pos.y, _heigth, 1);
        _vertices.push_back(_transForm * vertexBottom);
    }

    std::vector<math::Vec3> colors;
    colors.resize(_vertices.size(), color);
    if (ID == BONEID::HEAD)
    {
        uint32 rightEyePoint = _numVerticesSide*2/16;
        uint32 leftEyePoint = _numVerticesSide*5/16;

        colors[rightEyePoint-2] = math::Vec3(1,0,0);
        colors[rightEyePoint-1] = math::Vec3(1,0,0);
        colors[leftEyePoint-2] = math::Vec3(1,0,0);
        colors[leftEyePoint-1] = math::Vec3(1,0,0);
    }
    _buffer = _vertices;
    glBindBuffer(GL_ARRAY_BUFFER, VBC);
    glBufferData(GL_ARRAY_BUFFER, sizeof(math::Vec3) * colors.size(), colors.data(), GL_STATIC_DRAW);
}

void Cylinder::render(uint32 VBO) const
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(math::Vec4) * _vertices.size(), _vertices.data(), GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, _numVerticesSide);
    glDrawArrays(GL_TRIANGLE_FAN, _numVerticesSide, _numVerticesTopBottom);
    glDrawArrays(GL_TRIANGLE_FAN, _numVerticesSide + _numVerticesTopBottom, _numVerticesTopBottom);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}