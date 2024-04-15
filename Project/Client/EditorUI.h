#pragma once

#include "ImGui\\\imgui.h"

class EditorUI
{
private:
	string				m_Name;			// UI 이름 (겹치지 않게 주의)
	const string		m_ID;		

	EditorUI*			m_ParentUI;		// Editor UI 의 부모 UI 를 가리킴
	vector<EditorUI*>	m_vecChildUI;	// Editor UI 가 소유하고 있는 자식 UI 를 가리킴

	ImVec2				m_vChildSize;	// 자식 UI Size

	bool				m_Active;		// 활성화 - 비활성화 여부

public:
	void SetName(const string& name) { m_Name = name; }
	const string& GetName() { return m_Name; }

	// ImVec2(0, 0) = Parent Default Size
	void SetSize(ImVec2 size) { m_vChildSize = size; }

	void SetActive(bool active) { m_Active = active; }

	EditorUI* GetParentUI() { return m_ParentUI; }
	const vector<EditorUI*> GetChildUI() { return m_vecChildUI; }

	void AddChildUI(EditorUI* child) 
	{ 
		child->m_ParentUI = this;
		m_vecChildUI.push_back(child); 
	}

	// 자신의 타입을 반환
	bool IsRootUI() { return !m_ParentUI; }

public:
	virtual void Tick();
	virtual void Render_Tick() = 0;

public:
	// 상속받아간 곳에선  Name 을 무조건 지정할 수 있게
	EditorUI(const string& name, const  string& id);
	virtual ~EditorUI();
};