#pragma once
#include <Engine\\CScript.h>

class CCameraMoveScript : public CScript
{
private:
	CGameObject*	m_TargetObject;
	float			m_Speed;

	bool			m_IsShaking;
	float			m_ShakeDuration;
	float			m_ShakeTimer;
	float			m_ShakeMagnitude;

public:
	virtual void Tick() override;

private:
	void MoveByPerspective();
	void MoveByOrthographic();

public:
	void SetTargetObject(CGameObject* targetObject) { m_TargetObject = targetObject; }

	void StartShake(float duration, float magnitude);
	void UpdateShake();

public:
	CLONE(CCameraMoveScript);

public:
	CCameraMoveScript();
	~CCameraMoveScript();
};

