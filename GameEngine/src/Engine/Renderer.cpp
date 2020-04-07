#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "LoadShader.h"

#include "Renderer.h"
#include "Texture.h"
#include "Entity.h"

#include "glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

Renderer::Renderer(Window* window)
{
	renderWindow = window->getWindow();

	viewMatrix = glm::lookAt(
		glm::vec3(0.f, 0.f, 1.5f), // position
		glm::vec3(0.0f, 0.0f, 0.0f), // look at
		glm::vec3(0.0f, 1.0f, 0.0f)  // up
	);

	//projMatrix = glm::ortho(0.f,800.f,0.f, 600.f, 0.f, 100.f);
	projMatrix = glm::ortho(-window->GetWidth()/2, window->GetWidth() / 2, -window->GetHeight() / 2, window->GetHeight() / 2, 0.f, 100.f);
	//projMatrix = glm::perspective(45.0f, window->GetWidth()/ window->GetHeight(), 0.f, 100.f);
	//projMatrix = glm::perspectiveFov(45.0f, window->GetWidth(), window->GetHeight(), 0.f, 100.f);

	SetShader();
}

Renderer::~Renderer()
{

}

void Renderer::Render(std::list<Entity*> objectList)// const
{
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);

	/*draw elements*/
	for (std::list<Entity*>::iterator it = objectList.begin(); it != objectList.end(); it++)
	{
		//(*it)->Render();
		RenderEntity(*it);
	}

	/* Swap front and back buffers */
	glfwSwapBuffers(renderWindow);
}

void Renderer::SetBackgroundColor(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
}

glm::mat4 Renderer::GetViewMatrix()
{
	return viewMatrix;
}

glm::mat4 Renderer::GetProjMatrix()
{
	return projMatrix;
}

void Renderer::SetShader()
{
	//load shaders
	programID = LoadShaders("../src/Engine/SimpleVertexShader.vertexshader", "../src/Engine/SimpleFragmentShader.fragmentshader");

	//use shader
	glUseProgram(programID);

	// Specify the layout of the vertex data
	GLuint posAttrib = glGetAttribLocation(programID, "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	GLuint colAttrib = glGetAttribLocation(programID, "customColor");
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(colAttrib);

	GLuint texAttrib = glGetAttribLocation(programID, "aTexCoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	//model = glm::mat4(1.0f);
	//model[3].x += position.x;
	//model[3].y += position.y;
	//model[3].z += position.z;
	////model[3].z += -500.f;

	/*uniModel = glGetUniformLocation(programID, "model");
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));*/

	GLint uniView = glGetUniformLocation(programID, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	GLint uniProj = glGetUniformLocation(programID, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(projMatrix));

	glUniform1i(glGetUniformLocation(programID, "tex"), 0);

	//position = glm::project({ 0,0,0 }, model, renderer->GetProjMatrix(), glm::vec4(0, 0, 800, 600));
}

void Renderer::RenderEntity(Entity* entityToRender) 
{
	glUseProgram(programID);
	glBindVertexArray(entityToRender->GetVertexArray());
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(entityToRender->GetModel()));


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, entityToRender->GetTexturePointer()->GetTexture());

	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(entityToRender->GetModel()));
	glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);
}