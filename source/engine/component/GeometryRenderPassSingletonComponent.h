#pragma once
#include "BaseComponent.h"
#include "component/GLFrameBufferComponent.h"
#include "component/GLShaderProgramComponent.h"
#include "component/GLTextureDataComponent.h"

class GeometryRenderPassSingletonComponent : public BaseComponent
{
public:
	~GeometryRenderPassSingletonComponent() {};

	void setup() override;
	void initialize() override;
	void shutdown() override;
	
	static GeometryRenderPassSingletonComponent& getInstance()
	{
		static GeometryRenderPassSingletonComponent instance;
		return instance;
	}

	GLFrameBufferComponent m_GLFrameBufferComponent;

	GLShaderProgramComponent m_geometryPassProgram;
	GLuint m_geometryPassVertexShaderID;
	GLuint m_geometryPassFragmentShaderID;
	std::vector<GLTextureDataComponent> m_geometryPassTextures;

	GLuint m_geometryPass_uni_prt;
	GLuint m_geometryPass_uni_prt_previous;
	GLuint m_geometryPass_uni_m;

	GLuint m_geometryPass_uni_p_light_0;
	GLuint m_geometryPass_uni_p_light_1;
	GLuint m_geometryPass_uni_p_light_2;
	GLuint m_geometryPass_uni_p_light_3;
	GLuint m_geometryPass_uni_v_light;

	GLuint m_geometryPass_uni_normalTexture;
	GLuint m_geometryPass_uni_albedoTexture;
	GLuint m_geometryPass_uni_metallicTexture;
	GLuint m_geometryPass_uni_roughnessTexture;
	GLuint m_geometryPass_uni_aoTexture;
	GLuint m_geometryPass_uni_useTexture;
	GLuint m_geometryPass_uni_albedo;
	GLuint m_geometryPass_uni_MRA;
private:
	GeometryRenderPassSingletonComponent() {};
};
