#pragma once
#include "EditorUI.h"

class CGameObject;
class ComponentUI;

class CAsset;
class AssetUI;

class Inspector :
    public EditorUI
{
private:
    CGameObject*    m_TargetObject;
    ComponentUI*    m_arrComUI[(UINT)COMPONENT_TYPE::END];

    Ptr<CAsset>     m_TargetAsset;
    AssetUI*        m_arrAssetUI[(UINT)ASSET_TYPE::END];


public:
    virtual void render_tick() override;

public:
    void SetTargetObject(CGameObject* _Target);
    CGameObject* GetTargetObject() { return m_TargetObject; }

    void SetTargetAsset(Ptr<CAsset> _Asset);
    Ptr<CAsset> GetTargetAsset() { return m_TargetAsset; }

private:
    void CreateComponentUI();


public:
    Inspector();
    ~Inspector();
};

