#ifndef ENTITY_H
#define ENTITY_H
#define EXPORTDLL _declspec(dllexport)

//#include "../libs/glm/glm.hpp"
#include "../libs/glm/glm/glm.hpp"
//#include"glm/gtc/matrix_transform.hpp"
//#include "glm/gtc/type_ptr.hpp"
//#include "glm/gtx/transform.hpp"

class EXPORTDLL Entity
{
protected:
	glm::vec3 position;
	glm::mat4 myMatrix;
	unsigned int uniModel;
	unsigned int programID;
public:
	Entity();
	Entity(glm::vec3 pos);
	void SetShader();
	void Rotate(float angle, glm::vec3 axis);
	void Translate(float value, glm::vec3 axis);
	void Scale(glm::vec3 scaleValues);
};
#endif