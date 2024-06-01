#pragma once
#include <Engine\\CScript.h>

class CStructuredBuffer;

class CPlayerScript : public CScript
{
private:
	float			m_Speed;
	CGameObject*	m_TargetMonster;
	Ptr<CPrefab>	m_ParticlePrefab;
	Ptr<CPrefab>	m_MissilePrefab;

	bool			m_MoveLeft;
	bool			m_MoveRight;

public:
	void SetTarget(CGameObject* target) { m_TargetMonster = target; }
	bool GetMoveLeft() { return m_MoveLeft; }
	bool GetMoveRight() { return m_MoveRight; }

public:
	virtual void Begin() override;
	virtual void Tick() override;

	virtual void BeginOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider) override;
	virtual void Overlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider) override;
	virtual void EndOverlap(CCollider2D* ownerCollider, CGameObject* otherObject, CCollider2D* otehrCollider) override;

public:
	virtual void SaveToLevelFile(FILE* file) override;
	virtual void LoadFromLevelFile(FILE* file) override;

	CLONE(CPlayerScript);

public:
	CPlayerScript();
	~CPlayerScript();
};