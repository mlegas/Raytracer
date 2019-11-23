#pragma once
#include <memory>

class Ray;

class Camera
{
public:
	std::shared_ptr<Ray> CreateRay(glm::ivec2 _pixelCoords);
	Camera();
	~Camera();
};

