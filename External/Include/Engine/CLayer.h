#pragma once
#include "CEntity.h"

#include "CGameObject.h"

class CLayer : public CEntity
{
private:
	vector<CGameObject*> m_vecObjects;


public:
	CLayer();
	~CLayer();

};

