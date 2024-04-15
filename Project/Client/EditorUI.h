#pragma once

#include  "ImGui\\\imgui.h"

class EditorUI
{
private:
	string			m_Name;		// UI 이름 (겹치지 않게 주의)
	const string	m_ID;		

public:
	void SetName(const string& name) { m_Name = name; }
	const string& GetName() { return m_Name; }

public:
	virtual void Tick();
	virtual void Render_Tick() = 0;

public:
	// 상속받아간 곳에선  Name 을 무조건 지정할 수 있게
	EditorUI(const string& name, const  string& id);
	virtual ~EditorUI();
};