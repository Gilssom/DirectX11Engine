#pragma once
#include "CEntity.h"

class CLayer;
class CGameObject;

class CLevel : public CEntity
{
private:
	CLayer* m_arrLayer[MAX_LAYER];


public:
	void AddObject(UINT layerIdx, CGameObject* object);

public:
	void Init();
	void Tick();
	void FinalTick();
	void Render();

public:
	CLevel();
	~CLevel();
};

