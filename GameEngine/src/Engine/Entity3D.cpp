#include "Entity3D.h"

#include <iostream>

#include"glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"
#include "BoundingBox.h"
#include "Mesh.h"

Entity3D* Entity3D::sceneRoot = nullptr;

Entity3D::Entity3D()
{
	if (sceneRoot == nullptr)
		parent = nullptr;
	else
		SetParent(sceneRoot);

	worldModel = glm::mat4(1.f);
	boundingBox = new BoundingBox();
}

Entity3D::Entity3D(glm::vec3 position, Entity3D* parent, Shader* shader)
{
	if (parent == nullptr && sceneRoot != nullptr)
		SetParent(sceneRoot);
	else
		SetParent(parent);
	this->shader = shader;
	worldModel = glm::mat4(1.f);
	boundingBox = new BoundingBox();
}

Entity3D::~Entity3D()
{
	delete boundingBox;
}

void Entity3D::Rotate(float angle, glm::vec3 axis)
{
	localModel = glm::rotate(localModel, glm::radians(angle), axis);
	//UpdateModelMatrix();
	UpdateModelMatAndBoundingBox();
}

void Entity3D::Scale(glm::vec3 scaleValues)
{
	localModel = glm::scale(localModel, scaleValues);
	scale *= scaleValues;
	//UpdateModelMatrix();
	UpdateModelMatAndBoundingBox();
}

void Entity3D::Translate(float value, glm::vec3 axis)
{
	localModel = glm::translate(localModel, value * (axis));
	position += value * axis;
	//UpdateModelMatrix();
	UpdateModelMatAndBoundingBox();
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

Bounds Entity3D::UpdateModelMatAndBoundingBox()
{
	if (GetParent() != nullptr)
		worldModel = GetParent()->GetModel() * localModel;
	
	for (unsigned int i = 0; i < childs.size(); i++)
	{
		CalculateBounds(childs[i]->UpdateModelMatAndBoundingBox());
	}
	boundingBox->CalculateBoundingBox(bounds, worldModel);
	return bounds;
}

void Entity3D::SetParent(Entity3D* newParent)
{
	Entity3D* oldParent = parent;
	if (!newParent && sceneRoot)
		newParent = sceneRoot;
	else if(!newParent)
		return;
	
	newParent->childs.push_back(this);
	this->parent = newParent;
	this->localModel = inverse(parent->GetModel()) * worldModel;
	
	if(oldParent)
	{
		for (std::vector<Entity3D*>::iterator it = oldParent->GetChilds().begin(); it != oldParent->GetChilds().end(); ++it)
		{
			if ((*it) == this) 
			{
				oldParent->GetChilds().erase(it);
				break;
			}
		}
	}

	//newParent->UpdateModelMatAndBoundingBox();
}

Entity3D* Entity3D::GetParent()
{
	return parent;
}

Shader* Entity3D::GetShader()
{
	return shader;
}

std::vector<Entity3D*> & Entity3D::GetChilds()
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

void Entity3D::CalculateBounds(std::vector<glm::vec3> vertices)
{
	if (!vertices.empty())
	{
		Bounds resetBounds;
		bounds = resetBounds;
		for (int i = 0; i < vertices.size(); i++)
		{
			if (vertices[i].x < bounds.minX)
				bounds.minX = vertices[i].x;
			if (vertices[i].x > bounds.maxX)
				bounds.maxX = vertices[i].x;
			if (vertices[i].y < bounds.minY)
				bounds.minY = vertices[i].y;
			if (vertices[i].y > bounds.maxY)
				bounds.maxY = vertices[i].y;
			if (vertices[i].z < bounds.minZ)
				bounds.minZ = vertices[i].z;
			if (vertices[i].z > bounds.maxZ)
				bounds.maxZ = vertices[i].z;
		}
	}
}

void Entity3D::CalculateBounds(Bounds otherBounds)
{
	bounds.minX = bounds.minX < otherBounds.minX ? bounds.minX : otherBounds.minX;
	bounds.minY = bounds.minY < otherBounds.minY ? bounds.minY : otherBounds.minY;
	bounds.minZ = bounds.minZ < otherBounds.minZ ? bounds.minZ : otherBounds.minZ;
	bounds.maxX = bounds.maxX > otherBounds.maxX ? bounds.maxX : otherBounds.maxX;
	bounds.maxY = bounds.maxY > otherBounds.maxY ? bounds.maxY : otherBounds.maxY;
	bounds.maxZ = bounds.maxZ > otherBounds.maxZ ? bounds.maxZ : otherBounds.maxZ;
}

BoundingBox* Entity3D::GetBoundingBox()
{
	return boundingBox;
}

void Entity3D::SetColliderVisibility(bool visibility)
{
	boundingBox->SetVisibility(visibility);
	for (unsigned int i = 0; i < childs.size(); i++)
	{
		childs[i]->SetColliderVisibility(visibility);
	}
}

bool Entity3D::GetColliderVisibility() const
{
	return boundingBox->GetVisibility();
}
