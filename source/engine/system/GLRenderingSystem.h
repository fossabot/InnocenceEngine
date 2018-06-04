#pragma once
#include "interface/IRenderingSystem.h"
#include "component/EnvironmentRenderPassSingletonComponent.h"
#include "component/GLRenderingSystemSingletonComponent.h"
#include "component/AssetSystemSingletonComponent.h"

#include "interface/IRenderingSystem.h"
#include "interface/IMemorySystem.h"
#include "interface/IAssetSystem.h"
#include "interface/IGameSystem.h"

extern IMemorySystem* g_pMemorySystem;
extern IAssetSystem* g_pAssetSystem;
extern IGameSystem* g_pGameSystem;

class GLRenderingSystem : public IRenderingSystem
{
public:
	GLRenderingSystem() {};
	~GLRenderingSystem() {};

	void setup() override;
	void initialize() override;
	void update() override;
	void shutdown() override;

	const objectStatus& getStatus() const override;

private:
	objectStatus m_objectStatus = objectStatus::SHUTDOWN;

	void setupEnvironmentRenderPass();
	void setupGraphicPrimtives();
	void setupMesh(MeshDataComponent* GLMeshDataComponent);
	void setupTexture(TextureDataComponent* GLTextureDataComponent);
	void setupShader(GLuint shaderProgram, GLuint shaderID, GLuint shaderType, const std::string& shaderFilePath);
	GLuint getUniformLocation(GLuint shaderProgram, const std::string& uniformName);
	void updateUniform(const GLint uniformLocation, bool uniformValue) const;
	void updateUniform(const GLint uniformLocation, int uniformValue) const;
	void updateUniform(const GLint uniformLocation, double uniformValue) const;
	void updateUniform(const GLint uniformLocation, double x, double y) const;
	void updateUniform(const GLint uniformLocation, double x, double y, double z) const;
	void updateUniform(const GLint uniformLocation, double x, double y, double z, double w) const;
	void updateUniform(const GLint uniformLocation, const mat4& mat) const;

	void attachTextureToFramebuffer(const GLTextureDataComponent* GLTextureDataComponent, const GLFrameBufferComponent* GLFrameBufferComponent, int colorAttachmentIndex, int textureIndex, int mipLevel);
	void activateShaderProgram(const GLShaderProgramComponent* GLShaderProgramComponent);
	void activateMesh(const MeshDataComponent* GLTextureDataComponent);
	void drawMesh(const MeshDataComponent* GLTextureDataComponent);
	void activateTexture(const TextureDataComponent* GLTextureDataComponent, int activateIndex);
};
