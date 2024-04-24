#pragma once
#include "EditorUI.h"

class TreeUI;
class TreeNode;

class OutlinerUI : public EditorUI
{
private:
	TreeUI* m_Tree;


public:
	void RenewGameObject();


public:
	virtual void Render_Tick() override;


private:
	void AddGameObject(TreeNode* node, CGameObject* object);


public:
	OutlinerUI();
	~OutlinerUI();
};

