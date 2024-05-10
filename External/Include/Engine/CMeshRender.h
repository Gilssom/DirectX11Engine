#pragma once
#include "CRenderComponent.h"

class CMeshRender : public CRenderComponent
{
public:
    virtual void FinalTick() override;
    virtual void Render() override;

    virtual void SaveToLevelFile(FILE* file) override;
    virtual void LoadFromLevelFile(FILE* file) override;

    CLONE(CMeshRender);

public:
    CMeshRender();
    ~CMeshRender();
};

