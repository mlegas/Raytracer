#include "Sphere.h"
#include "Texture.h"

Texture::Texture(std::string _filename)
{
    m_pi = 3.1415926535897f;
}

glm::vec3 Texture::getTextureColourSphere(std::shared_ptr<Sphere> _sphere)
{
        float phi = atan2(_sphere->getIntersectionPoint().z, _sphere->getIntersectionPoint().x);
        float theta = asin(_sphere->getIntersectionPoint().y);
        float u = 1.0f - (phi + m_pi) / (2.0f * m_pi);
        float v = (theta + m_pi / 2.0f) / m_pi;

        int i = u * m_width;
        int j = (1 - v) * m_height - 0.001;

        if (i < 0) i = 0;
        if (j < 0) j = 0;

//        if (i > nx - 1) i = nx - 1;
//        if (j > ny - 1) j = ny - 1;

//        float r = int(data[3 * i + 3 * nx*j]  ) / 255.0;
//        float g = int(data[3 * i + 3 * nx*j+1]) / 255.0;
//        float b = int(data[3 * i + 3 * nx*j+2]) / 255.0;

//            return vec3(r, g, b);
}

//glm::vec3 Texture::getTextureColourPlane()
//{

//}
