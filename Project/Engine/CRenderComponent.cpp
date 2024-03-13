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
	// 동적 재질을 세팅받을 수 없다.
	assert(!material->IsDynamic());

	m_SharedMaterial = material;
	m_CurMaterial = m_SharedMaterial;
}

Ptr<CMaterial> CRenderComponent::GetDynamicMaterial()
{
	// 재질 자체를 참조한 적이 없다면 nullptr 반환
	if (m_SharedMaterial == nullptr)
		return nullptr;

	// 동적 재질을 이전에 생성을 했었다면 반환
	if (m_DynamicMaterial != nullptr)
		return m_DynamicMaterial;
	
	// 현재 사용되고 있는 재질도 동적 재질로 변경
	m_DynamicMaterial = m_SharedMaterial->GetDynamicMaterial();
	m_CurMaterial = m_DynamicMaterial;

	return m_DynamicMaterial;
}

void CRenderComponent::RestoreMaterial()
{
	// Shared 재질로 다시 복구
	m_CurMaterial = m_SharedMaterial;
	m_DynamicMaterial = nullptr;
}