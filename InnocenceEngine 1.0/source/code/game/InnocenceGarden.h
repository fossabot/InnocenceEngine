#pragma once
#include "../core/interface/IGameData.h"
#include "../core/interface/IGameEntity.h"

#include "../core/component/VisibleComponent.h"

#include "PlayerCharacter.h"
class InnocenceGarden :	public IGameData
{
public:
	InnocenceGarden();
	~InnocenceGarden();

private:
	void initialize() override;
	void update() override;
	void shutdown() override;

	BaseActor rootActor;

	PlayerCharacter playCharacter;
	BaseActor skyboxActor;
	BaseActor testStaticMeshActor1;
	BaseActor testStaticMeshActor2;

	VisibleComponent testSkyboxComponent;
	VisibleComponent testStaticMeshComponent1;
	VisibleComponent testStaticMeshComponent2;
};

