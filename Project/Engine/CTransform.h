#pragma once
#include "CComponent.h"
class CTransform : public CComponent
{
private:
	Vec3	m_RelativePos;
	Vec3	m_RelativeScale;
	Vec3	m_RelativeRotation;
	Matrix	m_matWorld;

public:
	virtual void FinalTick() override;
	void Binding();


public:
	Vec3 GetRelativePos() { return m_RelativePos; }
	Vec3 GetRelativeScale() { return m_RelativeScale; }
	Vec3 GetRelativeRotation() { return m_RelativeRotation; }

	void SetRelativePos(const Vec3& vPos) { m_RelativePos = vPos; }
	void SetRelativeScale(const Vec3& vScale) { m_RelativeScale = vScale; }
	void SetRelativeRotation(const Vec3& vRotation) { m_RelativeRotation = vRotation; }

	void SetRelativePos(float x, float y, float z) { m_RelativePos = Vec3(x, y, z); }
	void SetRelativeScale(float x, float y, float z) { m_RelativeScale = Vec3(x, y, z); }
	void SetRelativeRotation(float x, float y, float z) { m_RelativeRotation = Vec3(x, y, z); }

public:
	CTransform();
	~CTransform();
};

