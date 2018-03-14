#include "GameSystem.h"

void GameSystem::setup()
{
	if (g_pGame)
	{
		g_pLogSystem->printLog("Game loaded.");
		g_pGame->setup();

		m_CameraComponents = g_pGame->getCameraComponents();
		m_InputComponents = g_pGame->getInputComponents();
		m_LightComponents = g_pGame->getLightComponents();
		m_VisibleComponents = g_pGame->getVisibleComponents();

		g_pLogSystem->printLog("Game setup finished.");
		m_objectStatus = objectStatus::ALIVE;
	}
	else
	{
		g_pLogSystem->printLog("No game loaded!");
		m_objectStatus = objectStatus::STANDBY;
	}
}

void GameSystem::initialize()
{
	g_pGame->initialize();
}

void GameSystem::update()
{
	g_pGame->update();
}

void GameSystem::shutdown()
{
}

std::vector<VisibleComponent*>& GameSystem::getVisibleComponents()
{
	return m_VisibleComponents;
}

std::vector<LightComponent*>& GameSystem::getLightComponents()
{
	return m_LightComponents;
}

std::vector<CameraComponent*>& GameSystem::getCameraComponents()
{
	return m_CameraComponents;
}

std::vector<InputComponent*>& GameSystem::getInputComponents()
{
	return m_InputComponents;
}

std::string GameSystem::getGameName() const
{
	return g_pGame->getGameName();
}

bool GameSystem::needRender()
{
	return m_needRender;
}

const objectStatus & GameSystem::getStatus() const
{
	return m_objectStatus;
}
