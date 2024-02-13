#pragma once
#include "CEntity.h"

class CGameObject;

class CLayer : public CEntity
{
private:
	vector<CGameObject*> m_vecObjects;

public:
	void Init();
	void Tick();
	void FinalTick();
	void Render();


public:
	void Begin();
	void Tick();
	void FinalTick();
	void Render();


public:
	void Begin();
	void Tick();
	void FinalTick();
	void Render();


public:
	void AddObject(CGameObject* object) { m_vecObjects.push_back(object); }


public:
	CLayer();
	~CLayer();

};

