#pragma once
#include "Singletone.h"

class CLevel;

class CLevelManager : public CSingleton<CLevelManager>
{
	SINGLE(CLevelManager)

private:
	CLevel* m_CurLevel;

public:
	CLevel* GetCurrentLevel() { return m_CurLevel; }

public:
	void Init();
	void Tick();
	void Render();
};

