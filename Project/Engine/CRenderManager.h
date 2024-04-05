#pragma once

#include "CTexture.h"

class CCamera;
class CLight2D;
class CStructuredBuffer;

class CRenderManager : public CSingleton<CRenderManager>
{
	SINGLE(CRenderManager);

private:
	vector<CCamera*>	m_vecCam;
	vector<CLight2D*>	m_vecLight2D;		// 매 프레임마다 등록해야함 ( = Layer )
	CStructuredBuffer*	m_Light2DBuffer;	// 구조화 버퍼

	Ptr<CTexture>		m_RenderTargetCopyTex;


public:
	void RegisterCamera(CCamera* camera, int priority);
	int RegisterLight2D(CLight2D* light2D) 
	{ 
		m_vecLight2D.push_back(light2D);
		return (int)m_vecLight2D.size() - 1; // 마지막 Index 알려줌
	}

	void CopyRenderTarget();

public:
	void Init();
	void Tick();
	void Render();

private:
	void DataBinding();
	void DataClear();
};

