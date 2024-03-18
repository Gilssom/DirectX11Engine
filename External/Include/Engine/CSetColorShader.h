#pragma once
#include "CComputeShader.h"

#include "CTexture.h"

class CSetColorShader : public CComputeShader
{
private:
	Ptr<CTexture>	m_TargetTex;


public:
	void SetTargetTextrue(Ptr<CTexture> tex) { m_TargetTex = tex; }


public:
	virtual int Binding() override;
	virtual void CalculateGroupNum() override;
	virtual void Clear() override;


public:
	CSetColorShader();
	~CSetColorShader();
};

