#pragma once
#include "EditorUI.h"

class TreeUI;

class ContentUI :
    public EditorUI
{
private:
    TreeUI*     m_Tree;

public:
    // Renew : 갱신, Reset : 초기 상태로 되돌림
    void RenewContent();

private:
    UINT SelectAsset(DWORD_PTR _Data);


public:    
    virtual void render_tick() override;

public:
    ContentUI();
    ~ContentUI();
};

