#include "../main/stdafx.h"
#include "InnocenceGarden.h"


InnocenceGarden::InnocenceGarden()
{
}

InnocenceGarden::~InnocenceGarden()
{
}

void InnocenceGarden::initialize()
{	
	rootActor.addChildActor(&playCharacter);

	rootActor.addChildActor(&skyboxActor);

	rootActor.addChildActor(&directionalLightActor);

	rootActor.addChildActor(&landscapeActor);
	rootActor.addChildActor(&pawnActor1);
	rootActor.addChildActor(&pawnActor2);

	SceneGraphManager::getInstance().addToCameraQueue(&playCharacter.getCameraComponent());

	SceneGraphManager::getInstance().addToInputQueue(&playCharacter.getInputComponent());

	skyboxComponent.setVisiblilityType(visiblilityType::SKYBOX);
	skyboxComponent.setTextureWrapMethod(textureWrapMethod::CLAMPTOEDGE);
	skyboxActor.addChildComponent(&skyboxComponent);
	SceneGraphManager::getInstance().addToRenderingQueue(&skyboxComponent);
	

	landscapeStaticMeshComponent.setVisiblilityType(visiblilityType::STATIC_MESH);
	landscapeActor.addChildComponent(&landscapeStaticMeshComponent);
	SceneGraphManager::getInstance().addToRenderingQueue(&landscapeStaticMeshComponent);

	pawnMeshComponent1.setVisiblilityType(visiblilityType::STATIC_MESH);
	pawnActor1.addChildComponent(&pawnMeshComponent1);
	SceneGraphManager::getInstance().addToRenderingQueue(&pawnMeshComponent1);

	pawnMeshComponent2.setVisiblilityType(visiblilityType::STATIC_MESH);
	pawnActor2.addChildComponent(&pawnMeshComponent2);
	SceneGraphManager::getInstance().addToRenderingQueue(&pawnMeshComponent2);
	
	playCharacter.getTransform()->setPos(glm::vec3(0.0f, 2.0f, 5.0f));

	landscapeActor.getTransform()->setScale(glm::vec3(60.0f, 60.0f, 0.1f));
	landscapeActor.getTransform()->rotate(glm::vec3(1.0f, 0.0f, 0.0f), 90.0f);
	landscapeActor.getTransform()->setPos(glm::vec3(0.0f, 0.0f, 0.0f));
	pawnActor1.getTransform()->setScale(glm::vec3(0.2f, 0.2f, 0.2f));
	pawnActor1.getTransform()->setPos(glm::vec3(0.0f, 0.2f, -1.5f));
	pawnActor2.getTransform()->setScale(glm::vec3(0.2f, 0.2f, 0.2f));
	//testStaticMeshActor2.getTransform()->setScale(glm::vec3(0.002f, 0.002f, 0.002f));
	pawnActor2.getTransform()->setPos(glm::vec3(0.0f, 0.2f, 3.5f));

	initLights();
	initSpheres();

	//AssetManager::getInstance().importModel("nanosuit/nanosuit.obj");	
	//AssetManager::getInstance().importModel("deer.obj");

	//AssetManager::getInstance().loadModel("nanosuit/nanosuit.innoModel", pawnMeshComponent1);
	//AssetManager::getInstance().loadModel("nanosuit/nanosuit.innoModel", pawnMeshComponent2);
	//AssetManager::getInstance().loadModel("deer.innoModel", testStaticMeshComponent2);
	//AssetManager::getInstance().addUnitCube(skyboxComponent);
	AssetManager::getInstance().addUnitCube(landscapeStaticMeshComponent);

	//AssetManager::getInstance().loadTexture({ "skybox2/right.tga",
	//	"skybox2/left.tga", "skybox2/top.tga", "skybox2/bottom.tga", "skybox2/back.tga", "skybox2/front.tga" }, skyboxComponent);

	rootActor.initialize();
}

