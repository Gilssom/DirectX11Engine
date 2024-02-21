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

    RS_TYPE                     m_RSType;
    DS_TYPE                     m_DSType;
    BS_TYPE                     m_BSType;

public:
    int CreateVertexShader(const wstring& strFilePath, const string& vsFuncName);
    int CreatePixelShader(const wstring& strFilePath, const string& psFuncName);

    void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology) { m_Topology = topology; }
    void SetRSType(RS_TYPE type) { m_RSType = type; }
    void SetDSType(DS_TYPE type) { m_DSType = type; }
    void SetBSType(BS_TYPE type) { m_BSType = type; }

    virtual void Binding() override;

public:
    CGraphicShader();
    ~CGraphicShader();
};

