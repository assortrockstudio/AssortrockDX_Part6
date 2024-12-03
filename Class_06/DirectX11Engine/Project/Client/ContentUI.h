#pragma once
#include "EditorUI.h"

class TreeUI;

class ContentUI :
    public EditorUI
{
private:
    TreeUI*     m_Tree;


public:
    // Renew : ����, Reset : �ʱ� ���·� �ǵ���
    void RenewContent();


public:    
    virtual void render_tick() override;

public:
    ContentUI();
    ~ContentUI();
};

