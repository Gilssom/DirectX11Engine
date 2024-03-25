#pragma once
#include "CComputeShader.h"

class CStructuredBuffer;

class CParticleTickCS : public CComputeShader
{
private:
	CStructuredBuffer* m_ParticleBuffer;
	CStructuredBuffer* m_SpawnCountBuffer;


public:
	void SetParticleBuffer(CStructuredBuffer* buffer) { m_ParticleBuffer = buffer; }
	void SetSpawnCount(CStructuredBuffer* buffer) { m_SpawnCountBuffer = buffer; }


public:
	virtual int Binding() override;
	virtual void CalculateGroupNum() override;
	virtual void Clear() override;


public:
	CParticleTickCS();
	~CParticleTickCS();
};

