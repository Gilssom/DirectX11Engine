#pragma once
#include "CAsset.h"

class CShader : public CAsset
{
protected:
    // Error Blob
    ComPtr<ID3DBlob>		   m_ErrBlob;

public:
    virtual int Binding() = 0;
    virtual int Load(const wstring& _FilePath) override { return S_OK; }
    virtual int Save(const wstring& _FilePath) override { return S_OK; }


    CLONE_DISABLE(CShader);

public:
    CShader(ASSET_TYPE type);
    ~CShader();
};

