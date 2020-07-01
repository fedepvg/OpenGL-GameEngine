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

	worldModel = glm::mat4(1.f);
}

Entity3D::Entity3D(glm::vec3 position, Entity3D* parent, Shader* shader)
{
	if (parent == nullptr && sceneRoot != nullptr)
		SetParent(sceneRoot);
	else
		SetParent(parent);
	this->shader = shader;
	worldModel = glm::mat4(1.f);
}

void Entity3D::Rotate(float angle, glm::vec3 axis)
{
	localModel = glm::rotate(localModel, glm::radians(angle), axis);
	UpdateModelMatrix();
}

void Entity3D::Scale(glm::vec3 scaleValues)
{
	localModel = glm::scale(localModel, scaleValues);
	scale *= scaleValues;
	UpdateModelMatrix();
}

void Entity3D::Translate(float value, glm::vec3 axis)
{
	localModel = glm::translate(localModel, value * (axis));
	position += value * axis;
	UpdateModelMatrix();
}

void Entity3D::SetPosition(glm::vec3 newPosition)
{
	localModel[3].x = 0.f + newPosition.x;
	localModel[3].y = 0.f + newPosition.y;
	localModel[3].z = 0.f + newPosition.z;
}

glm::mat4 Entity3D::GetModel()
{
	return worldModel;
}

void Entity3D::UpdateModelMatrix()
{
	if(GetParent() != nullptr)
		worldModel = GetParent()->GetModel() * localModel;
		
	for (unsigned int i = 0; i < childs.size(); i++)
	{
		childs[i]->UpdateModelMatrix();
	}
}

void Entity3D::SetParent(Entity3D* newParent)
{
	if(newParent)
		newParent->childs.push_back(this);
	this->parent = newParent;
}

Entity3D* Entity3D::GetParent()
{
	return parent;
}

Shader* Entity3D::GetShader()
{
	return shader;
}

std::vector<Entity3D*> Entity3D::GetChilds()
{
	return childs;
}

Entity3D* Entity3D::GetNode(std::string node)
{
	Entity3D* toGet = nullptr;
	if (name == node)
		return this;
	else
	{
		for (unsigned int i = 0; i < childs.size(); i++)
		{
			toGet = childs[i]->GetNode(node);
			if (toGet != nullptr)
				break;
		}
	}
	return toGet;
}

void Entity3D::SetSceneRoot(Entity3D* root)
{
	sceneRoot = root;
}
