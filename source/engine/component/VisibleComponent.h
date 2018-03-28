#pragma once
#include "BaseComponent.h"
#include "entity/innoMath.h"

class VisibleComponent : public BaseComponent
{
public:
	VisibleComponent();
	~VisibleComponent();


	void setup() override;
	void initialize() override;
	void update() override;
	void shutdown() override;

	visiblilityType m_visiblilityType = visiblilityType::INVISIBLE;
	meshShapeType m_meshType = meshShapeType::QUAD;
	meshDrawMethod m_meshDrawMethod = meshDrawMethod::TRIANGLE;
	textureWrapMethod m_textureWrapMethod = textureWrapMethod::REPEAT;

	bool m_caclNormal = false;
	bool m_useTexture = true;
	vec4 m_albedo;
	vec4 m_MRA;
	bool m_drawAABB = false;
	meshID m_AABBMeshID;
	AABB m_AABB;

	std::string m_modelFileName;
	textureFileNameMap m_textureFileNameMap;

	modelMap& getModelMap();
	void setModelMap(modelMap& graphicDataMap);
	void addMeshData(meshID& meshDataID);
	void addTextureData(texturePair& textureDataPair);
	void overwriteTextureData(texturePair& textureDataPair);

private:
	modelMap m_modelMap;

};

