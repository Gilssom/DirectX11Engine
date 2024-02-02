#pragma once
#include "CShader.h"

class CGraphicShader : public CShader
{
private:
    ComPtr<ID3DBlob>            m_VSBlob;
    ComPtr<ID3DBlob>            m_PSBlob;

    ComPtr<ID3D11VertexShader>  m_VS;
    ComPtr<ID3D11PixelShader>   m_PS;

    // 정점 하나를 구성하는 Layout 정보가 필요함
    ComPtr<ID3D11InputLayout>   m_Layout;

    D3D11_PRIMITIVE_TOPOLOGY    m_Topology;

public:
    int CreateVertexShader(const wstring& strFilePath, const string& vsFuncName);
    int CreatePixelShader(const wstring& strFilePath, const string& psFuncName);

    void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology) { m_Topology = topology; }

    virtual void Binding() override;

public:
    CGraphicShader();
    ~CGraphicShader();
};

