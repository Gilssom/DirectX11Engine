#pragma once
#include "CRenderComponent.h"
#include "CParticleTickCS.h"

struct tSpawnCount
{
	int		SpawnCount;
	UINT	padding[3];
};


class CStructuredBuffer;

class CParticleSystem : public CRenderComponent
{
private:
	Ptr<CParticleTickCS>	m_TickCS;
	CStructuredBuffer*		m_ParticleBuffer;	// ����ȭ ���۷� GPU �޸� ���� �뵵
	CStructuredBuffer*		m_SpawnCountBuffer;	// Spawn Count ���� ���� �뵵
	CStructuredBuffer*		m_ModuleBuffer;		// Module ���� ���� �뵵

	Ptr<CTexture>			m_ParticleTex;		// ��ƼŬ ���� �ؽ�ó

	float					m_Time;				// ��ƼŬ ���� ���� �ð�

	// Particle Data
	UINT					m_MaxParticle;		// ��ƼŬ �ִ� ����

	tParticleModule			m_Module;			// ��ƼŬ�� ��� ����


public:
	void SetParticleTexture(Ptr<CTexture> tex) { m_ParticleTex = tex; }


private:
	void CalculateSpawnCount();

public:
	virtual void FinalTick() override;
	virtual void Render() override;


public:
	CParticleSystem();
	~CParticleSystem();

};

