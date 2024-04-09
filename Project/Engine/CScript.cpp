#include "pch.h"
#include "CScript.h"

#include "CTransform.h"

CScript::CScript()
	: CComponent(COMPONENT_TYPE::SCRIPT)
{
}

CScript::~CScript()
{
}

CGameObject* CScript::Instantiate(Ptr<CPrefab> prefab, int layerIdx, const Vec3& worldPos)
{
	CGameObject* pInst = prefab->Instantiate();
	pInst->Transform()->SetRelativePos(worldPos);
	SpawnObject(layerIdx, pInst);

	return pInst;
}