void InnocenceGarden::update()
{
	temp += 0.02f;
	updateLights(temp);
	//directionalLightComponent.setDirection(glm::vec3((((glm::sin(temp) + 1.0) / 2.0), 1.0f, 1.0f)));
	//directionalLightComponent.setColor(glm::vec3(0.0f * 30.0, (glm::sin(temp) + 1.0f) * 30.0 / 2.0f, 0.0f * 30.0));
	//pointLightComponent1.setColor(glm::vec3(0.5f * 30.0, (glm::sin(temp) + 1.0f) * 30.0 / 2.0f, 0.5f * 30.0));
	//pointLightActor1.getTransform()->setPos(glm::vec3(-2.0f, 1.0f, 2.0f) + glm::vec3(glm::sin(temp) + 1.0f, 0.0f, -glm::cos(temp) * 3.0f));

	//pointLightComponent2.setColor(glm::vec3((glm::sin(temp * 2) + 1.0f)* 30.0 / 2.0f, 0.5f * 30.0, 0.5f * 30.0));
	//pointLightActor2.getTransform()->setPos(glm::vec3(2.0f, 1.0f, 2.0f) + glm::vec3(glm::sin(temp) + 1.0f, 0.0f, -glm::cos(temp) * 2.0f));

	//pointLightComponent3.setColor(glm::vec3(0.5f * 30.0, 0.5f * 30.0, (glm::sin(temp * 3) + 1.0f) * 30.0 / 2.0f));
	//pointLightActor3.getTransform()->setPos(glm::vec3(0.0f, 1.0f, 4.0f) + glm::vec3(glm::sin(temp) + 1.0f, 0.0f, -glm::cos(temp) * 1.0f));

	rootActor.update();
}

void InnocenceGarden::shutdown()
{	
	rootActor.shutdown();
}

void InnocenceGarden::initSpheres()
{
	int sphereMatrixDim = 8;
	float sphereBreadthInterval = 4.0;
	for (auto i = (unsigned int)0; i < sphereMatrixDim * sphereMatrixDim; i++)
	{
		sphereActors.emplace_back();
		sphereComponents.emplace_back();
	}
	for (auto i = (unsigned int)0; i < sphereComponents.size(); i++)
	{
		sphereComponents[i].setMeshDrawMethod(meshDrawMethod::TRIANGLE_STRIP);
		sphereComponents[i].setVisiblilityType(visiblilityType::STATIC_MESH);

		rootActor.addChildActor(&sphereActors[i]);
		sphereActors[i].addChildComponent(&sphereComponents[i]);

		SceneGraphManager::getInstance().addToRenderingQueue(&sphereComponents[i]);

		AssetManager::getInstance().addUnitSphere(sphereComponents[i]);
	}
	for (auto i = (unsigned int)0; i < sphereComponents.size(); i+=4)
	{
		AssetManager::getInstance().loadSingleTexture("PBS/rustediron2_basecolor.png", textureType::DIFFUSE, sphereComponents[i]);
		AssetManager::getInstance().loadSingleTexture("PBS/rustediron2_metallic.png", textureType::SPECULAR, sphereComponents[i]);
		AssetManager::getInstance().loadSingleTexture("PBS/rustediron2_normal.png", textureType::NORMALS, sphereComponents[i]);
		AssetManager::getInstance().loadSingleTexture("PBS/rustediron2_roughness.png", textureType::AMBIENT, sphereComponents[i]);

		AssetManager::getInstance().loadSingleTexture("PBS/bamboo-wood-semigloss-albedo.png", textureType::DIFFUSE, sphereComponents[i + 1]);
		AssetManager::getInstance().loadSingleTexture("PBS/bamboo-wood-semigloss-metal.psd", textureType::SPECULAR, sphereComponents[i + 1]);
		AssetManager::getInstance().loadSingleTexture("PBS/bamboo-wood-semigloss-normal.png", textureType::NORMALS, sphereComponents[i + 1]);
		AssetManager::getInstance().loadSingleTexture("PBS/bamboo-wood-semigloss-ao.png", textureType::EMISSIVE, sphereComponents[i + 1]);

		AssetManager::getInstance().loadSingleTexture("PBS/greasy-metal-pan1-albedo.png", textureType::DIFFUSE, sphereComponents[i + 2]);
		AssetManager::getInstance().loadSingleTexture("PBS/greasy-metal-pan1-metal.png", textureType::SPECULAR, sphereComponents[i + 2]);
		AssetManager::getInstance().loadSingleTexture("PBS/greasy-metal-pan1-normal.png", textureType::NORMALS, sphereComponents[i + 2]);
		AssetManager::getInstance().loadSingleTexture("PBS/greasy-metal-pan1-roughness.png", textureType::AMBIENT, sphereComponents[i + 2]);

		AssetManager::getInstance().loadSingleTexture("PBS/roughrock1-albedo.png", textureType::DIFFUSE, sphereComponents[i + 3]);
		AssetManager::getInstance().loadSingleTexture("PBS/roughrock1-metalness.png", textureType::SPECULAR, sphereComponents[i + 3]);
		AssetManager::getInstance().loadSingleTexture("PBS/roughrock1-normal.png", textureType::NORMALS, sphereComponents[i + 3]);
		AssetManager::getInstance().loadSingleTexture("PBS/roughrock1-roughness.png", textureType::AMBIENT, sphereComponents[i + 3]);
		AssetManager::getInstance().loadSingleTexture("PBS/roughrock1-ao.png", textureType::EMISSIVE, sphereComponents[i + 3]);
	}
	for (auto i = (unsigned int)0; i < sphereMatrixDim; i++)
	{
		for (auto j = (unsigned int)0; j < sphereMatrixDim; j++)
		{
			sphereActors[i * sphereMatrixDim + j].getTransform()->setPos(glm::vec3((-(sphereMatrixDim - 1.0) * sphereBreadthInterval/ 2.0) + (i * sphereBreadthInterval), 2.0 + (j * sphereBreadthInterval), 2.0));
		}
	}
	
}

