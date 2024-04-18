#pragma once
#include "EditorUI.h"

class ListUI : public EditorUI
{
private:
	vector<string>	m_vecList;
	int				m_SelectedIdx;

	// ��ȯ Ÿ���� void, ���ڵ� void �� �Լ� ������
	UI_CALLBACK		m_CallBack;
	// ��ȯ Ÿ���� UINT, EditorUI �����̿��� �ϸ�, ���ڴ� ���� �Լ� ������
	UI_DELEGATE		m_Delegate;
	// ���ϴ� �Լ��� ����� ���ְڴ� ��� ����

public:
	void AddItem(const string& item) { m_vecList.push_back(item); }
	void AddItem(const vector<string>& vecItem) { m_vecList.insert(m_vecList.end(), vecItem.begin(), vecItem.end()); }

	void SetCallBack(UI_CALLBACK callBack) { m_CallBack = callBack; }

public:
	virtual void Render_Tick() override;
	virtual void Deactivate() override;

public:
	ListUI();
	~ListUI();
};

