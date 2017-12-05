#include "../../main/stdafx.h"
#include "IGameEntity.h"

Transform::Transform()
{
	m_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_rot = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_oldPos = m_pos + (1.0f);
	m_oldRot = m_rot *(0.5f);
	m_oldScale = m_scale + (1.0f);
}

Transform::~Transform()
{
}

void Transform::update()
{
	m_oldPos = m_pos;
	m_oldRot = m_rot;
	m_oldScale = m_scale;
}

void Transform::rotate(const glm::vec3& axis, float angle)
{
	// build a quaternion to represent the rotation axis and angle
	glm::quat l_hiddenRotatedQuat;

	float sinHalfAngle = sinf((angle * glm::pi<float>() / 180.0f) / 2);
	float cosHalfAngle = cosf((angle * glm::pi<float>() / 180.0f) / 2);

	l_hiddenRotatedQuat.w = cosHalfAngle;
	l_hiddenRotatedQuat.x = axis.x * sinHalfAngle;
	l_hiddenRotatedQuat.y = axis.y * sinHalfAngle;
	l_hiddenRotatedQuat.z = axis.z * sinHalfAngle;

	// get final rotation
	glm::quat l_finalRotatedQuat;
	l_finalRotatedQuat.w = l_hiddenRotatedQuat.w * m_rot.w - l_hiddenRotatedQuat.x * m_rot.x - l_hiddenRotatedQuat.y * m_rot.y - l_hiddenRotatedQuat.z * m_rot.z;
	l_finalRotatedQuat.x = l_hiddenRotatedQuat.x * m_rot.w + l_hiddenRotatedQuat.w * m_rot.x + l_hiddenRotatedQuat.y * m_rot.z - l_hiddenRotatedQuat.z * m_rot.y;
	l_finalRotatedQuat.y = l_hiddenRotatedQuat.y * m_rot.w + l_hiddenRotatedQuat.w * m_rot.y + l_hiddenRotatedQuat.z * m_rot.x - l_hiddenRotatedQuat.x * m_rot.z;
	l_finalRotatedQuat.z = l_hiddenRotatedQuat.z * m_rot.w + l_hiddenRotatedQuat.w * m_rot.z + l_hiddenRotatedQuat.x * m_rot.y - l_hiddenRotatedQuat.y * m_rot.x;

	// normalized the rotation
	auto l_quatLength = sqrtf(l_finalRotatedQuat.x * l_finalRotatedQuat.x + l_finalRotatedQuat.y * l_finalRotatedQuat.y + l_finalRotatedQuat.z * l_finalRotatedQuat.z + l_finalRotatedQuat.w * l_finalRotatedQuat.w);
	m_rot = l_finalRotatedQuat / l_quatLength;
}

const glm::vec3 & Transform::getPos() const
{
	return m_pos;
}

const glm::quat & Transform::getRot() const
{
	return m_rot;
}

const glm::vec3 & Transform::getScale() const
{
	return m_scale;
}

void Transform::setPos(const glm::vec3 & pos)
{
	m_pos = pos;
}

void Transform::setRot(const glm::quat & rot)
{
	m_rot = rot;
}

void Transform::setScale(const glm::vec3 & scale)
{
	m_scale = scale;
}

const glm::vec3 & Transform::getOldPos() const
{
	return m_oldPos;
}

const glm::quat & Transform::getOldRot() const
{
	return m_oldRot;
}

const glm::vec3 & Transform::getOldScale() const
{
	return m_oldScale;
}

