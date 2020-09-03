#ifndef BSPPLANE_H
#define BSPPLANE_H
#define EXPORTDLL _declspec(dllexport)

#include "glm/glm.hpp"

class EXPORTDLL BSPPlane
{
public:
	BSPPlane(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
	bool AreInSameSide(glm::vec3 point1, glm::vec3 point2);
private:
	glm::vec4 planeVector;
};

#endif