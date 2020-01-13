/** @file Texture.cpp
 *  @brief Implementation of functions for the Texture class.
 */

#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION ///< This define is necessary to use stb_image.
#include "stb_image.h"
#include <glm/ext.hpp>
#include <exception>

Texture::Texture(std::string _filename)
{
    m_width = 0;
    m_height = 0;
    m_channels = 0;

    /// Reads the texture data into m_data using stb's functions.
    m_data = stbi_load(_filename.c_str(), &m_width, &m_height, &m_channels, 0);

    /** If data could not be loaded, throw an exception.
     *  Usually this means a filename is incorrectly written. */
    if (!m_data)
    {
      throw std::exception();
    }
}

Texture::~Texture()
{
    /// Frees the m_data pointer.
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
