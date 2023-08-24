#pragma once
#include "Common.h"
class Line
{
    public:
        float     _length;
        math::Mat4 _transForm;
        std::vector<math::Vec4> _vertices;

    public:
        Line(float length, math::Mat4 transForm) :_length(length), _transForm(transForm){};
        ~Line(){};
        void initialize(math::Vec3 color, uint32 VBC);
        void render(uint32 VBO) const;
    private:
};
