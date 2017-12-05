#pragma once
#include "../../interface/IEventManager.h"
#include "../../manager/LogManager.h"

class GLWindowManager : public IEventManager
{
public:
	~GLWindowManager();

	void initialize() override;
	void update() override;
	void shutdown() override;

	static GLWindowManager& getInstance()
	{
		static GLWindowManager instance;
		return instance;
	}

	GLFWwindow* getWindow() const;
	glm::vec2 getScreenCenterPosition() const;
	glm::vec2 getScreenResolution() const;
	void setWindowName(const std::string& windowName);
	void hideMouseCursor() const;
	void showMouseCursor() const;

private:
	GLWindowManager();

	const unsigned int SCR_WIDTH = 1024;
	const unsigned int SCR_HEIGHT = 768;
	GLFWwindow* m_window;
	std::string m_windowName;
};

