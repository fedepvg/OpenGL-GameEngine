#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Renderer3D.h"
#include "Entity3D.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "BoundingBox.h"


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
		BoundingBox AABB = *toRender->GetBoundingBox();
		if (frustum.IsBoxVisible(AABB.GetMinP(), AABB.GetMaxP()))
		{
			thisMesh->GetShader()->Use();
			thisMesh->GetShader()->SetMat4("view", renderCamera->GetViewMatrix());
			thisMesh->GetShader()->SetMat4("proj", projMatrix);
			thisMesh->GetShader()->SetMat4("model", thisMesh->GetModel());

			SetTextures(thisMesh, thisMesh->GetTextures());

			glBindVertexArray(thisMesh->GetVertexArray());
			glDrawElements(GL_TRIANGLES, thisMesh->GetElementsSize(), GL_UNSIGNED_INT, 0);
			glActiveTexture(GL_TEXTURE0);
			glBindVertexArray(0);
		}
		else
		{
			std::printf(thisMesh->GetName().c_str());
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

Camera* Renderer3D::GetCamera()
{
	return renderCamera;
}