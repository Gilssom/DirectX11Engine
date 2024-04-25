#include "pch.h"
#include "ContentUI.h"

#include <Engine\\CAssetManager.h>

#include "Inspector.h"
#include "TreeUI.h"

ContentUI::ContentUI()
	: EditorUI("Content", "##Content")
{
	// �ڽ� UI �� Tree UI ����
	m_Tree = new TreeUI("Content Tree");
	AddChildUI(m_Tree);

	// Tree UI Root Node ������ �ʰ� ����
	m_Tree->ShowRoot(false);

	// Node �׸��� File Name �� ���̰� ����
	m_Tree->ShowFileNameOnly(true);

	// �׸� ���� �� ������ CallBack or Delegate ���
	m_Tree->RegisterSelectDelegate(this, (UI_DELEGATE1)&ContentUI::SelectAsset);

	// ���� Asset ���µ鿡 ���� Data Tree ����
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
	// ���� Data �������� ������ �� ������ Tree �� ��ü�ϰ� ���ο� Data �� Tree �� �����
	m_Tree->Clear();

	// Dummy Root Node
	TreeNode* pRootNode = m_Tree->AddTreeNode(nullptr, "Dummy Root");

	// Asset Manager �� ���� Asset �� ������ �޾ƿͼ� Tree �� �ݿ�
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
