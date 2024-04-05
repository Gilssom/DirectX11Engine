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


public:
	void AddObject(UINT layerIdx, CGameObject* object, bool childMove = false);
	CLayer* GetLayer(int layerIdx) { return m_arrLayer[layerIdx]; }


	CLONE_DISABLE(CLevel);

public:
	CLevel();
	~CLevel();
};

