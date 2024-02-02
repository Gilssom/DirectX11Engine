#pragma once
#include "CAsset.h"

class CShader : public CAsset
{
protected:
    // Error Blob
    ComPtr<ID3DBlob>		   m_ErrBlob;

public:
    virtual void Binding() = 0;

public:
    CShader(ASSET_TYPE type);
    ~CShader();
};

