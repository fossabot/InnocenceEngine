#pragma once
#include "../core/interface/IGameData.h"
#include "../core/interface/IGameEntity.h"
#include "../core/component/CameraComponent.h"
#include "../core/component/SkyboxComponent.h"
#include "../core/component/StaticMeshComponent.h"
class InnocenceGarden :	public IGameData
{
public:
	InnocenceGarden();
	~InnocenceGarden();

	CameraComponent* getCameraComponent();
	IVisibleGameEntity* getSkybox();
	IVisibleGameEntity* getTestStaticMeshComponent();

private:
	void init() override;
	void update() override;
	void shutdown() override;

	BaseActor testRootActor;

	BaseActor testCameraActor;
	BaseActor testSkyboxActor;
	BaseActor testStaticMeshActor;

	CameraComponent testCameraComponent;
	SkyboxComponent testSkyboxComponent;
	StaticMeshComponent testStaticMeshComponent;
};

