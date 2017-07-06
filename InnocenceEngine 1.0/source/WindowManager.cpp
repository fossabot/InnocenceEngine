#include "stdafx.h"
#include "WindowManager.h"


WindowManager::WindowManager()
{
}


WindowManager::~WindowManager()
{
}

GLFWwindow * WindowManager::getWindow()
{
	return m_window;
}

void WindowManager::init()
{
	if (glfwInit() != GL_TRUE)
	{
		this->setStatus(ERROR);
		LogManager::printLog("Failed to initialize GLFW.");
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

																   // Open a window and create its OpenGL context
	m_window = glfwCreateWindow(1024, 768, "Test", NULL, NULL);
	if (m_window == nullptr) {
		this->setStatus(ERROR);
		LogManager::printLog("Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.");
		glfwTerminate();
	}
	glfwMakeContextCurrent(m_window); // Initialize GLEW
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		this->setStatus(ERROR);
		LogManager::printLog("Failed to initialize GLEW.");
	}
	this->setStatus(INITIALIZIED);
	LogManager::printLog("UIManager has been initialized.");
}

void WindowManager::update()
{
	if (m_window != nullptr && glfwWindowShouldClose(m_window) == 0) {
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
	else
	{
		this->setStatus(STANDBY);
		LogManager::printLog("UIManager is stand-by.");
	}
}

void WindowManager::shutdown()
{
	if (m_window != nullptr)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		this->setStatus(UNINITIALIZIED);
		LogManager::printLog("UIManager has been shutdown.");
	}
}