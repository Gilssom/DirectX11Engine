#include "pch.h"
#include "CParticleSystem.h"

#include "CTransform.h"

#include "CDevice.h"
#include "CStructuredBuffer.h"

#include "CTimeManager.h"

CParticleSystem::CParticleSystem()
	: CRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_ParticleBuffer(nullptr)
	, m_Time(0.f)
	, m_MaxParticle(1000)
{
	// Particle Tick �뵵 Compute Shader
	m_TickCS = (CParticleTickCS*)CAssetManager::GetInst()->FindAsset<CComputeShader>(L"ParticleTickCS").Get();


	// Particle System �� ����� Mesh �� Material ����
	SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"PointMesh")); // ���� �ϳ��� �������� Geometry Shader �� ������.
	SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"ParticleMaterial"));


	// Particle ������ ������ ����ȭ ���� ����
	// Tick �� �������� �����͸� ������ ������ �ʿ䵵 ����
	Vec2 vResolution = CDevice::GetInst()->GetRenderResolution();
	float fTerm = vResolution.x / (m_MaxParticle + 1);

	/*tParticle arrParticle[100] = {};

	for (int i = 0; i < m_MaxParticle; ++i)
	{
		arrParticle[i].vWorldPos = Vec3(-(vResolution.x / 2.f) + (i + 1) * fTerm, 0.f, 100.f);
		arrParticle[i].vWorldScale = Vec3(10.f, 10.f, 1.f);
		arrParticle[i].Active = 0;
	}*/

	m_ParticleBuffer = new CStructuredBuffer;
	m_ParticleBuffer->Create(sizeof(tParticle), m_MaxParticle, SB_TYPE::SRV_UAV, false);

	m_SpawnCountBuffer = new CStructuredBuffer;
	m_SpawnCountBuffer->Create(sizeof(tSpawnCount), 1, SB_TYPE::SRV_UAV, true);


	// Particle Module Setting Test
	m_Module.Module[(UINT)PARTICLE_MODULE::SPAWN] = true;
	m_Module.vSpawnRate = 20;
	m_Module.vSpawnColor = Vec3(1.f, 0.f, 0.f);
	m_Module.MinLife = 1.f;
	m_Module.MaxLife = 4.f;
	m_Module.vSpawnMinScale = Vec3(10.f, 10.f, 1.f);
	m_Module.vSpawnMaxScale = Vec3(20.f, 20.f, 1.f);

	m_ModuleBuffer = new CStructuredBuffer;
	m_ModuleBuffer->Create(sizeof(tParticleModule) + (16 - sizeof(tParticleModule) % 16), 1, SB_TYPE::SRV_UAV, true, &m_Module);
}

CParticleSystem::~CParticleSystem()
{
	delete m_ParticleBuffer;
	delete m_SpawnCountBuffer;
	delete m_ModuleBuffer;
}

void CParticleSystem::FinalTick()
{
	// ���� CPU ���� ������ �ϰ� �Ǹ� ���⼭ ��õ ����� �ݺ����� �������� �Ѵ�.
	// �� ���� GPU ���� ó���� �ϵ��� ���踦 �Ѵ�.

	// Spawn Count ���
	CalculateSpawnCount();

	// Compute Shader Excecute
	m_TickCS->SetParticleWorldPos(Transform()->GetWorldPos());
	m_TickCS->SetParticleModuleBuffer(m_ModuleBuffer);
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

	// Instance �� Render �� Inatance ���� ID(���°) �� �ڵ����� �Ѱ���
	// ��� ���ڵ��� �ݺ����� ���� Render �� ������ �ν��Ͻ��� �ξ� �� ������ �� �ߵǰ� ȿ������
	GetMesh()->Render_Particle(m_MaxParticle);

	// Clear
	m_ParticleBuffer->Clear_SRV();
}

void CParticleSystem::CalculateSpawnCount()
{
	if (m_Module.Module[(UINT)PARTICLE_MODULE::SPAWN] == false)
		return;

	// Spawn Rate (�̹� Tick ���� ��ƼŬ �ϳ��� ������ �ð�)
	float Term = 1.f / (float)m_Module.vSpawnRate;
	m_Time += DT; 
	UINT SpawnCount = 0;	// SpawnCount Per Tick

	// �ð��� Term �� ���� ��츦 ����ؼ� �߰� ���� (1�ʿ� 10000�� �������� ���)
	if (Term < m_Time)
	{
		float Value = m_Time / Term;
		SpawnCount = (UINT)Value;
		m_Time -= (float)SpawnCount * Term;
	}

	// SpawnCount Buffer ����
	tSpawnCount count = { SpawnCount , };
	m_SpawnCountBuffer->SetData(&count);
}