glm::vec3 Transform::getDirection(direction direction) const
{
	glm::vec3 l_directionVec3;

	switch (direction)
	{
	case FORWARD: l_directionVec3 = glm::vec3(0.0f, 0.0f, 1.0f); break;
	case BACKWARD:l_directionVec3 = glm::vec3(0.0f, 0.0f, -1.0f); break;
	case UP:l_directionVec3 = glm::vec3(0.0f, 1.0f, 0.0f); break;
	case DOWN:l_directionVec3 = glm::vec3(0.0f, -1.0f, 0.0f); break;
	case RIGHT:l_directionVec3 = glm::vec3(1.0f, 0.0f, 0.0f); break;
	case LEFT:l_directionVec3 = glm::vec3(-1.0f, 0.0f, 0.0f); break;
	}

	// get conjugate quaternion
	glm::quat l_conjugateQuat;

	l_conjugateQuat.w = m_rot.w;
	l_conjugateQuat.x = -m_rot.x;
	l_conjugateQuat.y = -m_rot.y;
	l_conjugateQuat.z = -m_rot.z;

	// get rotated quaternion
	glm::quat l_hiddenRotatedQuat;

	l_hiddenRotatedQuat.w = -m_rot.x * l_directionVec3.x - m_rot.y * l_directionVec3.y - m_rot.z * l_directionVec3.z;
	l_hiddenRotatedQuat.x = m_rot.w * l_directionVec3.x + m_rot.y * l_directionVec3.z - m_rot.z * l_directionVec3.y;
	l_hiddenRotatedQuat.y = m_rot.w * l_directionVec3.y + m_rot.z * l_directionVec3.x - m_rot.x * l_directionVec3.z;
	l_hiddenRotatedQuat.z = m_rot.w * l_directionVec3.z + m_rot.x * l_directionVec3.y - m_rot.y * l_directionVec3.x;

	// multiply rotated quaternion by the conjugate quaternion
	glm::quat l_finalRotatedQuat;
	l_finalRotatedQuat.w = l_hiddenRotatedQuat.w * l_conjugateQuat.w - l_hiddenRotatedQuat.x * l_conjugateQuat.x - l_hiddenRotatedQuat.y * l_conjugateQuat.y - l_hiddenRotatedQuat.z * l_conjugateQuat.z;
	l_finalRotatedQuat.x = l_hiddenRotatedQuat.x * l_conjugateQuat.w + l_hiddenRotatedQuat.w * l_conjugateQuat.x + l_hiddenRotatedQuat.y * l_conjugateQuat.z - l_hiddenRotatedQuat.z * l_conjugateQuat.y;
	l_finalRotatedQuat.y = l_hiddenRotatedQuat.y * l_conjugateQuat.w + l_hiddenRotatedQuat.w * l_conjugateQuat.y + l_hiddenRotatedQuat.z * l_conjugateQuat.x - l_hiddenRotatedQuat.x * l_conjugateQuat.z;
	l_finalRotatedQuat.z = l_hiddenRotatedQuat.z * l_conjugateQuat.w + l_hiddenRotatedQuat.w * l_conjugateQuat.z + l_hiddenRotatedQuat.x * l_conjugateQuat.y - l_hiddenRotatedQuat.y * l_conjugateQuat.x;

	return glm::vec3(l_finalRotatedQuat.x, l_finalRotatedQuat.y, l_finalRotatedQuat.z);
}

BaseActor::BaseActor()
{
}


BaseActor::~BaseActor()
{
}

void BaseActor::addChildActor(BaseActor* childActor)
{
	m_childActor.emplace_back(childActor);
	childActor->setParentActor(this);
}

const std::vector<BaseActor*>& BaseActor::getChildrenActors() const
{
	return m_childActor;
}

BaseActor* BaseActor::getParentActor() const
{
	return m_parentActor;
}

void BaseActor::setParentActor(BaseActor* parentActor)
{
	m_parentActor = parentActor;
}

void BaseActor::addChildComponent(BaseComponent * childComponent)
{
	m_childComponent.emplace_back(childComponent);
	childComponent->setParentActor(this);
}

const std::vector<BaseComponent*>& BaseActor::getChildrenComponents() const
{
	return m_childComponent;
}

Transform* BaseActor::getTransform()
{
	return &m_transform;
}


bool BaseActor::hasTransformChanged() const
{
	if (m_transform.getPos() != m_transform.getOldPos() || m_transform.getRot() != m_transform.getOldRot() || m_transform.getScale() != m_transform.getOldScale())
	{
		return true;
	}

	if (getParentActor() != nullptr)
	{
		if (getParentActor()->hasTransformChanged())
		{
			return true;
		}
	}
	return false;
}

glm::mat4 BaseActor::caclLocalPosMatrix() const
{
	glm::mat4 l_posMatrix;
	l_posMatrix = glm::translate(l_posMatrix, m_transform.getPos());
	return l_posMatrix;
}

glm::mat4 BaseActor::caclLocalRotMatrix() const
{
	glm::mat4 l_rotaionMartix = glm::toMat4(m_transform.getRot());
	return l_rotaionMartix;
}

glm::mat4 BaseActor::caclLocalScaleMatrix() const
{
	glm::mat4 l_scaleMatrix;
	l_scaleMatrix = glm::scale(l_scaleMatrix, m_transform.getScale());
	return l_scaleMatrix;
}

