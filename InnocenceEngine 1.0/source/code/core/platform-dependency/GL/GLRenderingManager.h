#pragma once
#include "../../interface/IEventManager.h"
#include "../../manager/AssetManager.h"
#include "../../manager/LogManager.h"
#include "../../component/VisibleComponent.h"
#include "../../component/LightComponent.h"

class GLShader
{
public:
	virtual ~GLShader();

	virtual void init() = 0;
	virtual void draw(std::vector<LightComponent*>& lightComponents, VisibleComponent& visibleComponent) = 0;

protected:
	GLShader();

	enum shaderType
	{
		VERTEX,
		GEOMETRY,
		FRAGMENT
	};

	inline void addShader(shaderType shaderType, const std::string& fileLocation) const;
	inline void setAttributeLocation(int arrtributeLocation, const std::string& arrtributeName) const;
	inline void bindShader() const;

	inline void initProgram();
	inline void addUniform(std::string uniform) const;

	inline void updateUniform(const std::string &uniformName, bool uniformValue) const;
	inline void updateUniform(const std::string &uniformName, int uniformValue) const;
	inline void updateUniform(const std::string &uniformName, float uniformValue) const;
	inline void updateUniform(const std::string &uniformName, const glm::vec2 &uniformValue) const;
	inline void updateUniform(const std::string &uniformName, float x, float y) const;
	inline void updateUniform(const std::string &uniformName, const glm::vec3& uniformValue) const;
	inline void updateUniform(const std::string &uniformName, float x, float y, float z) const;
	inline void updateUniform(const std::string &uniformName, float x, float y, float z, float w);
	inline void updateUniform(const std::string &uniformName, const glm::mat4& mat) const;

private:
	inline void attachShader(shaderType shaderType, const std::string& fileContent, int m_program) const;
	inline void compileShader() const;
	inline void detachShader(int shader) const;

	unsigned int m_program;
};

class BasicGLShader : public GLShader
{

public:
	~BasicGLShader();

	static BasicGLShader& getInstance()
	{
		static BasicGLShader instance;
		return instance;
	}

	void init() override;
	void draw(std::vector<LightComponent*>& lightComponents, VisibleComponent& visibleComponent) override;

private:
	BasicGLShader();
};

class PhongShader : public GLShader
{

public:
	~PhongShader();

	static PhongShader& getInstance()
	{
		static PhongShader instance;
		return instance;
	}

	void init() override;
	void draw(std::vector<LightComponent*>& lightComponents, VisibleComponent& visibleComponent) override;

private:
	PhongShader();
};

class BillboardShader : public GLShader
{

public:
	~BillboardShader();

	static BillboardShader& getInstance()
	{
		static BillboardShader instance;
		return instance;
	}

	void init() override;
	void draw(std::vector<LightComponent*>& lightComponents, VisibleComponent& visibleComponent) override;

private:
	BillboardShader();
};

class SkyboxShader : public GLShader
{

public:
	~SkyboxShader();

	static SkyboxShader& getInstance()
	{
		static SkyboxShader instance;
		return instance;
	}

	void init() override;
	void draw(std::vector<LightComponent*>& lightComponents, VisibleComponent& visibleComponent) override;

private:
	SkyboxShader();
};

class GLRenderingManager : public IEventManager
{
public:
	~GLRenderingManager();

	static GLRenderingManager& getInstance()
	{
		static GLRenderingManager instance;
		return instance;
	}

	void render(std::vector<LightComponent*>& lightComponents, VisibleComponent& visibleComponent);

	void getCameraTranslationMatrix(glm::mat4& t) const;
	void setCameraTranslationMatrix(const glm::mat4& t);
	void getCameraRotMatrix(glm::mat4& v) const;
	void setCameraViewMatrix(const glm::mat4& v);
	void getCameraProjectionMatrix(glm::mat4& p) const;
	void setCameraProjectionMatrix(const glm::mat4& p);
	void getCameraPos(glm::vec3& pos) const;
	void setCameraPos(const glm::vec3& pos);
	void changeDrawPolygonMode();
	void toggleDepthBufferVisualizer();
	bool canDrawDepthBuffer() const;

private:
	GLRenderingManager();

	std::vector<std::unique_ptr<GLShader>> m_staticMeshGLShader;
	glm::mat4 cameraTranslationMatrix = glm::mat4();
	glm::mat4 cameraViewMatrix = glm::mat4();
	glm::mat4 cameraProjectionMatrix = glm::mat4();
	glm::vec3 cameraPos = glm::vec3();

	int m_polygonMode = 0;
	bool m_drawDepthBuffer = false;

	void initialize() override;
	void update() override;
	void shutdown() override;
};