#include "../../../main/stdafx.h"
#include "SceneGraphManager.h"

SceneGraphManager::SceneGraphManager()
{
}


SceneGraphManager::~SceneGraphManager()
{
}


void SceneGraphManager::addToRenderingQueue(VisibleComponent* visibleComponent)
{
	m_visibleComponents.emplace_back(visibleComponent);
}

void SceneGraphManager::addToLightQueue(LightComponent * lightComponent)
{
	m_LightComponents.emplace_back(lightComponent);
}

std::vector<VisibleComponent*>& SceneGraphManager::getRenderingQueue()
{
	return m_visibleComponents;
}

std::vector<LightComponent*>& SceneGraphManager::getLightQueue()
{
	return m_LightComponents;
}


void SceneGraphManager::initialize()
{
	this->setStatus(objectStatus::ALIVE);
	LogManager::getInstance().printLog("SceneGraphManager has been initialized.");
}

void SceneGraphManager::update()
{
	//if (m_visibleComponents.size() == 0)
	//{
	//	this->setStatus(objectStatus::STANDBY);
	//	LogManager::getInstance().printLog("SceneGraphManager is stand-by.");
	//}
}

void SceneGraphManager::shutdown()
{
	m_visibleComponents.empty();
	m_LightComponents.empty();
	this->setStatus(objectStatus::SHUTDOWN);
	LogManager::getInstance().printLog("SceneGraphManager has been shutdown.");
}
