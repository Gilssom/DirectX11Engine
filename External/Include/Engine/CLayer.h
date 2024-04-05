#pragma once
#include "CEntity.h"

class CGameObject;

class CLayer : public CEntity
{
private:
	vector<CGameObject*> m_vecParent;  // ���� Layer �� �ҼӵǾ� �ִ� �ֻ��� �θ� ������Ʈ�� ����
	vector<CGameObject*> m_vecObjects; // ���� Layer �� �ҼӵǾ� �ִ� ��� ������Ʈ�鸸 ����
	int					 m_LayerIdx;

public:
	void Init();
	void Tick();
	void FinalTick();


public:
	// childMove = object �� �ڽĵ鵵 �ش� Layer �� ���� �ű� ������, �ű��� ���� ������
	void AddObject(CGameObject* object, bool childMove = false);

	void RegisterObject(CGameObject* object) { m_vecObjects.push_back(object); }
	void Clear() { m_vecObjects.clear(); }

	const vector<CGameObject*>& GetObjects() { return m_vecObjects; }


	CLONE_DISABLE(CLayer);

public:
	CLayer();
	~CLayer();

	friend class CLevel;
};

