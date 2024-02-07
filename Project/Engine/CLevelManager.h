#pragma once
#include "Singletone.h"

class CLevelManager : public CSingleton<CLevelManager>
{
	SINGLE(CLevelManager)

private:
	CLevel* m_CurLevel;


public:
	void Init();
	void Tick();
	void Render();
};

