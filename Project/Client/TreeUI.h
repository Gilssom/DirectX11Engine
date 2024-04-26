#pragma once
#include "EditorUI.h"

class TreeUI;

class TreeNode
{
private:
	TreeUI*				m_Owner;
	TreeNode*			m_ParentNode;
	vector<TreeNode*>	m_vecChildNode;
	string				m_Name;

	DWORD_PTR			m_Data;

	bool				m_bFrame;
	bool				m_bSelected;

public:
	void SetName(const string& name) { m_Name = name; }
	void SetData(DWORD_PTR data) { m_Data = data; }
	void SetFrame(bool frame) { m_bFrame = frame; }
	void AddChildNode(TreeNode* child)
	{
		m_vecChildNode.push_back(child);
		child->m_ParentNode = this;
	}

	const string& GetName() { return m_Name; }
	DWORD_PTR GetData() { return m_Data; }
	const vector<TreeNode*>& GetChildNode() { return m_vecChildNode; }

public:
	void Render_Tick();

public:
	TreeNode()
		: m_Owner(nullptr)
		, m_ParentNode(nullptr)
		, m_Data(0)
		, m_bFrame(false)
		, m_bSelected(false)
	{}
	TreeNode(const string& name, DWORD_PTR data)
		: m_Owner(nullptr)
		, m_ParentNode(nullptr)
		, m_Name(name)
		, m_Data(data)
		, m_bFrame(false)
		, m_bSelected(false)
	{}
	~TreeNode();

	friend class TreeUI;
};

// ������ Data �� Tree ������ ��Ÿ���� ���� ���� ����
class TreeUI : public EditorUI
{
private:
	TreeNode*		m_RootNode;			// �ֻ��� Root Node
	TreeNode*		m_SelectedNode;		// ���õ� Node

	bool			m_bShowRoot;		// Root Node �� �������� �Ⱥ�������
	bool			m_bShowFileName;	// File �̸��� �������� �Ⱥ�������
	bool			m_bUseDrag;			// Drag
	bool			m_bUseDrop;			// Drop

	UI_CALLBACK		m_SelectedCallBack;

	EditorUI*		m_SelectedInst;
	UI_DELEGATE1	m_SelectedDelegate;


public:
	void ShowRoot(bool show) { m_bShowRoot = show; }
	void ShowFileNameOnly(bool showFileName) { m_bShowFileName = showFileName; }

	void UseDrag(bool drag) { m_bUseDrag = drag; }
	void UseDrop(bool drop) { m_bUseDrop = drop; }

	TreeNode* AddTreeNode(TreeNode* parent, const string& nodeName, DWORD_PTR dwData = 0);

	void RegisterSelectCallBack(UI_CALLBACK callBack) { m_SelectedCallBack = callBack; }
	void RegisterSelectDelegate(EditorUI* inst, UI_DELEGATE1 func) { m_SelectedInst = inst; m_SelectedDelegate = func; }

	void Clear() { if (m_RootNode != nullptr) { delete m_RootNode; m_RootNode = nullptr; }}


private:
	void SetSelectedNode(TreeNode* node);


public:
	virtual void Render_Tick() override;


public:
	TreeUI(const string& name);
	~TreeUI();

	friend class TreeNode;
};

