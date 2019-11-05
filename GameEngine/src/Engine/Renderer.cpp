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

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::SetShader()
{
	//load shaders
	programID = LoadShaders("../src/Engine/SimpleVertexShader.vertexshader", "../src/Engine/SimpleFragmentShader.fragmentshader");
	Texture tex("../res/texture.png");

	//use shader
	glUseProgram(programID);

	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation(programID, "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	GLint colAttrib = glGetAttribLocation(programID, "customColor");
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(colAttrib);

	GLint texAttrib = glGetAttribLocation(programID, "aTexCoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	myMatrix = glm::mat4(1.0f);
	uniModel = glGetUniformLocation(programID, "model");
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(myMatrix));

	glm::mat4 view = glm::lookAt(
		glm::vec3(0.f, 0.f, 1.5f), // position
		glm::vec3(0.0f, 0.0f, 0.0f), // look at
		glm::vec3(0.0f, 1.0f, 0.0f)  // up
	);
	GLint uniView = glGetUniformLocation(programID, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 proj = glm::ortho(-1.f, 1.f, -1.f, 1.f, 0.f, 100.f);
	GLint uniProj = glGetUniformLocation(programID, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	glUniform1i(glGetUniformLocation(programID, "tex"), 0);

	

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex.GetTexture());
}

void Renderer::Render(GLFWwindow* renderWindow, std::list<Entity*> objectList)// const
{
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);

	/*draw elements*/
	for (std::list<Entity*>::iterator it = objectList.begin(); it != objectList.end(); it++)
	{
		(*it)->Render();
	}

	/* Swap front and back buffers */
	glfwSwapBuffers(renderWindow);
}

void Renderer::SetBackgroundColor(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
}

//void Renderer::Rotate(float angle, glm::vec3 axis)
//{
//	myMatrix = glm::rotate(myMatrix, glm::radians(angle), axis);
//	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(myMatrix));
//}
//
//void Renderer::Scale(glm::vec3 scaleValues)
//{
//	myMatrix = glm::scale(myMatrix ,scaleValues);
//	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(myMatrix));
//}
//
//void Renderer::Translate(float value, glm::vec3 axis)
//{
//	myMatrix = glm::translate(myMatrix, value * axis);
//	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(myMatrix));
//}