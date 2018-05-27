#pragma once
#include "BaseComponent.h"
#include "entity/InnoMath.h"

class TextureDataComponent : public BaseComponent
{
public:
	TextureDataComponent() {};
	~TextureDataComponent() {};

	void setup() override;
	void initialize() override;
	void shutdown() override;

	textureID m_textureID;
	textureType m_textureType;
	textureColorComponentsFormat m_textureColorComponentsFormat;
	texturePixelDataFormat m_texturePixelDataFormat;
	textureFilterMethod m_textureMinFilterMethod;
	textureFilterMethod m_textureMagFilterMethod;
	textureWrapMethod m_textureWrapMethod;
	int m_textureWidth;
	int m_textureHeight;
	texturePixelDataType m_texturePixelDataType;
	std::vector<void *> m_textureData;
};

