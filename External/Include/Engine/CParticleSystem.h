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
	CStructuredBuffer*		m_ParticleBuffer;	// 구조화 버퍼로 GPU 메모리 전달용
	CStructuredBuffer*		m_SpawnCountBuffer;	// Spawn Count 정보 전달 용도

	Ptr<CTexture>			m_ParticleTex;		// 파티클 입자 텍스처

	UINT					m_SpawnCount;		// SpawnCount Per Tick
	float					m_Time;				// 파티클 생성 누적 시간

	// Particle Data
	UINT					m_MaxParticle;		// 파티클 최대 개수
	UINT					m_SpawnRate;		// 초당 파티클 생성 개수 (Spawn Per Second)


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

