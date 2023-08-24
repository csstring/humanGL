#pragma once
#include "Common.h"

class Cube
{
    private:
        std::vector<math::Vec4> _buffer;
        uint32 _VAO, _VBO, _VCO;
        
    public:
        std::vector<math::Vec4> _vertex;
        math::Quat _rot;
        math::Mat4 _translate;
        math::Vec3 _position;
        math::Vec3 _dimenstion;
        math::Vec3 _color;

    private:
        std::vector<math::Vec4> CreateCubeVertices(const math::Vec3& dimensions, const math::Vec3& position);    
    
    public:
        Cube(math::Vec3 dimensions, math::Vec3 position, math::Vec3 color = math::Vec3(0,1,0)) : _dimenstion(dimensions), _position(position), _color(color)
        {
            _rot = math::Quat(1.0f, math::Vec3(0.0f));
            _translate = math::Mat4(1.0f);
        };
        ~Cube(){};
        void initialize(void);
        void draw(void);
        void update(void);
};

