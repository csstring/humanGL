#pragma once
#include "Common.h"
#include <string>
class Skeleton;
struct Bone;
class Animation;
class CmuFileParser : Noncopyable
{
    public : 
        explicit CmuFileParser(
            std::string filePath, 
            Skeleton* skeleton,
            Animation* animation
        ) : _skeleton(skeleton), _animation(animation)
        {
            std::filesystem::path amcPath(filePath);
            if (std::filesystem::exists(amcPath) == false)
                ft_exit("asf file path fail");
            _filePath = std::filesystem::canonical(amcPath);
        };

        ~CmuFileParser()
        {
            _skeleton = NULL;
            _animation = NULL;
        };

        bool              loadCmuFile();
        bool              parseAsfUnits(std::ifstream& ifs);
        bool              parseAsfRoot(std::ifstream& ifs);
        bool              parseAsfBoneData(std::ifstream& ifs);
        bool              parseAsfHierarchy(std::ifstream& ifs);
        bool              parserAsfDof(std::ifstream& ifs, Bone& bone);

    private:
        std::string _filePath;
        Skeleton*         _skeleton;
        Animation*        _animation;
};