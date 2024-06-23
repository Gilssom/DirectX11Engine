#include "pch.h"
#include "UIButton.h"

UIButton::UIButton(const string& label, function<void()> onClick)
	: UIElement("Button", L"")
	, m_Label(label)
	, onClick(onClick)
{

}

UIButton::UIButton(Ptr<CTexture> texture, ImVec2 size, function<void()> onClick)
	: UIElement("Button", L"")
	, m_Texture(texture)
	, m_Size(size)
	, onClick(onClick)
{

}

UIButton::~UIButton()
{

}

void UIButton::Render()
{
	if (m_Texture != nullptr)
	{
		if (ImGui::ImageButton(m_Texture.Get(), m_Size))
		{
			onClick();
		}
	}
	else
	{
		if (ImGui::Button(m_Label.c_str()))
		{
			onClick();
		}
	}
}