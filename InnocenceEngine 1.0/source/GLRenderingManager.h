#pragma once
#include "Math.h"
#include "IEventManager.h"
#include "LogManager.h"
#include "CameraComponent.h"

class GLShader
{
public:
	GLShader();
	~GLShader();

	enum shaderType
	{
		VERTEX,
		GEOMETRY,
		FRAGMENT
	};

	void addShader(shaderType shaderType, const std::string& fileLocation, int shaderProgram);
	void bind(int shaderProgram);

	inline void addUniform(int shaderProgram, const std::string &uniformName, bool uniformValue) const
	{
		glUniform1i(glGetUniformLocation(shaderProgram, uniformName.c_str()), (int)uniformValue);
	}

	inline void addUniform(int shaderProgram, const std::string &uniformName, int uniformValue) const
	{
		glUniform1i(glGetUniformLocation(shaderProgram, uniformName.c_str()), uniformValue);
	}

	inline void addUniform(int shaderProgram, const std::string &uniformName, float uniformValue) const
	{
		glUniform1f(glGetUniformLocation(shaderProgram, uniformName.c_str()), uniformValue);
	}
	
	inline void addUniform(int shaderProgram, const std::string &uniformName, const Vec2f &uniformValue) const
	{
		float bufferUniformValue[] = { uniformValue.getX(), uniformValue.getY() };
		glUniform2fv(glGetUniformLocation(shaderProgram, uniformName.c_str()), 1, &bufferUniformValue[0]);
	}
	inline void addUniform(int shaderProgram, const std::string &uniformName, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(shaderProgram, uniformName.c_str()), x, y);
	}
	
	inline void addUniform(int shaderProgram, const std::string &uniformName, const Vec3f& uniformValue) const
	{
		float bufferUniformValue[] = { uniformValue.getX(), uniformValue.getY(), uniformValue.getZ() };
		glUniform3fv(glGetUniformLocation(shaderProgram, uniformName.c_str()), 1, &bufferUniformValue[0]);
	}

	inline void addUniform(int shaderProgram, const std::string &uniformName, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(shaderProgram, uniformName.c_str()), x, y, z);
	}

	inline void addUniform(int shaderProgram, const std::string &uniformName, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(shaderProgram, uniformName.c_str()), x, y, z, w);
	}
	
	inline void addUniform(int shaderProgram, const std::string &uniformName, const Mat4f& mat) const
	{
		glm::mat4 bufferUniformValue = { 
			mat.getElem(0,0), mat.getElem(0,1), mat.getElem(0,2), mat.getElem(0,3),  
			mat.getElem(1,0), mat.getElem(1,1), mat.getElem(1,2), mat.getElem(1,3),  
			mat.getElem(2,0), mat.getElem(2,1), mat.getElem(2,2), mat.getElem(2,3),
			mat.getElem(3,0), mat.getElem(3,1), mat.getElem(3,2), mat.getElem(3,3), };
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniformName.c_str()), 1, GL_FALSE, &bufferUniformValue[0][0]);
	}

private:
	std::string loadShader(const std::string& shaderFileName);
	void addProgram(shaderType shaderType, const std::string& fileContent, int shaderProgram);
	std::vector<std::string> split(const std::string& data, char marker);
};

class GLRenderingManager : public IEventManager
{
	friend GLShader;

public:
	GLRenderingManager();
	~GLRenderingManager();
	void setcameraProjectionMatrix(Mat4f* cameraProjectionMatrix);
	void setCameraViewProjectionMatrix(const Mat4f& cameraViewProjectionMatrix);
private:
	int m_program;

	void init() override;
	void update() override;
	void shutdown() override;

	GLShader m_vertexShader;
	GLShader m_fragmentShader;

	Mat4f* m_cameraProjectionMatrix;
	Mat4f m_cameraViewProjectionMatrix;
};