#include <glm/ext.hpp>
#include <exception>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Sphere.h"

Texture::Texture(std::string _filename)
{
    m_width = 0;
    m_height = 0;
    m_channels = 0;

    m_data = stbi_load(_filename.c_str(), &m_width, &m_height, &m_channels, 4);

    if (!m_data)
    {
      throw std::exception();
    }
}

Texture::~Texture()
{
    stbi_image_free(m_data);
}

int Texture::GetWidth()
{
    return m_width;
}

int Texture::GetHeight()
{
    return m_height;
}

unsigned char* Texture::GetData()
{
    return m_data;
}
