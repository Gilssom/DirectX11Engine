#pragma once
#include "CEntity.h"

class CLayer;
class CGameObject;

class CLevel : public CEntity
{
private:
	CLayer*			m_arrLayer[MAX_LAYER];
	LEVEL_STATE		m_State;
	
	CLevel*			m_NextLevel;

public:
	void Init();
	void Tick();
	void FinalTick();
	void RegisterClear();

public:
	void AddObject(UINT layerIdx, CGameObject* object, bool childMove = false);
	CLayer* GetLayer(int layerIdx) { return m_arrLayer[layerIdx]; }
	LEVEL_STATE GetState() { return m_State; }

	// 특정 이름을 가진 GameObject 를 검색(제일 먼저 검출된 Object 반환)
	CGameObject* FindObjectByName(const wstring& name);

	// 특정 이름을 가진 GameObject 를 모두 검색
	void FindObjectByName(const wstring& name, vector<CGameObject*>& vecObject );

	// 특정 Component 를 가진 GameObject 를 검색(제일 먼저 검출된 Object 반환)
	CGameObject* FindObjectByComponent(COMPONENT_TYPE type, const wstring& name);

	// 특정 Component 를 가진 GameObject 를 모두 검색
	void FindObjectByComponent(COMPONENT_TYPE type, vector<CGameObject*>& vecObject);

	// 현재 Level 의 다음 Level 이 어느곳인지 저장 및 반환
	void SetNextLevel(CLevel* nextLevel) { m_NextLevel = nextLevel; }
	CLevel* GetNextLevel() { return m_NextLevel; }

private:
	void ChangeState(LEVEL_STATE nextState);

public:
	CLONE_DISABLE(CLevel);

public:
	CLevel();
	~CLevel();

	friend class CTaskManager;
};

