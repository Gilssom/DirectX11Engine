#pragma once
#include "CRenderComponent.h"

class CStructuredBuffer;

class CParticleSystem : public CRenderComponent
{
private:
	CStructuredBuffer*	m_ParticleBuffer;	// 구조화 버퍼로 GPU 메모리 전달용

	UINT				m_MaxParticle;		// 파티클 최대 개수
	Ptr<CTexture>		m_ParticleTex;		// 파티클 입자 텍스처


public:
	void SetParticleTexture(Ptr<CTexture> tex) { m_ParticleTex = tex; }


public:
	virtual void FinalTick() override;
	virtual void Render() override;


public:
	CParticleSystem();
	~CParticleSystem();

};

