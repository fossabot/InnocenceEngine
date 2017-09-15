#pragma once
#include "../interface/IEventManager.h"
#include "../manager/LogManager.h"
#include "../data/GraphicData.h"
#include "../component/VisibleComponent.h"

#include "assimp/Importer.hpp"
#include "assimp/Exporter.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class AssetManager : public IEventManager
{
public:
	~AssetManager();

	static AssetManager& getInstance()
	{
		static AssetManager instance;
		return instance;
	}

	std::string loadShader(const std::string& shaderFileName) const;
	void importModel(const std::string& fileName) const;
	void loadModel(const std::string& fileName, std::vector<StaticMeshData>& staticMeshData) const;
	void loadModel(const std::string& fileName, VisibleComponent& visibleComponent) const;
private:
	AssetManager();

	void initialize() override;
	void update() override;
	void shutdown() override;

	void processAssimpNode(aiNode* node, const aiScene* scene, std::vector<StaticMeshData>& staticMeshData) const;
	void processAssimpNode(aiNode* node, const aiScene* scene, VisibleComponent& visibleComponent) const;
	void processAssimpMesh(aiMesh* mesh, const aiScene* scene, StaticMeshData& staticMeshData) const;
	void processAssimpMesh(aiMesh* mesh, const aiScene* scene, VisibleComponent& visibleComponent) const;

};

