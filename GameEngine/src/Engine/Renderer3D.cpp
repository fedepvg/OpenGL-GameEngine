#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"

#include "Renderer3D.h"
#include "Entity3D.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "BoundingBox.h"
#include "BSPPlane.h"

#include <list>
#include <algorithm>

vector<BSPPlane> Renderer3D::bspPlanes;

Renderer3D::Renderer3D(Window* window)
{
	renderWindow = window->getWindow();

	renderCamera = new Camera({ 0.f,0.f,100.f }, { 0.f,1.f,0.f }, { 0.f,0.f,-1.f }, -90.f, 0.f);

	projMatrix = glm::perspective(45.0f, window->GetWidth() / window->GetHeight(), 1.f, 1000.f);

	glm::mat4 vp = projMatrix * renderCamera->GetViewMatrix();
	frustum = Frustum(vp);

	glEnable(GL_DEPTH_TEST);
}

Renderer3D::~Renderer3D()
{

	delete renderCamera;
}

void Renderer3D::Draw(Entity3D* root)
{
	SetBackgroundColor(0.1f, 0.1f, 0.1f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 vp = projMatrix * renderCamera->GetViewMatrix();
	frustum = Frustum(vp);
	RenderEntity(root);
	glfwSwapBuffers(renderWindow);
}

void Renderer3D::RenderEntity(Entity3D* toRender)
{
	Mesh* thisMesh;
	thisMesh = dynamic_cast<Mesh*>(toRender);
	if (typeid(*toRender) == typeid(Mesh))
	{
		const bool found = (std::find(culledEntities.begin(), culledEntities.end(), toRender) != culledEntities.end());
		BoundingBox AABB = *toRender->GetBoundingBox();
		const bool isBSP = toRender->GetTag() == "bsp";
		
		if (isBSP || (frustum.IsBoxVisible(AABB.GetMinP(), AABB.GetMaxP()) && IsVisibleForBSP(AABB.GetMinP(), AABB.GetMaxP())))
		{
			thisMesh->GetShader()->Use();
			thisMesh->GetShader()->SetMat4("view", renderCamera->GetViewMatrix());
			thisMesh->GetShader()->SetMat4("proj", projMatrix);
			thisMesh->GetShader()->SetMat4("model", thisMesh->GetModel());

			SetTextures(thisMesh, thisMesh->GetTextures());
			if(isBSP)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glBindVertexArray(thisMesh->GetVertexArray());
			glDrawElements(GL_TRIANGLES, thisMesh->GetElementsSize(), GL_UNSIGNED_INT, 0);
			
			if (isBSP)
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			
			glActiveTexture(GL_TEXTURE0);
			glBindVertexArray(0);
			
			if (found)
				culledEntities.remove(toRender);
		}
		else
		{
			if (!found)
			{
				std::printf(thisMesh->GetName().c_str());
				culledEntities.push_back(toRender);
			}
		}
	}

	//toRender->GetBoundingBox()->Setup();
	toRender->GetBoundingBox()->Draw(renderCamera->GetViewMatrix(), projMatrix);

	for (int i = 0; i < toRender->GetChilds().size(); i++)
	{
		RenderEntity(toRender->GetChilds()[i]);
	}
}

void Renderer3D::SetTextures(Mesh* toRender, vector<TextureStruct> textures)
{
	for (int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		// now set the sampler to the correct texture unit
		toRender->GetShader()->SetInt(textures[i].type, i);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
}

void Renderer3D::SetBackgroundColor(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
}

glm::mat4 Renderer3D::GetProjMatrix()
{
	return projMatrix;
}

void Renderer3D::AddBSPPlane(BSPPlane newBSPPlane)
{
	bspPlanes.push_back(newBSPPlane);
}

bool Renderer3D::IsVisibleForBSP(glm::vec3 pos)
{
	for(int i = 0; i < bspPlanes.size(); i++)
	{
		if(!bspPlanes[i].AreInSameSide(pos, GetCamera()->GetPosition()))
			return false;
	}
	return true;
}

bool Renderer3D::IsVisibleForBSP(glm::vec3 boxMin, glm::vec3 boxMax)
{
	for (int i = 0; i < bspPlanes.size(); i++)
	{
		if (bspPlanes[i].AreInSameSide({ boxMin.x, boxMin.y, boxMin.z }, GetCamera()->GetPosition()))
			continue;
		if (bspPlanes[i].AreInSameSide({ boxMax.x, boxMin.y, boxMin.z }, GetCamera()->GetPosition()))
			continue;
		if (bspPlanes[i].AreInSameSide({ boxMin.x, boxMax.y, boxMin.z }, GetCamera()->GetPosition()))
			continue;
		if (bspPlanes[i].AreInSameSide({ boxMax.x, boxMax.y, boxMin.z }, GetCamera()->GetPosition()))
			continue;
		if (bspPlanes[i].AreInSameSide({ boxMin.x, boxMin.y, boxMax.z }, GetCamera()->GetPosition()))
			continue;
		if (bspPlanes[i].AreInSameSide({ boxMax.x, boxMin.y, boxMax.z }, GetCamera()->GetPosition()))
			continue;
		if (bspPlanes[i].AreInSameSide({ boxMin.x, boxMax.y, boxMax.z }, GetCamera()->GetPosition()))
			continue;
		if (bspPlanes[i].AreInSameSide({ boxMax.x, boxMax.y, boxMax.z }, GetCamera()->GetPosition()))
			continue;

		return false;
	}

	
	return true;
}

Camera* Renderer3D::GetCamera()
{
	return renderCamera;
}
