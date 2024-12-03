#pragma once
#include "AssetUI.h"

class MaterialUI :
    public AssetUI
{
private:
    UINT    m_ParamDescMaxWidth;

public:
    virtual void render_tick() override;
    virtual void TargetChanged() override;


public:
    MaterialUI();
    ~MaterialUI();
};

