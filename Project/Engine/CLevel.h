#pragma once
#include "CEntity.h"

class CLayer;
class CGameObject;

class CLevel : public CEntity
{
private:
	CLayer* m_arrLayer[MAX_LAYER];


public:
	void Init();
	void Tick();
	void FinalTick();
	void Render();


public:
	void AddObject(UINT layerIdx, CGameObject* object);

public:
	CLevel();
	~CLevel();
};

