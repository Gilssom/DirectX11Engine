#pragma once
#include "CEntity.h"

class CGameObject;

class CLayer : public CEntity
{
private:
	vector<CGameObject*> m_vecParent;  // 현재 Layer 에 소속되어 있는 최상위 부모 오브젝트만 관리
	vector<CGameObject*> m_vecObjects; // 현재 Layer 에 소속되어 있는 모든 오브젝트들만 관리
	int					 m_LayerIdx;

public:
	void Init();
	void Tick();
	void FinalTick();


public:
	void AddObject(CGameObject* object);
	void RegisterObject(CGameObject* object) { m_vecObjects.push_back(object); }
	void Clear() { m_vecObjects.clear(); }

	const vector<CGameObject*>& GetObjects() { return m_vecObjects; }

public:
	CLayer();
	~CLayer();

	friend class CLevel;
};

