#pragma once
#include "EditorUI.h"

class TreeUI;

class ContentUI : public EditorUI
{
private:
	TreeUI*		m_Tree;


public:
	void RenewContent();


public:
	virtual void Render_Tick() override;


public:
	ContentUI();
	~ContentUI();
};

