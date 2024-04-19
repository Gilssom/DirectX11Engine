#pragma once
#include "EditorUI.h"

class CGameObject;
class ComponentUI;

class Inspector : public EditorUI
{
private:
	CGameObject*	m_TargetObject;

	// 자식으로 넣기만 하지 말고 포인터를 편리하게 하나 더 들고 있자. (다형성)
	ComponentUI*	m_arrComUI[(UINT)COMPONENT_TYPE::END];

public:
	virtual void Render_Tick() override;

public:
	void SetTargetObject(CGameObject* target);
	CGameObject* GetTargetObject() { return m_TargetObject; }

private:
	void CreateComponentUI();

public:
	Inspector();
	~Inspector();
};