#pragma once
#include "CScript.h"

class CCameraMoveScript : public CScript
{
private:
	float m_Speed;


public:
	virtual void Tick() override;

private:
	void MoveByPerspective();
	void MoveByOrthographic();

public:
	CLONE(CCameraMoveScript);

public:
	CCameraMoveScript();
	~CCameraMoveScript();
};

