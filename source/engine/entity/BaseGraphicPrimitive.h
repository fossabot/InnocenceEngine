#pragma once
#include "interface/IObject.hpp"
#include "innoMath.h"

enum class visiblilityType { INVISIBLE, BILLBOARD, STATIC_MESH, SKYBOX, GLASSWARE };
enum class meshType { TWO_DIMENSION, THREE_DIMENSION };
enum class meshShapeType { QUAD, CUBE, SPHERE, CUSTOM };
enum class meshDrawMethod { TRIANGLE, TRIANGLE_STRIP };
enum class textureType { INVISIBLE, NORMAL, ALBEDO, METALLIC, ROUGHNESS, AMBIENT_OCCLUSION, CUBEMAP, CUBEMAP_HDR, EQUIRETANGULAR, LUT };
enum class textureColorComponentsFormat { RED, RG, RGB, RGBA, R8, RG8, RGB8, RGBA8, R16, RG16, RGB16, RGBA16, R16F, RG16F, RGB16F, RGBA16F, R32F, RG32F, RGB32F, RGBA32F, SRGB, SRGBA, SRGB8, SRGBA8 };
enum class texturePixelDataFormat { RED, RG, RGB, RGBA };
enum class texturePixelDataType { UNSIGNED_BYTE, BYTE, UNSIGNED_SHORT, SHORT, UNSIGNED_INT, INT, FLOAT };
enum class textureWrapMethod { CLAMP_TO_EDGE, REPEAT };
enum class textureFilterMethod { NEAREST, LINEAR, LINEAR_MIPMAP_LINEAR };
enum class frameBufferType { FORWARD, DEFER, SHADOWMAP, CUBEMAP };
enum class renderBufferType { DEPTH, STENCIL, DEPTH_AND_STENCIL };

class IMeshRawData
{
public:
	IMeshRawData() {};
	virtual ~IMeshRawData() {};

	virtual int getNumVertices() const = 0;
	virtual int getNumFaces() const = 0;
	virtual int getNumIndicesInFace(int faceIndex) const = 0;
	virtual vec3 getVertices(unsigned int index) const = 0;
	virtual vec2 getTextureCoords(unsigned int index) const = 0;
	virtual vec3 getNormals(unsigned int index) const = 0;
	virtual int getIndices(int faceIndex, int index) const = 0;
};

class IScene
{
public:
	IScene() {};
	virtual ~IScene() {};
};

typedef unsigned long int textureID;
typedef unsigned long int meshID;
typedef std::pair<textureType, textureID> texturePair;
typedef std::unordered_map<textureType, textureID> textureMap;
typedef std::pair<meshID, textureMap> modelPair;
typedef std::unordered_map<meshID, textureMap> modelMap;

typedef std::pair<textureType, std::string> textureFileNamePair;
typedef std::unordered_map<textureType, std::string> textureFileNameMap;
typedef std::pair<IMeshRawData*, textureFileNameMap> modelPointerPair;
typedef std::unordered_map<IMeshRawData*, textureFileNameMap> modelPointerMap;


class BaseMesh : public IObject
{
public:
	BaseMesh() { m_meshID = std::rand(); };
	virtual ~BaseMesh() {};

	void setup() override;
	void setup(meshType meshType, meshDrawMethod meshDrawMethod, bool calculateNormals, bool calculateTangents);
	const objectStatus& getStatus() const override;
	meshID getMeshID();

	void addVertices(const Vertex& Vertex);
	void addVertices(const vec3 & pos, const vec2 & texCoord, const vec3 & normal);
	void addVertices(double pos_x, double pos_y, double pos_z, double texCoord_x, double texCoord_y, double normal_x, double normal_y, double normal_z);
	void addIndices(unsigned int index);

	void addUnitCube();
	void addUnitSphere();
	void addUnitQuad();

protected:
	objectStatus m_objectStatus = objectStatus::SHUTDOWN;
	meshID m_meshID;
	meshType m_meshType;
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;

	meshDrawMethod m_meshDrawMethod;
	bool m_calculateNormals;
	bool m_calculateTangents;
};

class BaseTexture : public IObject
{
public:
	BaseTexture() { m_textureID = std::rand(); };
	virtual ~BaseTexture() {};

	void setup() override;
	void setup(textureType textureType, textureColorComponentsFormat textureColorComponentsFormat, texturePixelDataFormat texturePixelDataFormat, textureWrapMethod textureWrapMethod, textureFilterMethod textureMinFilterMethod, textureFilterMethod textureMagFilterMethod, int textureWidth, int textureHeight, texturePixelDataType texturePixelDataType, const std::vector<void *>& textureData);
	virtual void update(int textureIndex) = 0;
	virtual void updateFramebuffer(int colorAttachmentIndex, int textureIndex, int mipLevel) = 0;
	const objectStatus& getStatus() const override;
	textureID getTextureID();

protected:
	objectStatus m_objectStatus = objectStatus::SHUTDOWN;
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

class BaseRenderBuffer : public IObject
{
public:
	BaseRenderBuffer() {};
	virtual ~BaseRenderBuffer() {};

	void setup() override;
	void setup(vec2 renderBufferStorageResolution, renderBufferType renderBufferType);
	const objectStatus& getStatus() const override;

protected:
	objectStatus m_objectStatus = objectStatus::SHUTDOWN;
	vec2 m_renderBufferStorageResolution;
	renderBufferType m_renderBufferType = renderBufferType::DEPTH;
};

class BaseFrameBufferWIP : public IObject
{
public:
	BaseFrameBufferWIP() {};
	virtual ~BaseFrameBufferWIP() {};

	void setup() override;
	void setup(frameBufferType frameBufferType, const std::vector<textureID>& renderTargetTextureID);
	const objectStatus& getStatus() const override;

protected:
	objectStatus m_objectStatus = objectStatus::SHUTDOWN;
	frameBufferType m_frameBufferType = frameBufferType::FORWARD;

	std::vector<BaseRenderBuffer*> m_renderBuffers;
	std::vector<textureID> m_renderTargetTextureID;
};

class BaseFrameBuffer : public IObject
{
public:
	BaseFrameBuffer() {};
	virtual ~BaseFrameBuffer() {};

	void setup() override;
	void setup(vec2 renderBufferStorageResolution, frameBufferType frameBufferType, renderBufferType renderBufferType, unsigned int renderTargetTextureNumber);
	const objectStatus& getStatus() const override;

protected:
	objectStatus m_objectStatus = objectStatus::SHUTDOWN;
	vec2 m_renderBufferStorageResolution;
	frameBufferType m_frameBufferType = frameBufferType::FORWARD;
	renderBufferType m_renderBufferType = renderBufferType::DEPTH;
	unsigned int m_renderTargetTextureNumber = 0;
};

