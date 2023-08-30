#include "Body/Line.h"

void Line::initialize(math::Vec3 color, uint32 VBC)
{
    math::Vec4 bottomPoint(0,0,0,1);
    math::Vec4 topPoint(0,0,-_length,1);
    std::vector<math::Vec3> colors;

    _vertices.push_back(_transForm * bottomPoint);
    _vertices.push_back(_transForm * topPoint);
    colors.push_back(color);
    colors.push_back(color);

    glBindBuffer(GL_ARRAY_BUFFER, VBC);
    glBufferData(GL_ARRAY_BUFFER, sizeof(math::Vec3) * colors.size(), colors.data(), GL_STATIC_DRAW);
}

void Line::render(uint32 VBO) const
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(math::Vec4) * _vertices.size(), _vertices.data(), GL_DYNAMIC_DRAW);
    glDrawArrays(GL_LINES, 0, 2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}