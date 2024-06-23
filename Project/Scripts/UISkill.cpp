#include "pch.h"
#include "UISkill.h"

UISkill::UISkill(const string& name, const wstring& texPath, eSkillType skillType)
	: UIElement(name, texPath)
    , m_SkillType(skillType)
{

}

UISkill::~UISkill()
{

}
void UISkill::Render()
{
    ImGui::SetNextWindowBgAlpha(0.f); // ��� �����ϰ� ����
    ImGui::SetNextWindowPos(GetPosition(), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(GetWidth(), GetHeight()), ImGuiCond_Always); // â ũ�� ����
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // â �е��� ����

    ImGui::Begin((GetName() + "UI").c_str(), nullptr
        , ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground);

    ImGui::SetCursorPos(ImVec2(0, 0));
    SkillIcon();
    ImGui::End();
    ImGui::PopStyleVar(); // ��Ÿ�� ������ ���� ���·� ����
}

void UISkill::SkillIcon()
{
    float coolTime = CSkillManager::Instance().GetSkillCoolTime(m_SkillType);

    ImGuiIO& io = ImGui::GetIO();
    ImFont* customFont = io.Fonts->Fonts[1];

    // ���� ��Ÿ�� ���̸�
    if (!CSkillManager::Instance().SkillCoolTime(m_SkillType))
    {
        ImVec4 color = ImGui::GetStyle().Colors[ImGuiCol_TextDisabled];
        ImGui::Image(GetTexID(), ImVec2(GetWidth(), GetHeight()), ImVec2(0, 0), ImVec2(1, 1), color);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 30);

        ImGui::PushFont(customFont);
        ImGui::Text("%.0f", coolTime);
        ImGui::PopFont();
    }
    // �ƴ϶��
    else
    {
        ImGui::Image(GetTexID(), ImVec2(GetWidth(), GetHeight()));
    }
}