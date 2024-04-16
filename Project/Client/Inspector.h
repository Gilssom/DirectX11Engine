#pragma once
#include "EditorUI.h"

class CGameObject;
class ComponentUI;

class Inspector : public EditorUI
{
private:
	CGameObject*	m_TargetObject;

	// �ڽ����� �ֱ⸸ ���� ���� �����͸� ���ϰ� �ϳ� �� ��� ����. (������)
	ComponentUI*	m_arrComUI[(UINT)COMPONENT_TYPE::END];

public:
	virtual void Render_Tick() override;

public:
	void SetTargetObject(CGameObject* target);

private:
	void CreateComponentUI();

public:
	Inspector();
	~Inspector();
};