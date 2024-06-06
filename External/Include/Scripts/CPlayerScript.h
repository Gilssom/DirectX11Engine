#pragma once
#include <Engine\\CScript.h>

class CStructuredBuffer;

class CPlayerScript : public CScript
{
private:
	float			m_Speed;
	CGameObject*	m_TargetMonster;

	bool			m_MoveLeft;
	bool			m_MoveRight;

	bool			m_CanMoveLeft, m_CanMoveRight, m_CanMoveUp, m_CanMoveDown;

	bool			m_IsFightLevel;
	bool			m_IsSkill;

	bool			m_IsCombo;
	int				m_ComboIndex;
	float			m_ComboTimer;
	const float		m_MaxComboTime;

public:
	void SetTarget(CGameObject* target) { m_TargetMonster = target; }
	bool GetMoveLeft() { return m_MoveLeft; }
	bool GetMoveRight() { return m_MoveRight; }
	bool GetMove() { if (m_CanMoveLeft && m_CanMoveRight && m_CanMoveUp && m_CanMoveDown) return true; else return false; }

public:
	void AnimationInit();
	void Move();
	void Skill();
	void AttackCombo(int comboIndex);
	void ComboCheck();

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