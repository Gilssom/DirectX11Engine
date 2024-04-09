#include "pch.h"
#include "CPrefab.h"

#include "CGameObject.h"
#include "CTransform.h"

CPrefab::CPrefab()
	: CAsset(ASSET_TYPE::PREFAB)
	, m_ProtoObject(nullptr)
{

}

CPrefab::CPrefab(CGameObject* proto)
	: CAsset(ASSET_TYPE::PREFAB)
	, m_ProtoObject(proto)
{
	m_ProtoObject->Transform()->SetRelativePos(0.f, 0.f, 0.f);
}

CPrefab::CPrefab(const CPrefab& other)
	: CAsset(other)
	, m_ProtoObject(nullptr)
{
	// Prefab ³¢¸®ÀÇ º¹Á¦
	m_ProtoObject = other.m_ProtoObject->Clone();
	m_ProtoObject->Transform()->SetRelativePos(0.f, 0.f, 0.f);
}

CPrefab::~CPrefab()
{
	delete m_ProtoObject;
}

CGameObject* CPrefab::Instantiate()
{
	return m_ProtoObject->Clone();
}