#include "pch.h"
#include "Light2DUI.h"

Light2DUI::Light2DUI()
	: ComponentUI("Light2D", "##Light2DUI", COMPONENT_TYPE::LIGHT2D)
{
	SetSize(ImVec2(0, 200));
}

Light2DUI::~Light2DUI()
{
}

void Light2DUI::Render_Tick()
{
	Render_Title();
}