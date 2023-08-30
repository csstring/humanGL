#pragma once
#include "Common.h"

class Shader : Noncopyable
{   
    public :
        explicit    Shader(const char* vertexRelativePath,const char* fragmentRelativePath);
        void        initialize(void);
        void        use(void);
        void        setMat4(const std::string &name, math::Mat4 mat4) const;
        void        setUint(const std::string &name, unsigned int index) const;
        void        setVec3(const std::string &name, math::Vec3 vec3) const;
        void        setFloat(const std::string &name, float index) const;
    public :
        uint32      _programId;

    private:
        std::string _vertexFullPath;
        std::string _fragmentFullPath;
};
