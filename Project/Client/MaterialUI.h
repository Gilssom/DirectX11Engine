#pragma once
#include "AssetUI.h"

class MaterialUI : public AssetUI
{
private:
	UINT	m_ParamDescMaxWidth;

public:
	virtual void Render_Tick() override;
	virtual void TargetChanged() override;

public:
	MaterialUI();
	~MaterialUI();
};

