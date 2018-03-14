#include "CoreSystem.h"

void CoreSystem::setup()
{
	g_pMemorySystem = new INNO_MEMORY_System;
	g_pMemorySystem->setup();
	g_pLogSystem = g_pMemorySystem->spawn<INNO_LOG_System>();
	g_pLogSystem->setup();
	//g_pTaskSystem = g_pMemorySystem->spawn<INNO_TASK_System>();
	g_pTimeSystem = g_pMemorySystem->spawn<INNO_TIME_System>();
	g_pTimeSystem->setup();
	g_pLogSystem->printLog("MemorySystem setup finished.");
	g_pLogSystem->printLog("LogSystem setup finished.");
	g_pLogSystem->printLog("TimeSystem setup finished.");
	g_pRenderingSystem = g_pMemorySystem->spawn<INNO_RENDERING_System>();
	g_pRenderingSystem->setup();
	g_pLogSystem->printLog("RenderingSystem setup finished.");
	g_pAssetSystem = g_pMemorySystem->spawn<INNO_ASSET_System>();
	g_pAssetSystem->setup();
	g_pLogSystem->printLog("AssetSystem setup finished.");
	g_pGameSystem = g_pMemorySystem->spawn<INNO_GAME_System>();
	g_pGameSystem->setup();
	g_pLogSystem->printLog("GameSystem setup finished.");
	if (g_pGameSystem->getStatus() == objectStatus::ALIVE)
	{
		GLWindowSystem::getInstance().setWindowName(g_pGameSystem->getGameName());
		m_objectStatus = objectStatus::ALIVE;
		g_pLogSystem->printLog("CoreSystem setup finished.");
	}
	else
	{
		m_objectStatus = objectStatus::STANDBY;
		g_pLogSystem->printLog("CoreSystem stand-by.");
	}
}

void CoreSystem::initialize()
{
	g_pMemorySystem->initialize();
	g_pLogSystem->initialize();
	g_pTimeSystem->initialize();
	g_pRenderingSystem->initialize();
	g_pAssetSystem->initialize();
	g_pGameSystem->initialize();

	g_pLogSystem->printLog("CoreSystem has been initialized.");
}

void CoreSystem::update()
{
	// time System should update without any limitation.
	g_pTimeSystem->update();

	// a frame counter occurred.
	// @TODO: Async rendering
	if (g_pTimeSystem->getStatus() == objectStatus::ALIVE)
	{
		if (g_pRenderingSystem->getStatus() == objectStatus::ALIVE)
		{
			auto l_tickTime = g_pTimeSystem->getcurrentTime();
			// game simulation
			g_pGameSystem->update();

			if (g_pGameSystem->needRender())
			{
				g_pRenderingSystem->render();
			}

			g_pRenderingSystem->update();
			l_tickTime = g_pTimeSystem->getcurrentTime() - l_tickTime;
#ifdef DEBUG
			//g_pMemorySystem->dumpToFile("../" + g_pTimeSystem->getCurrentTimeInLocal() + ".innoMemoryDump");
#endif // DEBUG
		}
		else
		{
			m_objectStatus = objectStatus::STANDBY;
			g_pLogSystem->printLog("CoreSystem is stand-by.");
		}

	}
}


void CoreSystem::shutdown()
{
	g_pGameSystem->shutdown();
	g_pAssetSystem->shutdown();
	g_pRenderingSystem->shutdown();
	g_pTimeSystem->shutdown();
	m_objectStatus = objectStatus::SHUTDOWN;
	g_pLogSystem->printLog("CoreSystem has been shutdown.");
	//@TODO: dangerous
	g_pLogSystem->shutdown();
	g_pMemorySystem->shutdown();

	std::this_thread::sleep_for(std::chrono::seconds(2));
}

const objectStatus & CoreSystem::getStatus() const
{
	return m_objectStatus;
}