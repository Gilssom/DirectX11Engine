#pragma once

#include "ImGui\\\imgui.h"

class EditorUI
{
private:
	string				m_Name;			// UI �̸� (��ġ�� �ʰ� ����)
	const string		m_ID;		

	EditorUI*			m_ParentUI;		// Editor UI �� �θ� UI �� ����Ŵ
	vector<EditorUI*>	m_vecChildUI;	// Editor UI �� �����ϰ� �ִ� �ڽ� UI �� ����Ŵ

	ImVec2				m_vChildSize;	// �ڽ� UI Size

	bool				m_Active;		// Ȱ��ȭ - ��Ȱ��ȭ ����

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

	// �ڽ��� Ÿ���� ��ȯ
	bool IsRootUI() { return !m_ParentUI; }

public:
	virtual void Tick();
	virtual void Render_Tick() = 0;

public:
	// ��ӹ޾ư� ������  Name �� ������ ������ �� �ְ�
	EditorUI(const string& name, const  string& id);
	virtual ~EditorUI();
};