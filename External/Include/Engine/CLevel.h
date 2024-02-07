#pragma once
#include "CEntity.h"

class CLayer;

class CLevel : public CEntity
{
private:
	CLayer* m_arrLayer[MAX_LAYER];


public:
	CLevel();
	~CLevel();
};

