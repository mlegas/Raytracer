/** @file Texture.h
 *  @brief Class for storing texture data.
 */

#include <glm/vec3.hpp>
#include <memory>
#include <string>

class Sphere;

class Texture
{
private:
    int m_width;
    int m_height;
    int m_channels; ///< Channels stored by the image (usually 3 - RGB).
    unsigned char* m_data; ///< An 1D array of texture colour values.
public:
    /// @brief Returns the width of the texture.
    int GetWidth();
    /// @brief Returns the height of the texture.
    int GetHeight();
    /** @brief Loads a texture from the specified filename and stores it, constructing a Texture object.
     *  @param _filename The path to the texture.
     */
    Texture(std::string _filename);
    /// @brief Returns an 1D array of texture colour values.
    unsigned char* GetData();
    /// @brief Destroys the texture data using stb's function.
    ~Texture();
};
