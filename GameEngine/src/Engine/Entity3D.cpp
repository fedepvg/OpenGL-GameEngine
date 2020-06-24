#include "Entity3D.h"

#include <iostream>

#include"glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"

Entity3D* Entity3D::sceneRoot = nullptr;

Entity3D::Entity3D()
{
	if (sceneRoot == nullptr)
		parent = nullptr;
	else
		SetParent(sceneRoot);
	model = glm::mat4(1.0f);
	SetPosition(glm::vec3(0.f));
}

Entity3D::Entity3D(glm::vec3 position, Entity3D* parent, Shader* shader)
{
	model = glm::mat4(1.0f);
	SetPosition(position);
	if (parent == nullptr && sceneRoot != nullptr)
		SetParent(sceneRoot);
	else
		SetParent(parent);
	this->shader = shader;
}

void Entity3D::Rotate(float angle, glm::vec3 axis)
{
	model = glm::rotate(model, glm::radians(angle), axis);
}

void Entity3D::Scale(glm::vec3 scaleValues)
{
	model = glm::scale(model, scaleValues);
	scale *= scaleValues;
	std::cout << scale.x << std::endl;
}

void Entity3D::Translate(float value, glm::vec3 axis)
{
	model = glm::translate(model, value * (axis* 0.01f));
	position += value * axis;
}

void Entity3D::SetPosition(glm::vec3 newPosition)
{
	model[3].x = 0.f + newPosition.x;
	model[3].y = 0.f + newPosition.y;
	model[3].z = 0.f + newPosition.z;
}

glm::mat4 Entity3D::GetModel()
{
	return model;
}

void Entity3D::SetModelMatrix(glm::mat4 modelMat)
{
	model = modelMat;
	for (unsigned int i = 0; i < childs.size(); i++)
	{
		//childs[i]->SetModelMatrix()
	}
}

void Entity3D::SetParent(Entity3D* newParent)
{
	if(newParent)
		newParent->childs.push_back(this);
	this->parent = newParent;
}

Shader* Entity3D::GetShader()
{
	return shader;
}

std::vector<Entity3D*> Entity3D::GetChilds()
{
	return childs;
}

void Entity3D::Draw()
{
	for (unsigned int i = 0; i < childs.size(); i++)
		childs[i]->Draw();
}

void Entity3D::SetSceneRoot(Entity3D* root)
{
	sceneRoot = root;
}
