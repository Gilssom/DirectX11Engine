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
	// 기존에 있던 메모리가 남아있는 현상을 대비
	// 새로운 Create 가 들어오면 기존에 가리키던 버퍼 및 SRV 를 가리키지 않게 초기화.
	m_SB = nullptr;
	m_SRV = nullptr;

	// 버퍼의 크기를 16의 배수로 설정해야 한다.
	assert(!(elementSize % 16));
	
	m_ElementSize = elementSize;
	m_ElementCount = elementCount;

	m_Desc.ByteWidth = m_ElementSize * m_ElementCount; // 생성될 버퍼의 크기

	m_Desc.Usage = D3D11_USAGE_DYNAMIC;
	m_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	m_Desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	// 지금 만들어진 버퍼가 Texture 버퍼가 아닌, 구조화 버퍼란걸 알려주기 위한 용도
	m_Desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	// 구조화 버퍼안에 있는 요소 하나하나의 크기
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

	// Shader Resource View 설정
	D3D11_SHADER_RESOURCE_VIEW_DESC tViewDesc = {};
	tViewDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	tViewDesc.BufferEx.NumElements = m_ElementCount;

	hr = DEVICE->CreateShaderResourceView(m_SB.Get(), &tViewDesc, m_SRV.GetAddressOf());

	return hr;
}

// 가변적이기 때문에 Count 를 원하는 량 만큼 받아야됨
void CStructuredBuffer::SetData(void* data, UINT elementCount)
{
	// Count 가 안들어오면 구조화 버퍼의 크기만큼 연산
	if (!elementCount)
	{
		elementCount = m_ElementCount;
	}

	D3D11_MAPPED_SUBRESOURCE tSub = {};
	// 데이터 수정
	CONTEXT->Map(m_SB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);

	// 데이터 넣기
	memcpy(tSub.pData, data, elementCount * m_ElementSize);

	// 데이터 수정 완료
	CONTEXT->Unmap(m_SB.Get(), 0);
}

void CStructuredBuffer::Binding(UINT registerNum)
{
	CONTEXT->VSSetShaderResources(registerNum, 1, m_SRV.GetAddressOf());
	CONTEXT->HSSetShaderResources(registerNum, 1, m_SRV.GetAddressOf());
	CONTEXT->DSSetShaderResources(registerNum, 1, m_SRV.GetAddressOf());
	CONTEXT->GSSetShaderResources(registerNum, 1, m_SRV.GetAddressOf());
	CONTEXT->PSSetShaderResources(registerNum, 1, m_SRV.GetAddressOf());
}