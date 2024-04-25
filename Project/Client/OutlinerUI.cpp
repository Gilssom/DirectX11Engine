#include "pch.h"
#include "OutlinerUI.h"

#include <Engine\\CLevelManager.h>
#include <Engine\\CLevel.h>
#include <Engine\\CLayer.h>
#include <Engine\\CGameObject.h>
#include <Engine\\CTaskManager.h>

#include "Inspector.h"
#include "TreeUI.h"

OutlinerUI::OutlinerUI()
	: EditorUI("Outliner", "##Outliner")
{
	// 자식 UI 로 Tree UI 생성
	m_Tree = new TreeUI("Outliner Tree");
	AddChildUI(m_Tree);

	// Tree UI Root Node 보이지 않게 설정
	m_Tree->ShowRoot(false);

	// 항목 선택 시 동작할 CallBack or Delegate 등록
	m_Tree->RegisterSelectDelegate(this, (UI_DELEGATE1)&OutlinerUI::SelectGameObject);

	// 현재 Asset 상태들에 따라 Data Tree 설정
	RenewGameObject();
}

OutlinerUI::~OutlinerUI()
{

}

void OutlinerUI::Render_Tick()
{
	if (CTaskManager::GetInst()->IsObjectsChanged())
	{
		RenewGameObject();
	}
}

void OutlinerUI::RenewGameObject()
{
	// Tree Clear
	m_Tree->Clear();
	TreeNode* pRootNode = m_Tree->AddTreeNode(nullptr, "Dummy Root");

	// 현재 Level 을 알아낸다.
	CLevel* pCurLevel = CLevelManager::GetInst()->GetCurrentLevel();

	if (pCurLevel == nullptr)
		return;

	for (UINT i = 0; i < MAX_LAYER; i++)
	{
		CLayer* pLayer = pCurLevel->GetLayer(i);

		const vector<CGameObject*>& vecParent = pLayer->GetParentObjects();

		for (size_t j = 0; j < vecParent.size(); j++)
		{
			AddGameObject(pRootNode, vecParent[j]);
		}
	}
}

void OutlinerUI::AddGameObject(TreeNode* node, CGameObject* object)
{
	TreeNode* pNewNode = m_Tree->AddTreeNode(node, ToString(object->GetName()), (DWORD_PTR)object);

	// 만약 해당 Object 가 자식 Object 를 보유하고 있다면
	const vector<CGameObject*>& vecChildren = object->GetChildren();

	// 자식 Object 를 부모 Object 의 정보로 만들어진 노드 미틍로 다시 추가 (재귀 형식)
	for (size_t i = 0; i < vecChildren.size(); i++)
	{
		AddGameObject(pNewNode, vecChildren[i]);
	}
}

UINT OutlinerUI::SelectGameObject(DWORD_PTR data)
{
	TreeNode* pSelectedNode = (TreeNode*)data;

	pSelectedNode->GetName();
	CGameObject* pSelectObject = (CGameObject*)pSelectedNode->GetData();

	Inspector* pInspector = CImGuiManager::GetInst()->FindEditorUI<Inspector>("Inspector");

	pInspector->SetTargetObject(pSelectObject);

	return 0;
}
