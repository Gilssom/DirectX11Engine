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

void* CMaterial::GetScalarParam(SCALAR_PARAM param)
{
	switch (param)
	{
	case INT_0:
	case INT_1:
	case INT_2:
	case INT_3:
		return &m_Const.iArr[param];
		break;
	case FLOAT_0:
	case FLOAT_1:
	case FLOAT_2:
	case FLOAT_3:
		return &m_Const.fArr[param - FLOAT_0];
		break;
	case VEC2_0:
	case VEC2_1:
	case VEC2_2:
	case VEC2_3:
		return &m_Const.v2Arr[param - VEC2_0];
		break;
	case VEC4_0:
	case VEC4_1:
	case VEC4_2:
	case VEC4_3:
		return &m_Const.v4Arr[param - VEC4_0];
		break;
	case MAT_0:
	case MAT_1:
	case MAT_2:
	case MAT_3:
		return &m_Const.matArr[param - MAT_0];
		break;
	}

	return nullptr;
}

Ptr<CMaterial> CMaterial::GetDynamicMaterial()
{
	// 본인을 이용해서(복사) 새로운 재질 생성 (Clone 복제 사용)
	Ptr<CMaterial> pDynamicMtrl = Clone();
	pDynamicMtrl->m_bDynamic = true;

	return pDynamicMtrl;
}

void CMaterial::Binding()
{
	// 텍스처 바인딩 - 상수 데이터에 Texture Binding 여부까지 포함
	for (UINT i = 0; i < TEX_PARAM::END; i++)
	{
		if (m_arrTex[i] == nullptr)
		{
			CTexture::Clear(i);
			m_Const.btex[i] = false;
			continue;
		}

		m_arrTex[i]->Binding(i);
		m_Const.btex[i] = true;
	}

	// 상수 데이터 바인딩
	if (m_Shader.Get() != nullptr)
		m_Shader->Binding();

	CConstBuffer* pMtrlCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::MATERIAL);
	pMtrlCB->SetData(&m_Const);
	pMtrlCB->Binding();
}