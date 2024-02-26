#pragma once
#include "CComponent.h"

class CCollider2D : public CComponent
{
private:
	Vec3	m_Offset;	// Offset 위치
	Vec3	m_FinalPos; // 충돌체의 최종 위치 ( Object Position + Collider Offset )

	Vec3	m_Scale;	// Object 상대적인 배율
	Vec3	m_Rotation; // Object 상대적인 회전 (자전)

	bool	m_Absolute;	// true 인 경우, Object 크기에 영향 받지 않는 절대 크기 (고정)

	Matrix	m_matColWorld;

public:
	void SetOffset(Vec3 offset) { m_Offset = offset; }
	void SetScale(Vec3 scale) { m_Scale = scale; }
	void SetRotationZ(float angle) { m_Rotation.z = angle; }

	Vec3 GetOffset() { return m_Offset; }
	Vec3 GetScale() { return m_Scale; }
	Vec3 GetFinalPos() { return m_FinalPos; }
	float GetRotationZ() { return m_Rotation.z; }

	void SetAbsolute(bool abs) { m_Absolute = abs; }
	bool IsAbsolute() { return m_Absolute; }


public:
	virtual void FinalTick() override;

public:
	void BeginOverlap(CCollider2D* otherCollider);
	void Overlap(CCollider2D* otherCollider);
	void EndOverlap(CCollider2D* otherCollider);

public:
	CCollider2D();
	~CCollider2D();
};

