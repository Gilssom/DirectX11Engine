#pragma once
#include "CScript.h"

class CPlayerScript : public CScript
{
private:
	float		 m_Speed;
	CGameObject* m_TargetMonster;

public:
	void SetTarget(CGameObject* target) { m_TargetMonster = target; }

public:
	virtual void Tick() override;

	virtual void BeginOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider) override;
	virtual void Overlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider) override;
	virtual void EndOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider) override;

public:
	CPlayerScript();
	~CPlayerScript();
};

