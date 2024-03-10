#include "pch.h"
#include "CStructuredBuffer.h"

#include "CDevice.h"

CStructuredBuffer::CStructuredBuffer()
	: m_Desc{}
	, m_ElementSize(0)
	, m_ElementCount(0)
{

}

CStructuredBuffer::~CStructuredBuffer()
{

}

int CStructuredBuffer::Create(UINT elementSize, UINT elementCount, void* initialData)
{
	// ������ ũ�⸦ 16�� ����� �����ؾ� �Ѵ�.
	assert(!elementSize % 16);
	
	m_ElementSize = elementSize;
	m_ElementCount = elementCount;

	m_Desc.ByteWidth = m_ElementSize * m_ElementCount; // ������ ������ ũ��

	m_Desc.Usage = D3D11_USAGE_DEFAULT;
	m_Desc.CPUAccessFlags = 0;

	m_Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	// ���� ������� ���۰� Texture ���۰� �ƴ�, ����ȭ ���۶��� �˷��ֱ� ���� �뵵
	m_Desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	// ����ȭ ���۾ȿ� �ִ� ��� �ϳ��ϳ��� ũ��
	m_Desc.StructureByteStride = elementSize;

	HRESULT hr = E_FAIL;

	if (initialData)
	{
		D3D11_SUBRESOURCE_DATA tSub = {};
		tSub.pSysMem = initialData;
		hr = DEVICE->CreateBuffer(&m_Desc, &tSub, m_SB.GetAddressOf());
	}
	else
	{
		hr = DEVICE->CreateBuffer(&m_Desc, nullptr, m_SB.GetAddressOf());
	}

	if (FAILED(hr))
		return E_FAIL;

	// Shader Resource View ����
	D3D11_SHADER_RESOURCE_VIEW_DESC tViewDesc = {};
	tViewDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	tViewDesc.BufferEx.NumElements = m_ElementCount;

	hr = DEVICE->CreateShaderResourceView(m_SB.Get(), &tViewDesc, m_SRV.GetAddressOf());

	return hr;
}

void CStructuredBuffer::Binding(UINT registerNum)
{
	CONTEXT->VSSetShaderResources(registerNum, 1, m_SRV.GetAddressOf());
	CONTEXT->HSSetShaderResources(registerNum, 1, m_SRV.GetAddressOf());
	CONTEXT->DSSetShaderResources(registerNum, 1, m_SRV.GetAddressOf());
	CONTEXT->GSSetShaderResources(registerNum, 1, m_SRV.GetAddressOf());
	CONTEXT->PSSetShaderResources(registerNum, 1, m_SRV.GetAddressOf());
}