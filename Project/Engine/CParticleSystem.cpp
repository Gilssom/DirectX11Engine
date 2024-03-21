#include "pch.h"
#include "CParticleSystem.h"

#include "CTransform.h"

#include "CDevice.h"
#include "CStructuredBuffer.h"

CParticleSystem::CParticleSystem()
	: CRenderComponent(COMPONENT_TYPE::PARTICLESYSTEM)
	, m_ParticleBuffer(nullptr)
	, m_MaxParticle(100)
{
	// Particle System �� ����� Mesh �� Material ����
	SetMesh(CAssetManager::GetInst()->FindAsset<CMesh>(L"PointMesh")); // ���� �ϳ��� �������� Geometry Shader �� ������.
	SetMaterial(CAssetManager::GetInst()->FindAsset<CMaterial>(L"ParticleMaterial"));


	// Particle ������ ������ ����ȭ ���� ����
	// Particle 10���� ������ ����ȭ ���ۿ� ���� ����
	Vec2 vResolution = CDevice::GetInst()->GetRenderResolution();
	float fTerm = vResolution.x / (m_MaxParticle + 1);

	tParticle arrParticle[100] = {};

	for (int i = 0; i < m_MaxParticle; i++)
	{
		arrParticle[i].vWorldPos = Vec3(-(vResolution.x / 2.f) + (i + 1) * fTerm, 0.f, 100.f);
		arrParticle[i].vWorldScale = Vec3(10.f, 10.f, 1.f);
		arrParticle[i].Active = 1;

		if (i > (m_MaxParticle / 2))
			arrParticle[i].Active = 0;
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
	// ���� CPU ���� ������ �ϰ� �Ǹ� ���⼭ ��õ ����� �ݺ����� �������� �Ѵ�.
	// �� ���� GPU ���� ó���� �ϵ��� ���踦 �Ѵ�.

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
	GetMaterial()->Binding();

	// Instance �� Render �� Inatance ���� ID(���°) �� �ڵ����� �Ѱ���
	// ��� ���ڵ��� �ݺ����� ���� Render �� ������ �ν��Ͻ��� �ξ� �� ������ �� �ߵǰ� ȿ������
	GetMesh()->Render_Particle(m_MaxParticle);

	// Clear
	m_ParticleBuffer->Clear_SRV();
}