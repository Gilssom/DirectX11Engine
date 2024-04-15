#pragma once
#include "EditorUI.h"

#include <Engine\\CGameObject.h>

// �߻� Ŭ���� (��� �뵵)
class ComponentUI : public EditorUI
{
private:
	CGameObject*			m_TargetObject;
	const COMPONENT_TYPE	m_Type;

public:
	void SetTarget(CGameObject* target);

public:
	virtual void Render_Tick() = 0;

public:
	ComponentUI(const string& name, const  string& id, COMPONENT_TYPE type);
	~ComponentUI();
};

