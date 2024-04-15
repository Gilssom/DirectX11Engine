#pragma once
#include "ComponentUI.h"

class MeshRenderUI : public ComponentUI
{
private:

public:
	virtual void Render_Tick() override;

public:
	MeshRenderUI();
	~MeshRenderUI();
};

