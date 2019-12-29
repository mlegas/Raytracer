#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <glm/vec3.hpp>
#include <memory>
#include <string>

class Sphere;

class Texture
{
private:
    int m_width;
    int m_height;
    int m_channels;
    unsigned char* m_data;
public:
    int GetWidth();
    int GetHeight();
    Texture(std::string _filename);
    unsigned char* GetData();
    ~Texture();
};

#endif
