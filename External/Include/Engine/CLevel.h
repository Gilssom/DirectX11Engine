#pragma once
#include "CEntity.h"

class CLayer;
class CGameObject;

class CLevel : public CEntity
{
private:
	CLayer*			m_arrLayer[MAX_LAYER];
	LEVEL_STATE		m_State;

public:
	void Init();
	void Tick();
	void FinalTick();
	void RegisterClear();

public:
	void AddObject(UINT layerIdx, CGameObject* object, bool childMove = false);
	CLayer* GetLayer(int layerIdx) { return m_arrLayer[layerIdx]; }
	LEVEL_STATE GetState() { return m_State; }

private:
	void ChangeState(LEVEL_STATE nextState);

public:
	CLONE_DISABLE(CLevel);

public:
	CLevel();
	~CLevel();

	friend class CTaskManager;
};

