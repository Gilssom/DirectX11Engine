#include "pch.h"
#include "Animator2DUI.h"

Animator2DUI::Animator2DUI()
	: ComponentUI("Animator2D", "##Animator2DUI", COMPONENT_TYPE::ANIMATOR2D)
{
	SIZE;
}

Animator2DUI::~Animator2DUI()
{
}

void Animator2DUI::Render_Tick()
{
	Render_Title();
}