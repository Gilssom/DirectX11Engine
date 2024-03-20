#include "pch.h"
#include "CParticleSystem.h"

#include "CTransform.h"

#include "CDevice.h"
#include "CStructuredBuffer.h"

CParticleSystem::CParticleSystem()
	: CRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_ParticleBuffer(nullptr)
	, m_MaxParticle(10)
{
	// Particle System 이 사용할 Mesh 와 Material 설정
	SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"ParticleMaterial"));


	// Particle 정보를 저장할 구조화 버퍼 생성
	// Particle 10개의 정보를 구조화 버퍼에 강제 세팅
	Vec2 vResolution = CDevice::GetInst()->GetRenderResolution();
	float fTerm = vResolution.x / (m_MaxParticle + 1);

	tParticle arrParticle[10] = {};

	for (int i = 0; i < m_MaxParticle; i++)
	{
		arrParticle[i].vWorldPos = Vec3(-(vResolution.x / 2.f) + (i + 1) * fTerm, 0.f, 100.f);
		arrParticle[i].vWorldScale = Vec3(10.f, 10.f, 1.f);
		arrParticle[i].Active = 1;
	}

	m_ParticleBuffer = new CStructuredBuffer;
	m_ParticleBuffer->Create(sizeof(tParticle), m_MaxParticle, SB_TYPE::SRV_UAV, false, arrParticle);
}

CParticleSystem::~CParticleSystem()
{
	delete m_ParticleBuffer;
}

void CParticleSystem::FinalTick()
{
	// 원래 CPU 에서 연산을 하게 되면 여기서 몇천 몇만번의 반복문이 돌아져야 한다.
	// 이 일을 GPU 에서 처리를 하도록 설계를 한다.

	// Binding
	m_ParticleBuffer->Binding_CS_UAV(0);

	// Compute Shader Excecute

	// Clear
	m_ParticleBuffer->Clear_UAV();
}

void CParticleSystem::Render()
{
	// Test Particle Render
	m_ParticleBuffer->Binding(17);
	Transform()->Binding();

	for (int i = 0; i < m_MaxParticle; i++)
	{
		GetMaterial()->SetScalarParam(INT_0, i);
		GetMaterial()->Binding();

		GetMesh()->Render();
	}

	// Clear
	m_ParticleBuffer->Clear_SRV();
}