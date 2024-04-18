#include "pch.h"
#include "ListUI.h"

ListUI::ListUI()
	: EditorUI("List", "##List")
    , m_SelectedIdx(-1)
{

}

ListUI::~ListUI()
{

}

void ListUI::Render_Tick()
{
    // �ڽ��� �����ִ� Window â�� ũ�⸦ �˷��ش�. (List UI �� ����ũ��)
    ImVec2 vWinSize = ImGui::GetWindowContentRegionMax();
    vWinSize.y -= 27;
    vWinSize.x -= 8;

    if (ImGui::BeginListBox("##ListBox", vWinSize))
    {
        for (size_t i = 0; i < m_vecList.size(); i++)
        {
            const bool bSelected = (m_SelectedIdx == i);

            if (ImGui::Selectable(m_vecList[i].c_str(), bSelected))
            {
                m_SelectedIdx = i;
            }

            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            {
                // List UI �� ���� ������ ���� ����.
                // ���� ������ ����� �����ϱ� ���� �Լ��� �����ؾ��Ѵ�. (CallBack || Delegate - �Լ� ������ Type)
                if (m_CallBack)
                    m_CallBack();
            }
        }

        ImGui::EndListBox();
    }
}

void ListUI::Deactivate()
{
    m_vecList.clear();
    m_SelectedIdx = -1;
}
