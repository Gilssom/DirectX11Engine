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
	// �ڽ� UI �� Tree UI ����
	m_Tree = new TreeUI("Outliner Tree");
	AddChildUI(m_Tree);

	// Tree UI Root Node ������ �ʰ� ����
	m_Tree->ShowRoot(false);

	// �׸� ���� �� ������ CallBack or Delegate ���
	m_Tree->RegisterSelectDelegate(this, (UI_DELEGATE1)&OutlinerUI::SelectGameObject);

	// ���� Asset ���µ鿡 ���� Data Tree ����
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

	// ���� Level �� �˾Ƴ���.
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

	// ���� �ش� Object �� �ڽ� Object �� �����ϰ� �ִٸ�
	const vector<CGameObject*>& vecChildren = object->GetChildren();

	// �ڽ� Object �� �θ� Object �� ������ ������� ��� �̺v�� �ٽ� �߰� (��� ����)
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
