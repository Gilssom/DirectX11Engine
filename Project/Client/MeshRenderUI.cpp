#include "pch.h"
#include "MeshRenderUI.h"

#include <Engine\CAsset.h>
#include <Engine\CMeshRender.h>

#include "CImGuiManager.h"
#include "inspector.h"
#include "ListUI.h"

/*void ChangeBySelectedMesh()
{
	// List UI 를 가져온다.
	ListUI* pListUI = CImGuiManager::GetInst()->FindEditorUI<ListUI>("List");

	// ImGui Manager 에서 Inspector 를 가져온다.
	Inspector* pInspector = CImGuiManager::GetInst()->FindEditorUI<Inspector>("Inspector");

	// List UI 에서 더블클릭이 발생했을 때의 아이템의 문자열을 알아낸다.
	// 문자열을 2Byte 로 전환
	wstring strMeshKey = ToWString(pListUI->GetSelectedString());

	// Asset Manager 에 접근해서 해당 이름의 Mesh 를 찾아낸다.
	Ptr<CMesh> pMesh = CAssetManager::GetInst()->FindAsset<CMesh>(strMeshKey);

	// Inspector 를 통해 Target Object 를 알아내고, Render Component 에 접근, 찾아낸 Mesh 를 적용시킨다.
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

	// ImGuiInputTextFlags_ : ImGui 의 Flag 는 모두 _ 를 붙이고, 조합을 할 수 있다. (비트)
	string strMeshKey;
	if (pMesh != nullptr)
	{
		strMeshKey = string(pMesh->GetKey().begin(), pMesh->GetKey().end());
	}

	ImGui::Text("Mesh      "); ImGui::SameLine();
	ImGui::InputText("##MeshName", (char*)strMeshKey.c_str(), strMeshKey.capacity(), ImGuiInputTextFlags_ReadOnly); ImGui::SameLine();
	if (ImGui::Button("##MeshButton", ImVec2(18, 18)))
	{
		// List UI 활성화
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
		// List UI 활성화
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
