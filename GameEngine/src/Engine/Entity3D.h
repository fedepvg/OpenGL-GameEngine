#ifndef ENTITY3D_H
#define ENTITY3D_H
#define EXPORTDLL _declspec(dllexport)

#include "glm/glm.hpp"
#include <vector>

class EXPORTDLL Entity3D
{
public:
	Entity3D();
	Entity3D(glm::vec3 position, Entity3D* parent, class Shader* shader);

	//transformations
	void Rotate(float angle, glm::vec3 axis);
	void Translate(float value, glm::vec3 axis);
	void Scale(glm::vec3 scaleValues);
	void SetPosition(glm::vec3 newPosition);
	glm::mat4 GetModel();
	void SetModelMatrix(glm::mat4 modelMat);
	void SetParent(Entity3D* parent);
	Shader* GetShader();
	std::vector<Entity3D*> GetChilds();
	virtual void Draw();
	static void SetSceneRoot(Entity3D* root);

protected:
	glm::vec3 position;
	glm::vec3 scale;
	glm::mat4 model;
	Entity3D* parent;
	std::vector<Entity3D*> childs;
	Shader* shader;

private:
	static Entity3D* sceneRoot;

	friend class Model;
};

#endif