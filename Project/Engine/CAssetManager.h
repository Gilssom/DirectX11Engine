#pragma once
#include "Singletone.h"

class CAssetManager : public CSingleton<CAssetManager>
{
    SINGLE(CAssetManager)

private:


public:
    void Init();
    void CreateDefaultMesh();
    void CreateDefaultTexture();
    void CreateDefaultMaterial();
    void CreateDefaultGraphicShader();
    void CreateDefaultComputeShader();

};

