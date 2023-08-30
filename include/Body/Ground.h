#pragma once
#include "Common.h"
class Ground
{
    private:
        std::vector<math::Vec4> _groundVertex;
        // const float _groundVertex[16] = {100.0f,-10.0f,100.0f,1.0f, 100.0f,-10.0f,-100.0f,1.0f,-100.0f,-10.0f,100.0f,1.0f,-100.0f,-10.0f,-100.0f,1.0f};
        uint32 _VAO, _VBO, _VCO;
    public:
        Ground() : _rot(math::Mat4(1.0f)){};
        ~Ground()
        {
            glDeleteVertexArrays(1, &_VAO);
            glDeleteBuffers(1, &_VBO);
            glDeleteBuffers(1, &_VCO);
        };
        void initialize(void);
        void draw(void);
        void update(void);
        math::Vec3 getCenter(void) const;
        math::Mat4 _rot;
        math::Vec3 _normal;
};

