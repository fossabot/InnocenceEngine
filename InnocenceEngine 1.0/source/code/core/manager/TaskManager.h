#pragma once
#include "../interface/IEventManager.h"
#include "LogManager.h"

class TaskManager : public IEventManager
{
public:
	TaskManager();

	void setup() override;
	void initialize() override;
	void update() override;
	void shutdown() override;

	static TaskManager& getInstance()
	{
		static TaskManager instance;
		return instance;
	}

private:
	~TaskManager();

	unsigned int m_hardwareConcurrency;
	std::vector<std::thread> m_threadPool;
};

