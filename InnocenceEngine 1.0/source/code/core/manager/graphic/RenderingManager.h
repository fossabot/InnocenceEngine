#pragma once

#include "../../interface/IEventManager.h"
#include "../../manager/LogManager.h"
#include "SceneGraphManager.h"

#include "GLWindowManager.h"
#include "GLInputManager.h"
#include "../../platform-dependency/GL/GLRenderingManager.h"
//#include "GLGUIManager.h"
#include "../../data/GraphicData.h"

class RenderingManager : public IEventManager
{
public:
	~RenderingManager();

	static RenderingManager& getInstance()
	{
		static RenderingManager instance;
		return instance;
	}

	void initInput();
	void changeDrawPolygonMode() const;
	void toggleDepthBufferVisualizer();
	void addMeshData();
	void addTextureData();
	std::vector<MeshData>& getMeshData();
	std::vector<TextureData>& getTextureData();
	MeshData& getLastMeshData();
	TextureData& getLastTextureData();

private:
	RenderingManager();

	void initialize() override;
	void update() override;
	void shutdown() override;
	std::thread* m_asyncRenderThread;
	void AsyncRender();
	std::vector<std::unique_ptr<IEventManager>> m_childEventManager;

	std::vector<MeshData> m_meshDatas;
	std::vector<TextureData> m_textureDatas;
};

