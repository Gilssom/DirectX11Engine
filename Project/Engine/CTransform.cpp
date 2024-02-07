#include "pch.h"
#include "CTransform.h"

#include "CDevice.h"
#include "CConstBuffer.h"

CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
	, m_RelativeScale(Vec3(1.f, 1.f, 1.f))
{

}

CTransform::~CTransform()
{

}

void CTransform::FinalTick()
{
	
}

void CTransform::Binding()
{
	// 데이터 GPU 로 보내기
	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);

	tTransform trans = {};
	trans.Position = m_RelativePos;
	trans.Scale = m_RelativeScale;

	pCB->SetData(&trans);
	pCB->Binding();
}
