#include "pch.h"
#include "MeshRenderUI.h"

#include <Engine\CAsset.h>
#include <Engine\CMeshRender.h>

#include "CImGuiManager.h"
#include "ListUI.h"

void Test()
{
	int a = 0;
}

MeshRenderUI::MeshRenderUI()
	: ComponentUI("MeshRender", "##MeshRenderUI", COMPONENT_TYPE::MESHRENDER)
{
	SetSize(ImVec2(0, 200));
}

MeshRenderUI::~MeshRenderUI()
{
}

void MeshRenderUI::Render_Tick()
{
	Render_Title();

	CMeshRender* pMeshRender = GetTarget()->MeshRender();
	Ptr<CMesh> pMesh = pMeshRender->GetMesh();
	Ptr<CMaterial> pMaterial = pMeshRender->GetMaterial();

	// ImGuiInputTextFlags_ : ImGui �� Flag �� ��� _ �� ���̰�, ������ �� �� �ִ�. (��Ʈ)
	string strMeshKey;
	if (pMesh != nullptr)
	{
		strMeshKey = string(pMesh->GetKey().begin(), pMesh->GetKey().end());
	}

	ImGui::Text("Mesh      "); ImGui::SameLine();
	ImGui::InputText("##MeshName", (char*)strMeshKey.c_str(), strMeshKey.capacity(), ImGuiInputTextFlags_ReadOnly); ImGui::SameLine();
	if (ImGui::Button("##MeshButton", ImVec2(18, 18)))
	{
		// List UI Ȱ��ȭ
		ListUI* pListUI = CImGuiManager::GetInst()->FindEditorUI<ListUI>("List");

		if (pListUI != nullptr && !pListUI->IsActive())
		{
			pListUI->SetActive(true);
			pListUI->SetFocus();

			vector<string> vecNames;
			CAssetManager::GetInst()->GetAssetNames(ASSET_TYPE::MESH, vecNames);
			pListUI->AddItem(vecNames);
			pListUI->SetCallBack(&Test);
		}
	}

	string strMaterialKey;
	if (pMaterial != nullptr)
	{
		strMaterialKey = string(pMaterial->GetKey().begin(), pMaterial->GetKey().end());
	}

	ImGui::Text("Material  "); ImGui::SameLine();
	ImGui::InputText("##MaterialName", (char*)strMaterialKey.c_str(), strMaterialKey.capacity(), ImGuiInputTextFlags_ReadOnly); ImGui::SameLine();
	if (ImGui::Button("##MaterialButton", ImVec2(18, 18)))
	{
		// List UI Ȱ��ȭ
		ListUI* pListUI = CImGuiManager::GetInst()->FindEditorUI<ListUI>("List");

		if (pListUI != nullptr && !pListUI->IsActive())
		{
			pListUI->SetActive(true);
			pListUI->SetFocus();

			vector<string> vecNames;
			CAssetManager::GetInst()->GetAssetNames(ASSET_TYPE::MATERIAL, vecNames);
			pListUI->AddItem(vecNames);
			pListUI->SetCallBack(&Test);
		}
	}
}