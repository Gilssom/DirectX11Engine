#pragma once
#include "CComponent.h"

#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CAssetManager.h"

#include "components.h"

// 추상 클래스 정의
class CScript : public CComponent
{
private:


public:
	virtual void Tick() = 0; // Tick 은 꼭 구현하도록 강제
	virtual void FinalTick() final {} // 이 밑으로는 FinalTick 을 override 할 수 없게

public:
	virtual void BeginOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider) {}
	virtual void Overlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider) {}
	virtual void EndOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider) {}

public:
	CScript();
	~CScript();
};

