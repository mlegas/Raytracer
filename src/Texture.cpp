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

//glm::vec3 Texture::getTextureColourSphere(std::shared_ptr<Sphere> _sphere)
//{
//        float phi = atan2(_sphere->getIntersectionPoint().x, _sphere->getIntersectionPoint().z);
//        float theta = asin(_sphere->getIntersectionPoint().y);
//        float u = (phi + M_PI) / (2.0f * M_PI);
//        float v = (theta + M_PI / 2.0f) / M_PI;

//        int i = u * m_width;
//        int j = (1.0f - v) * m_height;

//        if (i < 0)
//        {
//            i = 0;
//        }

//        else if (i > m_width - 1)
//        {
//            i = m_width - 1;
//        }

//        if (j < 0)
//        {
//            j = 0;
//        }

//        else if (j > m_height - 1)
//        {
//            j = m_height - 1;
//        }

//        float r = m_data[3 * i + 3 * m_width * j];
//        float g = m_data[3 * i + 3 * m_width * j + 1];
//        float b = m_data[3 * i + 3 * m_width * j + 2];

//        return glm::vec3(r, g, b);
//}

//glm::vec3 Texture::getTextureColourPlane()
//{
//vec3 computePrimaryTexDir(vec3 normal)
//{
//    vec3 a = cross(normal, vec3(1, 0, 0));
//    vec3 b = cross(normal, vec3(0, 1, 0));

//    vec3 max_ab = dot(a, a) < dot(b, b) ? b : a;

//    vec3 c = cross(normal, vec3(0, 0, 1));

//    return normalize(dot(max_ab, max_ab) < dot(c, c) ? c : max_ab);
//}

//  …

//    vec3 u = computePrimaryTexDir(normal);
//    vec3 v = cross(n, u);
//}
