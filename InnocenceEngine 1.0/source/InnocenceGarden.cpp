#include "stdafx.h"
#include "InnocenceGarden.h"


InnocenceGarden::InnocenceGarden()
{
}


InnocenceGarden::~InnocenceGarden()
{
}

CameraComponent * InnocenceGarden::getCameraComponent()
{
	return &testCamera;
}

void InnocenceGarden::init()
{
	testCamera.exec(INIT);
	testTriangle.exec(INIT);
	testCamera.getTransform()->setPos(Vec3f(1.0f, 3.0f, 2.0f));
	testCamera.getTransform()->setRot(Quaternion(1.0f, 3.0f, 2.0f, 1.0f));
	testTriangle.getTransform()->setPos(Vec3f(0.0f, -1.0f, 5.0f));
}

void InnocenceGarden::update()
{
	testCamera.exec(UPDATE);
	testTriangle.exec(UPDATE);
}

void InnocenceGarden::shutdown()
{	
	testCamera.exec(SHUTDOWN);
	testTriangle.exec(SHUTDOWN);
}
