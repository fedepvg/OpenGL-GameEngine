#include "BSPPlane.h"

BSPPlane::BSPPlane(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3)
{
	glm::vec3 vecA = point1 - point2;
	glm::vec3 vecB = point3 - point2;

	glm::vec3 normal = glm::cross(vecA, vecB);
	float d = -1.f * (normal.x * point2.x + normal.y * point2.y + normal.z * point2.z);
	
	planeVector = glm::vec4(normal, d);
}

bool BSPPlane::AreInSameSide(glm::vec3 point1, glm::vec3 point2)
{
	float a = planeVector.x * point1.x + planeVector.y * point1.y + planeVector.z * point1.z + planeVector.w;
	float b = planeVector.x * point2.x + planeVector.y * point2.y + planeVector.z * point2.z + planeVector.w;

	if ((a > 0 && b > 0) || (a < 0 && b < 0) || (a == 0 || b == 0))
		return true;

	return false;
}

bool BSPPlane::IsInCameraSide(glm::vec3 point1)
{
	float a = planeVector.x * point1.x + planeVector.y * point1.y + planeVector.z * point1.z + planeVector.w;

	if ((a > 0 && cameraSide > 0) || (a < 0 && cameraSide < 0) || (a == 0 || cameraSide == 0))
		return true;

	return false;
}

bool BSPPlane::IsBoxInCameraSide(glm::vec3 boxMin, glm::vec3 boxMax)
{
	if (IsInCameraSide({ boxMin.x, boxMin.y, boxMin.z }) ||
		IsInCameraSide({ boxMax.x, boxMin.y, boxMin.z }) ||
		IsInCameraSide({ boxMin.x, boxMax.y, boxMin.z }) ||
		IsInCameraSide({ boxMax.x, boxMax.y, boxMin.z }) ||
		IsInCameraSide({ boxMin.x, boxMin.y, boxMax.z }) ||
		IsInCameraSide({ boxMax.x, boxMin.y, boxMax.z }) ||
		IsInCameraSide({ boxMin.x, boxMax.y, boxMax.z }) ||
		IsInCameraSide({ boxMax.x, boxMax.y, boxMax.z }))
	{
		return true;
	}

	return false;
}

float BSPPlane::CalculateSide(glm::vec3 point)
{
	return planeVector.x * point.x + planeVector.y * point.y + planeVector.z * point.z + planeVector.w;
}

void BSPPlane::SetCameraSide(float newCameraSide)
{
	cameraSide = newCameraSide;
}
