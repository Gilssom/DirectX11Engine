#pragma once
#include "CRenderComponent.h"

class CStructuredBuffer;

class CParticleSystem : public CRenderComponent
{
private:
	CStructuredBuffer*	m_ParticleBuffer;	// ����ȭ ���۷� GPU �޸� ���޿�

	UINT				m_MaxParticle;		// ��ƼŬ �ִ� ����
	Ptr<CTexture>		m_ParticleTex;		// ��ƼŬ ���� �ؽ�ó


public:
	void SetParticleTexture(Ptr<CTexture> tex) { m_ParticleTex = tex; }


public:
	virtual void FinalTick() override;
	virtual void Render() override;


public:
	CParticleSystem();
	~CParticleSystem();

};

