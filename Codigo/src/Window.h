#pragma once
#include <stdio.h>
#include <glew.h>
#include <glfw3.h>

class Window
{
public:
	Window() : mainWindow(nullptr), width(800), height(600), bufferWidth(0), bufferHeight(0),
		lastX(0), lastY(0), xChange(0), yChange(0), mouseFirstMoved(true) {}
	Window(GLint windowWidth, GLint windowHeight) : Window()
	{
		width = windowWidth;
		height = windowHeight;
	}

	int Initialise()
	{
		if (!glfwInit())
		{
			printf("Fallo inicializar GLFW\n");
			glfwTerminate();
			return 1;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		mainWindow = glfwCreateWindow(width, height, "Proyecto Final", NULL, NULL);
		if (!mainWindow)
		{
			printf("Fallo en crearse la ventana con GLFW\n");
			glfwTerminate();
			return 1;
		}
		glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
		glfwMakeContextCurrent(mainWindow);

		glfwSetWindowUserPointer(mainWindow, this);
		glfwSetKeyCallback(mainWindow, ManejaTeclado);
		glfwSetCursorPosCallback(mainWindow, ManejaMouse);
		glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			printf("Fallo GLEW: %s\n", glewGetErrorString(err));
			glfwDestroyWindow(mainWindow);
			glfwTerminate();
			return 1;
		}
		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, bufferWidth, bufferHeight);
		glfwSwapInterval(1);
		return 0;
	}

	GLfloat getBufferWidth() { return (GLfloat)bufferWidth; }
	GLfloat getBufferHeight() { return (GLfloat)bufferHeight; }
	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }
	bool* getsKeys() { return keys; }
	GLfloat getXChange() { GLfloat t = xChange; xChange = 0.0f; return t; }
	GLfloat getYChange() { GLfloat t = yChange; yChange = 0.0f; return t; }
	void swapBuffers() { glfwSwapBuffers(mainWindow); }

private:
	GLFWwindow* mainWindow;
	GLint width, height;
	GLint bufferWidth, bufferHeight;
	bool keys[1024] = { false };
	GLfloat lastX, lastY, xChange, yChange;
	bool mouseFirstMoved;

	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
	{
		Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		if (key >= 0 && key < 1024)
		{
			if (action == GLFW_PRESS) w->keys[key] = true;
			else if (action == GLFW_RELEASE) w->keys[key] = false;
		}
	}
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos)
	{
		Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
		if (w->mouseFirstMoved)
		{
			w->lastX = (GLfloat)xPos;
			w->lastY = (GLfloat)yPos;
			w->mouseFirstMoved = false;
		}
		w->xChange = (GLfloat)xPos - w->lastX;
		w->yChange = w->lastY - (GLfloat)yPos;
		w->lastX = (GLfloat)xPos;
		w->lastY = (GLfloat)yPos;
	}
};
