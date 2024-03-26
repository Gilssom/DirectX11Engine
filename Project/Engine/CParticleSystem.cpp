#include "pch.h"
#include "CParticleSystem.h"

#include "CTransform.h"

#include "CDevice.h"
#include "CStructuredBuffer.h"

#include "CTimeManager.h"

CParticleSystem::CParticleSystem()
	: CRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_ParticleBuffer(nullptr)
	, m_SpawnCount(0)
	, m_Time(0.f)
	, m_MaxParticle(100)
	, m_SpawnRate(10)
{
	// Particle Tick 용도 Compute Shader
	m_TickCS = (CParticleTickCS*)CAssetManager::GetInst()->FindAsset<CComputeShader>(L"ParticleTickCS").Get();


	// Particle System 이 사용할 Mesh 와 Material 설정
	SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"PointMesh")); // 정점 하나를 기준으로 Geometry Shader 로 보낸다.
	SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"ParticleMaterial"));


	// Particle 정보를 저장할 구조화 버퍼 생성
	// Tick 이 생겼으니 데이터를 강제로 세팅할 필요도 없음
	Vec2 vResolution = CDevice::GetInst()->GetRenderResolution();
	float fTerm = vResolution.x / (m_MaxParticle + 1);

	tParticle arrParticle[100] = {};

	for (int i = 0; i < m_MaxParticle; ++i)
	{
		arrParticle[i].vWorldPos = Vec3(-(vResolution.x / 2.f) + (i + 1) * fTerm, 0.f, 100.f);
		arrParticle[i].vWorldScale = Vec3(10.f, 10.f, 1.f);
		arrParticle[i].Active = 0;
	}

	m_ParticleBuffer = new CStructuredBuffer;
	m_ParticleBuffer->Create(sizeof(tParticle), m_MaxParticle, SB_TYPE::SRV_UAV, false, arrParticle);

	m_SpawnCountBuffer = new CStructuredBuffer;
	m_SpawnCountBuffer->Create(sizeof(tSpawnCount), 1, SB_TYPE::SRV_UAV, true);
}

CParticleSystem::~CParticleSystem()
{
	delete m_ParticleBuffer;
	delete m_SpawnCountBuffer;
}

void CParticleSystem::FinalTick()
{
	// 원래 CPU 에서 연산을 하게 되면 여기서 몇천 몇만번의 반복문이 돌아져야 한다.
	// 이 일을 GPU 에서 처리를 하도록 설계를 한다.

	// Spawn Count 계산
	CalculateSpawnCount();

	// Compute Shader Excecute
	m_TickCS->SetParticleBuffer(m_ParticleBuffer);
	m_TickCS->SetSpawnCount(m_SpawnCountBuffer);
	
	if (FAILED(m_TickCS->Execute()))
	{
		assert(nullptr);
	}
}

void CParticleSystem::Render()
{
	// Test Particle Render
	m_ParticleBuffer->Binding(17);
	Transform()->Binding();

	GetMaterial()->SetTexParam(TEX_0, m_ParticleTex);
	GetMaterial()->Binding();

	// Instance 로 Render 시 Inatance 고유 ID(몇번째) 를 자동으로 넘겨줌
	// 모든 입자들을 반복문을 통해 Render 할 때보다 인스턴싱이 훨씬 더 프레임 방어도 잘되고 효율적임
	GetMesh()->Render_Particle(m_MaxParticle);

	// Clear
	m_ParticleBuffer->Clear_SRV();
}

void CParticleSystem::CalculateSpawnCount()
{
	// Spawn Rate (이번 Tick 에서 파티클 하나가 생성될 시간)
	float Term = 1.f / (float)m_SpawnRate;
	m_Time += DT;
	m_SpawnCount = 0;

	// 시간이 Term 을 넘을 경우를 대비해서 추가 연산 (1초에 10000개 생성같은 경우)
	if (Term < m_Time)
	{
		float Value = m_Time / Term;
		m_SpawnCount = (UINT)Value;
		m_Time -= (float)m_SpawnCount * Term;
	}

	// SpawnCount Buffer 전달
	tSpawnCount count = { m_SpawnCount , };
	m_SpawnCountBuffer->SetData(&count);
}