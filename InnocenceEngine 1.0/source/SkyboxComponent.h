#pragma once
#include "GraphicData.h"
#include "IVisibleGameEntity.h"


class SkyboxComponent : public IVisibleGameEntity
{
public:
	SkyboxComponent();
	~SkyboxComponent();

	void render() override;
private:
	MeshData m_meshData;
	CubemapData m_cubemapData;

	void init() override;
	void update() override;
	void shutdown() override;
};

