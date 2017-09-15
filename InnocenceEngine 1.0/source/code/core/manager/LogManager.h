#pragma once
#include "../interface/IEventManager.h"

class LogManager : public IEventManager
{
public:
	~LogManager();

	static LogManager& getInstance()
	{
		static LogManager instance;
		return instance;
	}
	void printLog(float logMessage);
	void printLog(std::string logMessage);
	void printLog(const glm::vec2& logMessage);
	void printLog(const glm::vec3& logMessage);
	void printLog(const glm::quat& logMessage);
	void printLog(const glm::mat4& logMessage);

private:
	LogManager();

	void initialize() override;
	void update() override;
	void shutdown() override;
};

