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
	vector<CLight2D*>	m_vecLight2D;		// �� �����Ӹ��� ����ؾ��� ( = Layer )
	CStructuredBuffer*	m_Light2DBuffer;	// ����ȭ ����

	Ptr<CTexture>		m_RenderTargetCopyTex;


public:
	void RegisterCamera(CCamera* camera, int priority);
	int RegisterLight2D(CLight2D* light2D) 
	{ 
		m_vecLight2D.push_back(light2D);
		return (int)m_vecLight2D.size() - 1; // ������ Index �˷���
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

