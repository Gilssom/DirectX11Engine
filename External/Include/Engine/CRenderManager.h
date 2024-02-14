#pragma once
#include "Singletone.h"

class CCamera;

class CRenderManager : public CSingleton<CRenderManager>
{
	SINGLE(CRenderManager);

private:
	vector<CCamera*>	m_vecCam;


public:
	void RegisterCamera(CCamera* camera, int priority);


public:
	void Init();
	void Tick();
	void Render();
};

