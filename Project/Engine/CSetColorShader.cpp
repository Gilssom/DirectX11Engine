#include "pch.h"
#include "CSetColorShader.h"

CSetColorShader::CSetColorShader()
	: CComputeShader(32, 32, 1) // Thread 개수 지정 필수로 강제화
{

}

CSetColorShader::~CSetColorShader()
{

}

int CSetColorShader::Binding()
{
	if (m_TargetTex == nullptr || m_TargetTex->GetUAV() == nullptr)
		return E_FAIL;

	m_TargetTex->Binding_CS_UAV(0);

	return S_OK;
}

void CSetColorShader::CalculateGroupNum()
{
	m_GroupX = (UINT)m_TargetTex->GetWidth() / m_ThreadPerGroupX;
	m_GroupY = (UINT)m_TargetTex->GetHeight() / m_ThreadPerGroupY;
	m_GroupZ = 1;
}

void CSetColorShader::Clear()
{
	m_TargetTex->Clear_CS_UAV(0);
}