#include "pch.h"
#include "CMaterial.h"

#include "CDevice.h"
#include "CConstBuffer.h"

#include "CGraphicShader.h"

CMaterial::CMaterial()
	:CAsset(ASSET_TYPE::MATERIAL)
	, m_bDynamic(false)
{

}

CMaterial::~CMaterial()
{

}

void CMaterial::SetTexParam(TEX_PARAM param, Ptr<CTexture> tex)
{
	m_arrTex[param] = tex;
}

Ptr<CMaterial> CMaterial::GetDynamicMaterial()
{
	// 본인을 이용해서(복사) 새로운 재질 생성
	Ptr<CMaterial> pDynamicMtrl = new CMaterial(*this); 
	pDynamicMtrl->m_bDynamic = true;

	return pDynamicMtrl;
}

void CMaterial::Binding()
{
	// 텍스처 바인딩
	for (UINT i = 0; i < TEX_PARAM::END; i++)
	{
		if (m_arrTex[i] == nullptr)
		{
			CTexture::Clear(i);
			continue;
		}

		m_arrTex[i]->Binding(i);
	}

	// 상수 데이터 바인딩
	if (m_Shader.Get() != nullptr)
		m_Shader->Binding();

	CConstBuffer* pMtrlCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::MATERIAL);
	pMtrlCB->SetData(&m_Const);
	pMtrlCB->Binding();
}