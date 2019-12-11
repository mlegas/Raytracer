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
    Texture(std::string _filename);
    glm::vec3 getTextureColourSphere(std::shared_ptr<Sphere> _sphere);
    glm::vec3 getTextureColourPlane();
    ~Texture();
};
