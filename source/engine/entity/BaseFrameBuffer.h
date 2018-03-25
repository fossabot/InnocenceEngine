#pragma once
#include "interface/IObject.hpp"
#include "innoMath.h"
#include "interface/IMemorySystem.h"
#include "interface/ILogSystem.h"
#include "ComponentHeaders.h"
#include "BaseShaderProgram.h"

extern IMemorySystem* g_pMemorySystem;
extern ILogSystem* g_pLogSystem;

class BaseFrameBuffer : public IObject
{
public:
	BaseFrameBuffer() {};
	virtual ~BaseFrameBuffer() {};

	void setup() override;
	void setup(frameBufferType frameBufferType, renderBufferType renderBufferType, const std::vector<vec2>& renderBufferStorageSize, const std::vector<BaseTexture*>& renderTargetTextures, const std::vector<BaseShaderProgram*>& renderTargetShaderPrograms);
	void update() override;
	virtual void update(std::vector<CameraComponent*>& cameraComponents, std::vector<LightComponent*>& lightComponents, std::vector<VisibleComponent*>& visibleComponents, std::unordered_map<EntityID, BaseMesh*>& meshMap, std::unordered_map<EntityID, BaseTexture*>& textureMap, bool cleanColorBuffer, bool cleanDepthBuffer) = 0;
	virtual void activeTexture(int textureIndexInOwnerFrameBuffer, int textureIndexInUserFrameBuffer) = 0;
	const unsigned int getRenderTargetNumber() const;
	virtual void asReadBuffer() = 0;
	virtual void asWriteBuffer(const vec2& source, const vec2& dest) = 0;
	const objectStatus& getStatus() const override;

protected:
	objectStatus m_objectStatus = objectStatus::SHUTDOWN;

	frameBufferType m_frameBufferType = frameBufferType::FORWARD;
	renderBufferType m_renderBufferType = renderBufferType::DEPTH;
	std::vector<vec2> m_renderBufferStorageSize;
	std::vector<BaseTexture*> m_renderTargetTextures;
	std::vector<BaseShaderProgram*> m_shaderPrograms;
};