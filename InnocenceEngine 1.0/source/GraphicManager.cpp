#include "stdafx.h"
#include "GraphicManager.h"


GraphicManager::GraphicManager()
{
}


GraphicManager::~GraphicManager()
{
}

GLFWwindow * GraphicManager::getWindow()
{
	if (m_window != nullptr && glfwWindowShouldClose(m_window) == 0) {
		return m_window;
	}
	else
	{
		return nullptr;
	}
}

void GraphicManager::init()
{
	if (!glfwInit())
	{
		printLog("Failed to initialize GLFW.");
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

																   // Open a _window and create its OpenGL context
	m_window = glfwCreateWindow(1024, 768, "Test", NULL, NULL);
	if (m_window == NULL) {
		printLog("Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.");
		glfwTerminate();
	}
	glfwMakeContextCurrent(m_window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		printLog("Failed to initialize GLEW.");
	}

	m_renderingManager.exec(INIT);
	printLog("GraphicManager has been initialized.");
}

void GraphicManager::update()
{
	//fprintf(stdout, "Window is rendering.\n");
		if (m_window != nullptr && glfwWindowShouldClose(m_window) == 0) {
			m_renderingManager.exec(UPDATE);
			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}
		else 
		{
			printLog("Window has been closed!");
		}
}

void GraphicManager::shutdown()
{
	if (m_window)
	{
		m_renderingManager.exec(SHUTDOWN);
		glfwDestroyWindow(m_window);
		glfwTerminate();
		printLog("UIManager has been shutdown.");
	}
}