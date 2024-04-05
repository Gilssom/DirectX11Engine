#include "pch.h"
#include "CPrefab.h"

#include "CGameObject.h"

CPrefab::CPrefab()
	: CAsset(ASSET_TYPE::PREFAB)
	, m_ProtoObject(nullptr)
{

}

CPrefab::~CPrefab()
{
	delete m_ProtoObject;
}