void InnocenceGarden::initLights()
{
	int pointLightMatrixDim = 8;
	float pointLightBreadthInterval = 4.0;
	for (auto i = (unsigned int)0; i < pointLightMatrixDim * pointLightMatrixDim; i++)
	{
		pointLightActors.emplace_back();
		pointLightComponents.emplace_back();
	}
	for (auto i = (unsigned int)0; i < pointLightComponents.size(); i++)
	{
		rootActor.addChildActor(&pointLightActors[i]);
		pointLightActors[i].addChildComponent(&pointLightComponents[i]);

		SceneGraphManager::getInstance().addToLightQueue(&pointLightComponents[i]);
	}
	for (auto i = (unsigned int)0; i < pointLightMatrixDim; i++)
	{
		for (auto j = (unsigned int)0; j < pointLightMatrixDim; j++)
		{
			pointLightActors[i * pointLightMatrixDim + j].getTransform()->setPos(glm::vec3((-(pointLightMatrixDim - 1.0) * pointLightBreadthInterval / 2.0) + (i * pointLightBreadthInterval), 2.0 + (j * pointLightBreadthInterval), 0.0));
		}
	}
}

void InnocenceGarden::updateLights(double seed)
{
	for (auto i = (unsigned int)0; i < pointLightComponents.size(); i+=4)
	{
		pointLightComponents[i].setColor(glm::vec3((glm::sin(seed + i) + 1.0f) * 10.0f / 2.0f, 0.2f * 10.0f, 0.4f * 10.0f));
		pointLightComponents[i + 1].setColor(glm::vec3(0.2f * 10.0f, (glm::sin(seed + i) + 1.0f) * 10.0f / 2.0f, 0.4f * 10.0f));
		pointLightComponents[i + 2].setColor(glm::vec3((0.2f * 10.0f, 0.4f * 10.0f, glm::sin(seed + i) + 1.0f) * 10.0f / 2.0f));
		pointLightComponents[i + 3].setColor(glm::vec3((glm::sin(seed + i * 2.0 ) + 1.0f) * 10.0f / 2.0f, (glm::sin(seed + i* 3.0) + 1.0f) * 10.0f / 2.0f, (glm::sin(seed + i * 5.0) + 1.0f) * 10.0f / 2.0f));
	}
}
