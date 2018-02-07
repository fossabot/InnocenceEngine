#include "../../main/stdafx.h"
#include "TaskManager.h"

void TaskManager::setup()
{
	m_hardwareConcurrency =	std::thread::hardware_concurrency();
	this->setStatus(objectStatus::ALIVE);
}

void TaskManager::initialize()
{
	//for (unsigned int i = 0; i < m_hardwareConcurrency; ++i)
	//{
	//	m_threadPool.emplace_back(std::thread(&TaskManager::m_threadHolder, this));
	//}

	LogManager::getInstance().printLog("TaskManager has been initialized.");
}

void TaskManager::update()
{

}

void TaskManager::shutdown()
{
	this->setStatus(objectStatus::STANDBY);
	for (auto& i : m_threadPool)
	{
		if (i.joinable())
		{
			i.join();
		}
	}
	this->setStatus(objectStatus::SHUTDOWN);
	LogManager::getInstance().printLog("TaskManager has been shutdown.");
}

void TaskManager::addTask(std::function<void()>& task)
{
	m_mtx.lock();
	m_taskQueue.emplace_back(&task);
	m_mtx.unlock();
}

void TaskManager::m_threadHolder()
{
	do 
	{
		//if (m_taskQueue.size() > 0)
		//{
		//	(*m_taskQueue[0])();
		//}
	} 
	while (this->getStatus() == objectStatus::ALIVE);
}
