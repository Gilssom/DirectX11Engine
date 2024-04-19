#include "pch.h"
#include "MeshRenderUI.h"

#include <Engine\CAsset.h>
#include <Engine\CMeshRender.h>

#include "CImGuiManager.h"
#include "inspector.h"
#include "ListUI.h"

/*void ChangeBySelectedMesh()
{
	// List UI �� �����´�.
	ListUI* pListUI = CImGuiManager::GetInst()->FindEditorUI<ListUI>("List");

	// ImGui Manager ���� Inspector �� �����´�.
	Inspector* pInspector = CImGuiManager::GetInst()->FindEditorUI<Inspector>("Inspector");

	// List UI ���� ����Ŭ���� �߻����� ���� �������� ���ڿ��� �˾Ƴ���.
	// ���ڿ��� 2Byte �� ��ȯ
	wstring strMeshKey = ToWString(pListUI->GetSelectedString());

	// Asset Manager �� �����ؼ� �ش� �̸��� Mesh �� ã�Ƴ���.
	Ptr<CMesh> pMesh = CAssetManager::GetInst()->FindAsset<CMesh>(strMeshKey);

	// Inspector �� ���� Target Object �� �˾Ƴ���, Render Component �� ����, ã�Ƴ� Mesh �� �����Ų��.
	CGameObject* pTargetObject = pInspector->GetTargetObject();

	assert(pTargetObject != nullptr && pMesh != nullptr);

	pTargetObject->GetRenderComponent()->SetMesh(pMesh);

	pInspector->SetFocus();
}*/

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
			pListUI->SetModal(true);
			pListUI->SetActive(true);
			pListUI->SetFocus();

			vector<string> vecNames;
			CAssetManager::GetInst()->GetAssetNames(ASSET_TYPE::MESH, vecNames);
			pListUI->AddItem(vecNames);
			pListUI->RegisterDoubleClickDelegate(this, (UI_DELEGATE1)&MeshRenderUI::SelectMesh);
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
			pListUI->SetModal(true);
			pListUI->SetActive(true);
			pListUI->SetFocus();

			vector<string> vecNames;
			CAssetManager::GetInst()->GetAssetNames(ASSET_TYPE::MATERIAL, vecNames);
			pListUI->AddItem(vecNames);
			pListUI->RegisterDoubleClickDelegate(this, (UI_DELEGATE1)&MeshRenderUI::SelectMaterial);
		}
	}
}

UINT MeshRenderUI::SelectMesh(DWORD_PTR selected)
{
	string* pStr = (string*)selected;

	wstring strMeshKey = ToWString(*pStr);

	Ptr<CMesh> pMesh = CAssetManager::GetInst()->FindAsset<CMesh>(strMeshKey);

	assert(GetTarget() != nullptr && pMesh != nullptr);

	GetTarget()->GetRenderComponent()->SetMesh(pMesh);

	SetFocus();

	return 0;
}

UINT MeshRenderUI::SelectMaterial(DWORD_PTR selected)
{
	string* pStr = (string*)selected;

	wstring strMaterialKey = ToWString(*pStr);

	Ptr<CMaterial> pMaterial = CAssetManager::GetInst()->FindAsset<CMaterial>(strMaterialKey);

	assert(GetTarget() != nullptr && pMaterial != nullptr);

	GetTarget()->GetRenderComponent()->SetMaterial(pMaterial);

	SetFocus();

	return 0;
}
