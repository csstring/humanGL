#pragma once
#include "Common.h"
#include "EnumHeader.h"

class Cylinder
{
    public:
        float     _radius;
        float     _heigth;
        uint32    _numSlices;
        math::Mat4 _transForm;
        uint32 _numVerticesSide;
        uint32 _numVerticesTopBottom;
        uint32 _numVerticesTotal;
        std::vector<math::Vec4> _vertices;
        std::vector<math::Vec4> _buffer;
    public:
        Cylinder(
            float radius, float height, uint32 numSilices, math::Mat4 transForm
        ) :_radius(radius), _heigth(height), _numSlices(numSilices), _transForm(transForm)
        {
            _numVerticesSide = (_numSlices + 1) * 2;
            _numVerticesTopBottom = _numSlices + 2;
            _numVerticesTotal = _numVerticesSide + _numVerticesTopBottom * 2;
        }
        ~Cylinder(){}
        void initialize(math::Vec3 color, uint32 VBC, BONEID ID);
        void render(uint32 vbo) const;
    private:
};
