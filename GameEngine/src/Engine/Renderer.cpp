#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Render(GLFWwindow* renderWindow) const
{
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);

	/*draw elements*/
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	/* Swap front and back buffers */
	glfwSwapBuffers(renderWindow);
}

void Renderer::SetBackgroundColor(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
}
