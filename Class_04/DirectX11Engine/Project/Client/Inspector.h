#pragma once
#include "EditorUI.h"

class CGameObject;
class ComponentUI;

class Inspector :
    public EditorUI
{
private:
    CGameObject*    m_TargetObject;
    ComponentUI*    m_arrComUI[(UINT)COMPONENT_TYPE::END];


public:
    virtual void render_tick() override;

public:
    void SetTargetObject(CGameObject* _Target);
    CGameObject* GetTargetObject() { return m_TargetObject; }

private:
    void CreateComponentUI();


public:
    Inspector();
    ~Inspector();
};

