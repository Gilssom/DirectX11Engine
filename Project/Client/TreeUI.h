#pragma once
#include "EditorUI.h"

class TreeNode
{
private:
	TreeNode*			m_ParentNode;
	vector<TreeNode*>	m_vecChildNode;
	string				m_Name;

	DWORD_PTR			m_Data;

	bool				m_bFrame;

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
		: m_ParentNode(nullptr)
		, m_Data(0)
	{}
	TreeNode(const string& name, DWORD_PTR data)
		: m_ParentNode(nullptr)
		, m_Name(name)
		, m_Data(data)
	{}
	~TreeNode();
};

// 동적인 Data 를 Tree 구조로 나타내기 위한 구조 설계
class TreeUI : public EditorUI
{
private:
	TreeNode*	m_RootNode;		// 최상위 Root Node
	bool		m_bShowRoot;	// Root Node 를 보여줄지 안보여줄지


public:
	void ShowRoot(bool show) { m_bShowRoot = show; }
	TreeNode* AddTreeNode(TreeNode* parent, const string& nodeName, DWORD_PTR dwData = 0);


public:
	virtual void Render_Tick() override;


public:
	TreeUI();
	~TreeUI();
};

