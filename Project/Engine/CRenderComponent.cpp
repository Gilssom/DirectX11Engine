#include "pch.h"
#include "CRenderComponent.h"

CRenderComponent::CRenderComponent(COMPONENT_TYPE type)
	: CComponent(type)
{

}

CRenderComponent::~CRenderComponent()
{

}

void CRenderComponent::SetMaterial(Ptr<CMaterial> material)
{
	// ���� ������ ���ù��� �� ����.
	assert(!material->IsDynamic());

	m_SharedMaterial = material;
	m_CurMaterial = m_SharedMaterial;
}

Ptr<CMaterial> CRenderComponent::GetDynamicMaterial()
{
	// ���� ��ü�� ������ ���� ���ٸ� nullptr ��ȯ
	if (m_SharedMaterial == nullptr)
		return nullptr;

	// ���� ������ ������ ������ �߾��ٸ� ��ȯ
	if (m_DynamicMaterial != nullptr)
		return m_DynamicMaterial;
	
	// ���� ���ǰ� �ִ� ������ ���� ������ ����
	m_DynamicMaterial = m_SharedMaterial->GetDynamicMaterial();
	m_CurMaterial = m_DynamicMaterial;

	return m_DynamicMaterial;
}

void CRenderComponent::RestoreMaterial()
{
	// Shared ������ �ٽ� ����
	m_CurMaterial = m_SharedMaterial;
	m_DynamicMaterial = nullptr;
}