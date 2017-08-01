#include "stdafx.h"
#include "IVisibleGameEntity.h"


IVisibleGameEntity::IVisibleGameEntity()
{
}


IVisibleGameEntity::~IVisibleGameEntity()
{
}

const int IVisibleGameEntity::getVisibleGameEntityType() const
{
	return m_visibleGameEntityType;
}

void IVisibleGameEntity::setVisibleGameEntityType(visibleGameEntityType visibleGameEntityType)
{
	m_visibleGameEntityType = visibleGameEntityType;
}
