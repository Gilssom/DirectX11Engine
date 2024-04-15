#pragma once

#include  "ImGui\\\imgui.h"

class EditorUI
{
private:
	string			m_Name;		// UI �̸� (��ġ�� �ʰ� ����)
	const string	m_ID;		

public:
	void SetName(const string& name) { m_Name = name; }
	const string& GetName() { return m_Name; }

public:
	virtual void Tick();
	virtual void Render_Tick() = 0;

public:
	// ��ӹ޾ư� ������  Name �� ������ ������ �� �ְ�
	EditorUI(const string& name, const  string& id);
	virtual ~EditorUI();
};