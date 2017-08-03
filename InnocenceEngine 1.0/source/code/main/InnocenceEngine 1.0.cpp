// InnocenceEngine 1.0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../core/interface/IBaseObject.h"
#include "../core/manager/CoreManager.h"
#include "../game/InnocenceGarden.h"


int main()
{
	CoreManager* m_coreManager = new CoreManager();
	InnocenceGarden* m_innocenceGarden = new InnocenceGarden();

	m_coreManager->setGameData(m_innocenceGarden);

	m_coreManager->exec(execMessage::INIT);
	while (m_coreManager->getStatus() == objectStatus::INITIALIZIED)
	{
		m_coreManager->exec(execMessage::UPDATE);
	}
	m_coreManager->exec(execMessage::SHUTDOWN);
	delete m_innocenceGarden;
	delete m_coreManager;
	
	return EXIT_SUCCESS;
}

