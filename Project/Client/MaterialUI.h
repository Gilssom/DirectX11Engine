#pragma once
#include "AssetUI.h"

class MaterialUI : public AssetUI
{
private:


public:
	virtual void Render_Tick() override;

public:
	MaterialUI();
	~MaterialUI();
};