glm::vec3 BaseActor::caclWorldPos() const
{
	glm::mat4 l_parentTransformationMatrix;

	l_parentTransformationMatrix[0][0] = 1.0f;
	l_parentTransformationMatrix[1][1] = 1.0f;
	l_parentTransformationMatrix[2][2] = 1.0f;
	l_parentTransformationMatrix[3][3] = 1.0f;

	if (getParentActor() != nullptr && getParentActor()->hasTransformChanged())
	{
		l_parentTransformationMatrix = getParentActor()->caclTransformationMatrix();
	}

	return glm::vec3(l_parentTransformationMatrix[0][0] * m_transform.getPos().x + l_parentTransformationMatrix[1][0] * m_transform.getPos().y + l_parentTransformationMatrix[2][0] * m_transform.getPos().z + l_parentTransformationMatrix[3][0],
		l_parentTransformationMatrix[0][1] * m_transform.getPos().x + l_parentTransformationMatrix[1][1] * m_transform.getPos().y + l_parentTransformationMatrix[2][1] * m_transform.getPos().z + l_parentTransformationMatrix[3][1],
		l_parentTransformationMatrix[0][2] * m_transform.getPos().x + l_parentTransformationMatrix[1][2] * m_transform.getPos().y + l_parentTransformationMatrix[2][2] * m_transform.getPos().z + l_parentTransformationMatrix[3][2]);
}

glm::quat BaseActor::caclWorldRot() const
{
	glm::quat l_parentRotationQuat = glm::quat(1, 0, 0, 0);

	if (getParentActor() != nullptr)
	{
		l_parentRotationQuat = getParentActor()->caclWorldRot();
	}

	return l_parentRotationQuat * m_transform.getRot();
}

glm::vec3 BaseActor::caclWorldScale() const
{
	glm::vec3 l_parentScale = glm::vec3(1.0, 1.0, 1.0);

	if (getParentActor() != nullptr)
	{
		l_parentScale = getParentActor()->caclWorldScale();
	}

	return l_parentScale * m_transform.getScale();
}

glm::mat4 BaseActor::caclWorldPosMatrix() const
{
	glm::mat4 l_posMatrix;
	l_posMatrix = glm::translate(l_posMatrix, caclWorldPos());
	return l_posMatrix;
}

glm::mat4 BaseActor::caclWorldRotMatrix() const
{
	glm::mat4 l_rotaionMartix = glm::toMat4(caclWorldRot());
	return l_rotaionMartix;
}

glm::mat4 BaseActor::caclWorldScaleMatrix() const
{
	glm::mat4 l_scaleMatrix;
	l_scaleMatrix = glm::scale(l_scaleMatrix, caclWorldScale());
	return l_scaleMatrix;
}

glm::mat4 BaseActor::caclTransformationMatrix() const
{
	glm::mat4 l_posMatrix;
	l_posMatrix = glm::translate(l_posMatrix, m_transform.getPos());
	glm::mat4 l_rotaionMartix = glm::toMat4(m_transform.getRot());

	glm::mat4 l_scaleMatrix;
	l_scaleMatrix = glm::scale(l_scaleMatrix, m_transform.getScale());

	glm::mat4 l_parentTransformationMatrix;
	
	l_parentTransformationMatrix[0][0] = 1.0f;
	l_parentTransformationMatrix[1][1] = 1.0f;
	l_parentTransformationMatrix[2][2] = 1.0f;
	l_parentTransformationMatrix[3][3] = 1.0f;

	if (getParentActor() != nullptr && getParentActor()->hasTransformChanged())
	{
		l_parentTransformationMatrix = getParentActor()->caclTransformationMatrix();
	}

	return l_parentTransformationMatrix * l_posMatrix * l_rotaionMartix * l_scaleMatrix;
}

void BaseActor::initialize()
{
	for (size_t i = 0; i < m_childActor.size(); i++)
	{
		m_childActor[i]->initialize();
	}
	for (size_t i = 0; i < m_childComponent.size(); i++)
	{
		m_childComponent[i]->initialize();
	}
	this->setStatus(objectStatus::ALIVE);
}

void BaseActor::update()
{
	m_transform.update();
	if (m_childActor.size() != 0)
	{
		for (size_t i = 0; i < getChildrenActors().size(); i++)
		{
			m_childActor[i]->update();
		}
	}
	if (m_childComponent.size() != 0)
	{
		for (size_t i = 0; i < m_childComponent.size(); i++)
		{
			m_childComponent[i]->update();
		}
	}
}

void BaseActor::shutdown()
{
	for (size_t i = 0; i < getChildrenActors().size(); i++)
	{
		getChildrenActors()[i]->shutdown();
	}
	for (size_t i = 0; i < m_childComponent.size(); i++)
	{
		m_childComponent[i]->shutdown();
	}
	this->setStatus(objectStatus::SHUTDOWN);
}

BaseComponent::BaseComponent()
{
}

BaseComponent::~BaseComponent()
{
}

BaseActor* BaseComponent::getParentActor() const
{
	return m_parentActor;
}

void BaseComponent::setParentActor(BaseActor * parentActor)
{
	m_parentActor = parentActor;
}

Transform* BaseComponent::getTransform()
{
	return m_parentActor->getTransform();
}
