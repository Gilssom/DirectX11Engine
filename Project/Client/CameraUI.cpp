#include "pch.h"
#include "CameraUI.h"

CameraUI::CameraUI()
	: ComponentUI("Camera", "##CameraUI", COMPONENT_TYPE::CAMERA)
{
	SetSize(ImVec2(0, 200));
}

CameraUI::~CameraUI()
{
}

void CameraUI::Render_Tick()
{
	Render_Title();
}