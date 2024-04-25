#pragma once
#include "EditorUI.h"

class TreeUI;

class ContentUI : public EditorUI
{
private:
	TreeUI*		m_Tree;


public:
	void RenewContent();


private:
	UINT SelectAsset(DWORD_PTR data);


public:
	virtual void Render_Tick() override;


public:
	ContentUI();
	~ContentUI();
};

