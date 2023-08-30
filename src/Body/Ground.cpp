#include "Body/Ground.h"
#include "math/Math.h"
void Ground::initialize(void)
{
    _groundVertex = {math::Vec4(10.0f,-10.0f,10.0f,1.0f),math::Vec4(10.0f,-10.0f,-10.0f,1.0f),math::Vec4(-10.0f,-10.0f,10.0f,1.0f), math::Vec4(-10.0f,-10.0f,-10.0f,1.0f)};
    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    glGenBuffers(1, &_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);//size 열의 개수
    glBufferData(GL_ARRAY_BUFFER, sizeof(math::Vec4) * _groundVertex.size(), _groundVertex.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    std::vector<math::Vec3> colors = {math::Vec3(1,0,0),math::Vec3(0,1,0),math::Vec3(0,0,1),math::Vec3(1,0,0)};
    glGenBuffers(1, &_VCO);
    glBindBuffer(GL_ARRAY_BUFFER, _VCO);
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);//size 열의 개수
    glBufferData(GL_ARRAY_BUFFER, sizeof(math::Vec3) * colors.size(), colors.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
}

void Ground::update(void)
{
    for (auto& it : _groundVertex)
        it = _rot * it;
    math::Vec4 center(0.0f);
    for (const auto& it : _groundVertex)
        center += it;
    center /= 4;
    math::Vec3 point0 = math::normalize(math::Vec3(_groundVertex[0] - center));
    math::Vec3 point1 = math::normalize(math::Vec3(_groundVertex[1] - center));
    _normal = math::cross(point0, point1);
    _rot = math::Mat4(1.0f);
}

math::Vec3 Ground::getCenter(void) const
{
    math::Vec4 center(0.0f);
    for (const auto& it : _groundVertex)
        center += it;
    center /= 4;
    return math::Vec3(center);
}

void Ground::draw(void) //깊이버퍼 이상한데?
{
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(math::Vec4) * _groundVertex.size(), _groundVertex.data(), GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}