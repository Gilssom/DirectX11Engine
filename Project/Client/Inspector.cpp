#include "pch.h"
#include "Inspector.h"

#include <Engine\\CLevelManager.h>
#include <Engine\\CLevel.h>
#include <Engine\\CGameObject.h>
#include <Engine\\CTransform.h>

#include "ComponentUI.h"
#include "AssetUI.h"
#include "TransformUI.h"
#include "MeshRenderUI.h"
#include "Animator2DUI.h"
#include "Collider2DUI.h"
#include "CameraUI.h"
#include "Light2DUI.h"
#include "ParticleSystemUI.h"
#include "TileMapUI.h"

Inspector::Inspector()
	: EditorUI("Inspector", "##Inspector")
	, m_TargetObject(nullptr)
	, m_arrComUI{}
{
	CreateComponentUI();

	CreateAssetUI();
}

Inspector::~Inspector()
{
	
}

void Inspector::Render_Tick()
{
	ImGui::Text("Inspector");
}

void Inspector::SetTargetObject(CGameObject* target)
{
	// 만약 Target Asset 이 있다면 대응하는 Asset UI 비활성화
	if (m_TargetAsset != nullptr)
	{
		m_arrAssetUI[(UINT)m_TargetAsset->GetAssetType()]->SetActive(false);
		m_TargetAsset = nullptr;
	}

	m_TargetObject = target;

	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; i++)
	{
		// 해당 컴포넌트를 담당할 UI 가 생성되어있지 않기 때문에 nullptr 체크 해주어야 함.
		if (m_arrComUI[i] == nullptr)
			continue;

		m_arrComUI[i]->SetTarget(m_TargetObject);
	}
}

void Inspector::SetTargetAsset(Ptr<CAsset> asset)
{
	// 모든 Component UI 비활성화
	SetTargetObject(nullptr);

	// Target Asset Setting
	m_TargetAsset = asset;

	// 모든 Asset UI 비활성화
	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; i++)
	{
		if (m_arrAssetUI[i] == nullptr)
			continue;

		m_arrAssetUI[i]->SetActive(false);
	}

	// Target Asset 이 null 이면 종료
	if (m_TargetAsset == nullptr)
		return;

	// Target Asset 에 대응하는 Asset UI 만 활성화 및 Target Setting
	ASSET_TYPE AssetType = m_TargetAsset->GetAssetType();
	m_arrAssetUI[(UINT)AssetType]->SetActive(true);
	m_arrAssetUI[(UINT)AssetType]->SetTarget(m_TargetAsset);
}

void Inspector::CreateComponentUI()
{
	m_arrComUI[(UINT)COMPONENT_TYPE::TRANSFORM] = new TransformUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::MESHRENDER] = new MeshRenderUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::COLLIDER2D] = new Collider2DUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::ANIMATOR2D] = new Animator2DUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::CAMERA] = new CameraUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::LIGHT2D] = new Light2DUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::TILEMAP] = new TileMapUI;
	m_arrComUI[(UINT)COMPONENT_TYPE::PARTICLESYSTEM] = new ParticleSystemUI;

	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; i++)
	{
		if (m_arrComUI[i] == nullptr)
			continue;

		m_arrComUI[i]->SetActive(false);
		m_arrComUI[i]->SetSeperate(true);
		AddChildUI(m_arrComUI[i]);
	}
}

#include "MeshUI.h"
#include "MeshDataUI.h"
#include "MaterialUI.h"
#include "TextureUI.h"
#include "PrefabUI.h"
#include "SoundUI.h"
#include "GraphicShaderUI.h"
#include "ComputeShaderUI.h"

void Inspector::CreateAssetUI()
{
	m_arrAssetUI[(UINT)ASSET_TYPE::MESH] = new MeshUI;
	m_arrAssetUI[(UINT)ASSET_TYPE::MESH_DATA] = new MeshDataUI;
	m_arrAssetUI[(UINT)ASSET_TYPE::MATERIAL] = new MaterialUI;
	m_arrAssetUI[(UINT)ASSET_TYPE::TEXTURE] = new TextureUI;
	m_arrAssetUI[(UINT)ASSET_TYPE::PREFAB] = new PrefabUI;
	m_arrAssetUI[(UINT)ASSET_TYPE::SOUND] = new SoundUI;
	m_arrAssetUI[(UINT)ASSET_TYPE::GRAPHICS_SHADER] = new GraphicShaderUI;
	m_arrAssetUI[(UINT)ASSET_TYPE::COMPUTE_SHADER] = new ComputeShaderUI;

	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; i++)
	{
		if (m_arrAssetUI[i] == nullptr)
			continue;

		m_arrAssetUI[i]->SetActive(false);
		m_arrAssetUI[i]->SetSeperate(true);
		AddChildUI(m_arrAssetUI[i]);
	}
}