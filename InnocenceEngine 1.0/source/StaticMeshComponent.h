#pragma once
#include "IVisibleGameEntity.h"
#include "GLRenderingManager.h"

class VertexData
{
public:
	VertexData();
	~VertexData();

	const Vec3f& getPos();
	const Vec2f& getTexCoord();
	const Vec3f& getNormal();

	void setPos(const Vec3f& pos);
	void setTexCoord(const Vec2f& texCoord);
	void setNormal(const Vec3f& normal);

	void addVertexData(const Vec3f & pos, const Vec2f & texCoord, const Vec3f & normal);
private:
	Vec3f m_pos;
	Vec2f m_texCoord;
	Vec3f m_normal;
};

class MeshData
{
public:
	MeshData();
	~MeshData();

	void init();
	void update();
	void shutdown();

	void addMeshData(std::vector<VertexData*>& vertices, std::vector<unsigned int>& indices, bool calcNormals);
	void addTestTriangle();

private:
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_IBO;

	std::vector<VertexData*> m_vertices;
	std::vector<unsigned int> m_intices;

};


class TextureData
{
public:
	TextureData();
	~TextureData();

	void init();
	void update();
	void shutdown();


	void addTextureData(int textureWidth, int textureHeight, unsigned char * textureData);
private:
	GLuint m_textureID;


};

class StaticMeshComponent : public IVisibleGameEntity
{
public:
	StaticMeshComponent();
	~StaticMeshComponent();

	void loadMesh(const std::string& meshFileName);
	void loadTexture(const std::string& textureFileName);

	void render() override;
private:
	MeshData m_meshData;
	TextureData m_textureData;
	void init() override;
	void update() override;
	void shutdown() override;
};

