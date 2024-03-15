#include "pch.h"
#include "CComputeShader.h"

#include "CDevice.h"

CComputeShader::CComputeShader()
	: CShader(ASSET_TYPE::COMPUTE_SHADER)
{

}

CComputeShader::~CComputeShader()
{

}

int CComputeShader::CreateComputeShader(const wstring& strFilePath, const string& csFuncName)
{
	// Compute Shader
	if (FAILED(D3DCompileFromFile(strFilePath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, csFuncName.c_str(), "cs_5_0", D3DCOMPILE_DEBUG, 0
		, m_CSBlob.GetAddressOf()
		, m_ErrBlob.GetAddressOf())))
	{
		if (m_ErrBlob != nullptr)
		{
			MessageBoxA(nullptr
				, (char*)m_ErrBlob->GetBufferPointer()
				, "Compute Shader Compile 오류", MB_OK);
		}
		else
		{
			MessageBox(nullptr
				, L"파일을 찾을 수 없습니다."
				, L"Compute Shader Compile 오류", MB_OK);
		}

		return E_FAIL;
	}

	// Compute Shader 객체 생성
	if (FAILED(DEVICE->CreateComputeShader(m_CSBlob->GetBufferPointer()
		, m_CSBlob->GetBufferSize()
		, nullptr, m_CS.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CComputeShader::Binding()
{

}

void CComputeShader::Execute()
{
	CONTEXT->CSSetShader(m_CS.Get(), nullptr, 0);

	// Group Count (최대 개수 제한 X) (그룹 당 Thread 개수는 1,024개)
	CONTEXT->Dispatch(2, 2, 1);
}
