#include "CameraComponent.h"

CameraComponent::CameraComponent()
{
}

CameraComponent::~CameraComponent()
{
}

mat4 CameraComponent::getPosMatrix() const
{
	return getParentEntity()->caclWorldPos().scale(-1.0).toTranslationMartix();
}

mat4 CameraComponent::getRotMatrix() const
{
	// quaternion rotation
	quat conjugateRotQuat = getParentEntity()->caclWorldRot();
	conjugateRotQuat.x = -conjugateRotQuat.x;
	conjugateRotQuat.y = -conjugateRotQuat.y;
	conjugateRotQuat.z = -conjugateRotQuat.z;

	return conjugateRotQuat.toRotationMartix();
}

mat4 CameraComponent::getProjectionMatrix() const
{
	return m_projectionMatrix;
}

void CameraComponent::setup()
{
	m_projectionMatrix.initializeToPerspectiveMatrix((70.0 / 180.0) * PI, (16.0 / 9.0), 0.1, 10000.0);
	m_rayOfEye.m_origin = getParentEntity()->caclWorldPos();
	m_rayOfEye.m_direction = getParentEntity()->getTransform()->getDirection(Transform::direction::BACKWARD);
}

void CameraComponent::initialize()
{
}

void CameraComponent::update()
{
	m_rayOfEye.m_origin = getParentEntity()->caclWorldPos();
	m_rayOfEye.m_direction = getParentEntity()->getTransform()->getDirection(Transform::direction::BACKWARD);
}

void CameraComponent::shutdown()
{
}

