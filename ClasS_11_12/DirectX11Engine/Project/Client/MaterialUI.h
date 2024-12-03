#pragma once
#include "AssetUI.h"

class MaterialUI :
    public AssetUI
{
public:
    virtual void render_tick() override;

public:
    MaterialUI();
    ~MaterialUI();
};

