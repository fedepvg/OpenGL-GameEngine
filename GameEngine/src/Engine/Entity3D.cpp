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
	worldModel = glm::mat4(1.f);
	regenerativeAABB = new BoundingBox();
	staticBoundingBox = new BoundingBox();
	
	if (sceneRoot == nullptr)
		parent = nullptr;
	else
		SetParent(sceneRoot);
}

Entity3D::Entity3D(glm::vec3 position, Entity3D* parent, Shader* shader)
{
	worldModel = glm::mat4(1.f);
	regenerativeAABB = new BoundingBox();
	staticBoundingBox = new BoundingBox();
	
	if (parent == nullptr && sceneRoot != nullptr)
		SetParent(sceneRoot);
	else
		SetParent(parent);
	this->shader = shader;
}

Entity3D::~Entity3D()
{
	delete regenerativeAABB;
}

void Entity3D::Rotate(float angle, glm::vec3 axis)
{
	localModel = glm::rotate(localModel, glm::radians(angle), axis);
	//UpdateModelMatrix();
	sceneRoot->UpdateModelMatAndBoundingBox();
}

void Entity3D::Scale(glm::vec3 scaleValues)
{
	localModel = glm::scale(localModel, scaleValues);
	scale *= scaleValues;
	//UpdateModelMatrix();
	sceneRoot->UpdateModelMatAndBoundingBox();
}

void Entity3D::Translate(float value, glm::vec3 axis)
{
	localModel = glm::translate(localModel, value * (axis));
	position += value * axis;
	//UpdateModelMatrix();
	sceneRoot->UpdateModelMatAndBoundingBox();
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

	Bounds cBounds;
	Bounds resultantBounds;
	
	for (unsigned int i = 0; i < childs.size(); i++)
	{
		cBounds = CombineBounds(childs[i]->UpdateModelMatAndBoundingBox(), cBounds);
	}

	VertexArray vertexArray = BoundingBox::GetBoxVertices(resultantBounds);

	for (int i=0; i<BOXVERTICES;i++)
	{
		vertexArray.actualVertexArray[i] = staticBoundingBox->GetVertex(i);
	}

	bounds = GenerateBoundsByTransformedVertex(vertexArray, worldModel);
	resultantBounds = CombineBounds(cBounds, bounds);
	
	regenerativeAABB->CalculateBoundingBox(resultantBounds);
	return resultantBounds;
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

	if(sceneRoot)
		sceneRoot->UpdateModelMatAndBoundingBox();
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

Bounds Entity3D::CombineBounds(Bounds bounds1, Bounds bounds2)
{
	Bounds newBounds;
	
	newBounds.minX = bounds1.minX <  bounds2.minX ? bounds1.minX :  bounds2.minX;
	newBounds.minY = bounds1.minY <  bounds2.minY ? bounds1.minY :  bounds2.minY;
	newBounds.minZ = bounds1.minZ <  bounds2.minZ ? bounds1.minZ :  bounds2.minZ;
	newBounds.maxX = bounds1.maxX >  bounds2.maxX ? bounds1.maxX :  bounds2.maxX;
	newBounds.maxY = bounds1.maxY >  bounds2.maxY ? bounds1.maxY :  bounds2.maxY;
	newBounds.maxZ = bounds1.maxZ >  bounds2.maxZ ? bounds1.maxZ :  bounds2.maxZ;

	return newBounds;
}

Bounds Entity3D::GenerateBoundsByVertex(VertexArray vertexArray)
{
	Bounds resetBounds;

	for (int i = 0; i < BOXVERTICES; i++)
	{
		if (vertexArray.actualVertexArray[i].x < resetBounds.minX)
			resetBounds.minX = vertexArray.actualVertexArray[i].x;
		if (vertexArray.actualVertexArray[i].x > resetBounds.maxX)
			resetBounds.maxX = vertexArray.actualVertexArray[i].x;
		if (vertexArray.actualVertexArray[i].y < resetBounds.minY)
			resetBounds.minY = vertexArray.actualVertexArray[i].y;
		if (vertexArray.actualVertexArray[i].y > resetBounds.maxY)
			resetBounds.maxY = vertexArray.actualVertexArray[i].y;
		if (vertexArray.actualVertexArray[i].z < resetBounds.minZ)
			resetBounds.minZ = vertexArray.actualVertexArray[i].z;
		if (vertexArray.actualVertexArray[i].z > resetBounds.maxZ)
			resetBounds.maxZ = vertexArray.actualVertexArray[i].z;
	}

	return resetBounds;
}

Bounds Entity3D::GenerateBoundsByTransformedVertex(VertexArray vArray, glm::mat4 modelMatrix)
{
	for (int i = 0; i < BOXVERTICES; i++)
	{
		vArray.actualVertexArray[i] = modelMatrix * glm::vec4(vArray.actualVertexArray[i], 1.f);
	}

	return GenerateBoundsByVertex(vArray);
}

void Entity3D::SetVisibility(bool visible)
{
	isVisible = visible;
	for (int i = 0; i < childs.size(); i++)
	{
		childs[i]->SetVisibility(visible);
	}
}

BoundingBox* Entity3D::GetBoundingBox()
{
	return regenerativeAABB;
}

void Entity3D::SetColliderVisibility(bool visibility)
{
	regenerativeAABB->SetVisibility(visibility);
	for (unsigned int i = 0; i < childs.size(); i++)
	{
		childs[i]->SetColliderVisibility(visibility);
	}
}

bool Entity3D::GetColliderVisibility() const
{
	return regenerativeAABB->GetVisibility();
}

std::string Entity3D::GetName()
{
	return name;
}

std::string Entity3D::GetTag()
{
	return tag;
}

bool Entity3D::isBSPPlane() const
{
	return  name.find("BSP") != string::npos;
}
