#pragma once
#include "EditorUI.h"

class CGameObject;

class Inspector : public EditorUI
{
private:
	CGameObject* m_TargetObject;

public:
	virtual void Render_Tick() override;

public:
	void SetTargetObject(CGameObject* target);

public:
	Inspector();
	~Inspector();
};