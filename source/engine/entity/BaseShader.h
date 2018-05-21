#pragma once
#include "interface/IGraphicPrimitive.h"
#include "InnoMath.h"
#include "interface/IMemorySystem.h"
#include "interface/ILogSystem.h"

extern IMemorySystem* g_pMemorySystem;
extern ILogSystem* g_pLogSystem;

class BaseShader : public IGraphicPrimitive
{
public:
	BaseShader() {};
	virtual ~BaseShader() {};

	void setup() override;
	void setup(shaderData shaderData);
	void update() override;

	const objectStatus& getStatus() const override;
	const shaderData& getShaderData() const;

protected:
	objectStatus m_objectStatus = objectStatus::SHUTDOWN;

	shaderData m_shaderData;
};
