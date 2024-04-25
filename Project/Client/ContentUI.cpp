#include "pch.h"
#include "ContentUI.h"

#include <Engine\\CAssetManager.h>

#include "Inspector.h"
#include "TreeUI.h"

ContentUI::ContentUI()
	: EditorUI("Content", "##Content")
{
	// 자식 UI 로 Tree UI 생성
	m_Tree = new TreeUI("Content Tree");
	AddChildUI(m_Tree);

	// Tree UI Root Node 보이지 않게 설정
	m_Tree->ShowRoot(false);

	// Node 항목의 File Name 만 보이게 설정
	m_Tree->ShowFileNameOnly(true);

	// 항목 선택 시 동작할 CallBack or Delegate 등록
	m_Tree->RegisterSelectDelegate(this, (UI_DELEGATE1)&ContentUI::SelectAsset);

	// 현재 Asset 상태들에 따라 Data Tree 설정
	RenewContent();
}

ContentUI::~ContentUI()
{

}

void ContentUI::Render_Tick()
{

}

void ContentUI::RenewContent()
{
	// 무언가 Data 변경점이 생겼을 때 기존의 Tree 를 해체하고 새로운 Data 로 Tree 를 재생성
	m_Tree->Clear();

	// Dummy Root Node
	TreeNode* pRootNode = m_Tree->AddTreeNode(nullptr, "Dummy Root");

	// Asset Manager 로 부터 Asset 의 정보를 받아와서 Tree 에 반영
	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; i++)
	{
		// Category Setting
		TreeNode* pCategoryNode = m_Tree->AddTreeNode(pRootNode, ASSET_TYPE_STRING[i]);
		pCategoryNode->SetFrame(true);

		const map<wstring, Ptr<CAsset>>& mapAsset = CAssetManager::GetInst()->GetAssets((ASSET_TYPE)i);

		for (const auto& pair : mapAsset)
		{
			m_Tree->AddTreeNode(pCategoryNode, ToString(pair.first).c_str(), (DWORD_PTR)pair.second.Get());
		}
	}
}

UINT ContentUI::SelectAsset(DWORD_PTR data)
{
	TreeNode* pSelectedNode = (TreeNode*)data;

	pSelectedNode->GetName();
	Ptr<CAsset> pAsset = (CAsset*)pSelectedNode->GetData();

	Inspector* pInspector = CImGuiManager::GetInst()->FindEditorUI<Inspector>("Inspector");

	pInspector->SetTargetAsset(pAsset);

	return 0;
}
