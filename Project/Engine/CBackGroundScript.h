#pragma once
#include "CScript.h"

class CBackGroundScript : public CScript
{
private:
	float m_Intence;


public:
	virtual void Tick() override;


public:
	CBackGroundScript();
	~CBackGroundScript();
};

