#pragma once
#include "CRenderComponent.h"

class CStructuredBuffer;

class CParticleSystem : public CRenderComponent
{
private:
	CStructuredBuffer*	m_ParticleBuffer;	// ����ȭ ���۷� GPU �޸� ���޿�

	UINT				m_MaxParticle;		// ��ƼŬ �ִ� ����


public:
	virtual void FinalTick() override;
	virtual void Render() override;


public:
	CParticleSystem();
	~CParticleSystem();

};

