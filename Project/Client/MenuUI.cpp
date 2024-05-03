#include "pch.h"
#include "MenuUI.h"

#include <Engine\\CEngine.h>

#include <Engine\\CLevelManager.h>
#include <Engine\\CLevel.h>
#include <Engine\\CLayer.h>
#include <Engine\\CGameObject.h>
#include <Engine\\components.h>

#include <Engine\\CPathManager.h>

#include "CImGuiManager.h"
#include "Inspector.h"
#include "ContentUI.h"

MenuUI::MenuUI()
	: EditorUI("Menu", "##Menu")
{

}

MenuUI::~MenuUI()
{

}

void MenuUI::Tick()
{
	if (ImGui::BeginMainMenuBar())
	{
		File();

		Level();

		GameObject();

        Asset();

		ImGui::EndMainMenuBar();
	}
}

void MenuUI::Render_Tick() { }

void MenuUI::File()
{
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("Exit", "Alt+F4"))
        {
            DestroyWindow(CEngine::GetInst()->GetMainWnd());
        }

        ImGui::EndMenu();
    }
}

void MenuUI::Level()
{
    if (ImGui::BeginMenu("Level"))
    {
        if (ImGui::MenuItem("Save Level"))
        {

        }

        if (ImGui::MenuItem("Load Level"))
        {

        }

        ImGui::Separator();

        if (ImGui::MenuItem("Play"))
        {

        }

        if (ImGui::MenuItem("Pause"))
        {

        }

        if (ImGui::MenuItem("Stop"))
        {

        }

        ImGui::EndMenu();
    }
}

void MenuUI::GameObject()
{
    if (ImGui::BeginMenu("GameObject"))
    {
        if (ImGui::MenuItem("Create EmptyObject"))
        {
            CGameObject* pNewObj = new CGameObject;
            pNewObj->AddComponent(new CTransform);
            pNewObj->SetName(L"Empty GameObject");
            SpawnObject(0, pNewObj);

            Inspector* pInspector = CImGuiManager::GetInst()->FindEditorUI<Inspector>("Inspector");
            pInspector->SetTargetObject(pNewObj);
        }

        if (ImGui::MenuItem("Register As Prefab"))
        {

        }

        if (ImGui::BeginMenu("Add Component"))
        {
            Inspector* pInspector = CImGuiManager::GetInst()->FindEditorUI<Inspector>("Inspector");
            CGameObject* pTargetObj = pInspector->GetTargetObject();

            for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
            {
                if (ImGui::MenuItem(COMPONENT_TYPE_STRING[i]))
                {
                    if (nullptr != pTargetObj)
                    {
                        switch (COMPONENT_TYPE(i))
                        {
                        case COMPONENT_TYPE::TRANSFORM:
                            pTargetObj->AddComponent(new CTransform);
                            break;
                        case COMPONENT_TYPE::CAMERA:
                            pTargetObj->AddComponent(new CCamera);
                            break;
                        case COMPONENT_TYPE::COLLIDER2D:
                            pTargetObj->AddComponent(new CCollider2D);
                            break;
                        case COMPONENT_TYPE::COLLIDER3D:

                            break;
                        case COMPONENT_TYPE::ANIMATOR2D:
                            pTargetObj->AddComponent(new CAnimator2D);
                            break;
                        case COMPONENT_TYPE::ANIMATOR3D:

                            break;
                        case COMPONENT_TYPE::LIGHT2D:
                            pTargetObj->AddComponent(new CLight2D);
                            break;
                        case COMPONENT_TYPE::LIGHT3D:
                            break;
                        case COMPONENT_TYPE::MESHRENDER:
                            pTargetObj->AddComponent(new CMeshRender);
                            break;
                        case COMPONENT_TYPE::DECAL:
                            break;
                        case COMPONENT_TYPE::PARTICLESYSTEM:
                            pTargetObj->AddComponent(new CParticleSystem);
                            break;
                        case COMPONENT_TYPE::TILEMAP:
                            pTargetObj->AddComponent(new CTileMap);
                            break;
                        case COMPONENT_TYPE::LANDSCAPE:
                            break;
                        }
                    }
                }
            }
            pInspector->SetTargetObject(pTargetObj);

            ImGui::EndMenu();

        }

        ImGui::EndMenu();
    }
}

void MenuUI::Asset()
{
    if (ImGui::BeginMenu("Asset"))
    {
        if (ImGui::MenuItem("Create Empty Material"))
        {
            // Material 생성 -> Asset Manager 등록
            Ptr<CMaterial> pMaterial = new CMaterial;

            wstring strMaterialKey = GetAssetDefaultName(L"material\\Default Material");
            strMaterialKey += L".mtrl";
            CAssetManager::GetInst()->AddAsset<CMaterial>(strMaterialKey, pMaterial);

            // Material 파일 저장
            wstring strFilePath = CPathManager::GetInst()->GetContentPath();
            strFilePath += strMaterialKey;
            pMaterial->Save(strFilePath);

            // 새로운 Asset 이 등록되었기 때문에, ContentUI 갱신
            ContentUI* pContent = CImGuiManager::GetInst()->FindEditorUI<ContentUI>("Content");
            pContent->RenewContent();
        }

        ImGui::Separator();

        ImGui::EndMenu();
    }
}

wstring MenuUI::GetAssetDefaultName(wstring baseName)
{
    baseName += L" %d";

    wchar_t szKey[255] = {};

    int i = 0;
    while (true)
    {
        wcscpy_s(szKey, 255, baseName.c_str());
        swprintf_s(szKey, 255, szKey, i++);

        if (CAssetManager::GetInst()->FindAsset<CMaterial>(szKey) == nullptr)
            break;
    }

    return wstring();
}
