#pragma once

#include "../../interface/IEventManager.h"
#include "../../manager/LogManager.h"
#include "SceneGraphManager.h"

#include "GLWindowManager.h"
#include "GLInputManager.h"
#include "../../platform-dependency/GL/GLRenderingManager.h"
//#include "GLGUIManager.h"

class RenderingManager : public IEventManager
{
public:
	~RenderingManager();

	void setup() override;
	void initialize() override;
	void update() override;
	void shutdown() override;

	static RenderingManager& getInstance()
	{
		static RenderingManager instance;
		return instance;
	}

	meshDataID addMeshData();
	textureDataID addTextureData();
	std::unordered_map<meshDataID, MeshData>& getMeshData();
	std::unordered_map<textureDataID, TextureData>& getTextureData();
	MeshData& getMeshData(meshDataID meshDataIndex);
	TextureData& getTextureData(textureDataID textureDataIndex);

private:
	RenderingManager();

	void AsyncRender();
	void changeDrawPolygonMode();
	void changeDrawTextureMode();

	std::vector<std::unique_ptr<IEventManager>> m_childEventManager;
	std::function<void()> f_changeDrawPolygonMode;
	std::function<void()> f_changeDrawTextureMode;	
	std::unordered_map<meshDataID, MeshData> m_meshDatas;
	std::unordered_map<textureDataID, TextureData> m_textureDatas;
};

