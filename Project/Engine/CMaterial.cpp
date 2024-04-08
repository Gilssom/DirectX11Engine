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
	// ������ �̿��ؼ�(����) ���ο� ���� ���� (Clone ���� ���)
	Ptr<CMaterial> pDynamicMtrl = Clone();
	pDynamicMtrl->m_bDynamic = true;

	return pDynamicMtrl;
}

void CMaterial::Binding()
{
	// �ؽ�ó ���ε� - ��� �����Ϳ� Texture Binding ���α��� ����
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

	// ��� ������ ���ε�
	if (m_Shader.Get() != nullptr)
		m_Shader->Binding();

	CConstBuffer* pMtrlCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::MATERIAL);
	pMtrlCB->SetData(&m_Const);
	pMtrlCB->Binding();
}