#pragma once
#include "ComponentUI.h"

class CameraUI : public ComponentUI
{
private:

public:
	virtual void Render_Tick() override;

public:
	CameraUI();
	~CameraUI();
};

