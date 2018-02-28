#pragma once
#include "BaseManager.h"
#include "LogManager.h"
#include "graphic/RenderingManager.h"
#include "entity/BaseGraphicPrimitive.h"
#include "component/VisibleComponent.h"
#include "assimp/Importer.hpp"
#include "assimp/Exporter.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class AssetManager : public BaseManager
{
public:
	AssetManager() {};
	~AssetManager() {};

	void setup() override;
	void initialize() override;
	void update() override;
	void shutdown() override;

	void loadAsset(const std::string& filePath, VisibleComponent& visibleComponent);
	void loadAsset(const std::vector<std::string>& filePath, textureType textureType, VisibleComponent& visibleComponent);
	void loadAsset(const std::string& filePath, textureType textureType, VisibleComponent& visibleComponent);

	std::string loadShader(const std::string& fileName) const;

	void addUnitMesh(VisibleComponent& visibleComponent, meshType unitMeshType);
	
	static RenderingManager* g_pRenderingManager;
	static LogManager* g_pLogManager;
	static SceneGraphManager* g_pSceneGraphManager;

private:
	enum class textureAssignType { ADD_DEFAULT, OVERWRITE };

	void loadModelImpl(const std::string& fileName, VisibleComponent& visibleComponent);
	void load2DTextureImpl(const std::string& fileName, textureType textureType, VisibleComponent& visibleComponent);

	void load3DTextureFromDisk(const std::vector<std::string>&  fileName, textureType textureType, VisibleComponent& visibleComponent) const;
	void load3DTextureFromDisk(const std::string& filePath, textureType textureType, VisibleComponent& visibleComponent) const;

	void assignloadedModel(modelMap& loadedGraphicDataMap, VisibleComponent& visibleComponent);

	modelMap processAssimpScene(const std::string& fileName, const aiScene* aiScene, meshDrawMethod& meshDrawMethod, textureWrapMethod& textureWrapMethod);
	modelMap processAssimpNode(const std::string& fileName, aiNode* node, const aiScene* scene, meshDrawMethod& meshDrawMethod, textureWrapMethod textureWrapMethod);
	meshID processSingleAssimpMesh(aiMesh* mesh, meshDrawMethod meshDrawMethod) const;
	void addVertex(aiMesh * aiMesh, int vertexIndex, BaseMesh* mesh) const;
	textureMap processSingleAssimpMaterial(const std::string& fileName, aiMaterial * aiMaterial, textureWrapMethod textureWrapMethod);

	void assignDefaultTextures(textureAssignType textureAssignType, VisibleComponent & visibleComponent);
	void assignLoadedTexture(textureAssignType textureAssignType, texturePair& loadedTextureDataPair, VisibleComponent& visibleComponent);

	textureID load2DTextureFromDisk(const std::string & fileName, textureType textureType, textureWrapMethod textureWrapMethod);

	std::unordered_map<std::string, modelMap> m_loadedModelMap;
	std::unordered_map<std::string, texturePair> m_loaded2DTextureMap;
	std::unordered_map<std::string, int> m_supportedTextureType = { std::pair<std::string, int>("png", 0) };
	std::unordered_map<std::string, int> m_supportedModelType = { std::pair<std::string, int>("obj",0), std::pair<std::string, int>("innoModel", 0) };
	std::unordered_map<std::string, int> m_supportedShaderType = { std::pair<std::string, int>("sf", 0) };
	const std::string m_textureRelativePath = "../res/textures/";
	const std::string m_modelRelativePath = "../res/models/";
	const std::string m_shaderRelativePath = "../res/shaders/";

	meshID m_UnitCubeTemplate;
	meshID m_UnitSphereTemplate;
	meshID m_UnitQuadTemplate;
	textureID m_basicNormalTemplate;
	textureID m_basicAlbedoTemplate;
	textureID m_basicMetallicTemplate;
	textureID m_basicRoughnessTemplate;
	textureID m_basicAOTemplate;
};

