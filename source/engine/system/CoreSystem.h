#pragma once
#include "common/config.h"
#include "interface/ICoreSystem.h"

#include "platform/InnoSystemHeader.h"

#ifdef INNO_PLATFORM_WIN32
#include "platform/InnoSystemHeaderWin32.h"
#endif

#ifdef INNO_PLATFORM_WIN64
#include "platform/InnoSystemHeaderWin64.h"
#endif

#ifdef INNO_PLATFORM_LINUX64
#include "platform/InnoSystemHeaderLinux64.h"
#endif

#ifdef INNO_PLATFORM_MACOS
#include "platform/InnoSystemHeaderMacOS.h"
#endif

IMemorySystem* g_pMemorySystem;
ILogSystem* g_pLogSystem;
ITaskSystem* g_pTaskSystem;
ITimeSystem* g_pTimeSystem;
IGameSystem* g_pGameSystem;
IAssetSystem* g_pAssetSystem;
IVisionSystem* g_pVisionSystem;
IPhysicsSystem* g_pPhysicsSystem;

class CoreSystem : public ICoreSystem
{
public:
	CoreSystem() {};
	~CoreSystem() {};
	void setup() override;
	void initialize() override;
	void update() override;
	void shutdown() override;
	const objectStatus& getStatus() const override;

private:
	objectStatus m_objectStatus = objectStatus::SHUTDOWN;

	void taskTest();
};

CoreSystem g_CoreSystem;
ICoreSystem* g_pCoreSystem = &g_CoreSystem;
