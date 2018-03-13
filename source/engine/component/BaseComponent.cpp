#include "BaseComponent.h"

BaseComponent::BaseComponent()
{
}

BaseComponent::~BaseComponent()
{
}

IEntity* BaseComponent::getParentEntity() const
{
	return m_parentEntity;
}

void BaseComponent::setParentEntity(IEntity* parentEntity)
{
	m_parentEntity = parentEntity;
}

const objectStatus & BaseComponent::getStatus() const
{
	return m_objectStatus;
}