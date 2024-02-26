#pragma once
#include "CComponent.h"

#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CAssetManager.h"

#include "components.h"

// �߻� Ŭ���� ����
class CScript : public CComponent
{
private:


public:
	virtual void Tick() = 0; // Tick �� �� �����ϵ��� ����
	virtual void FinalTick() final {} // �� �����δ� FinalTick �� override �� �� ����

public:
	virtual void BeginOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider) {}
	virtual void Overlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider) {}
	virtual void EndOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider) {}

public:
	CScript();
	~CScript();
};

