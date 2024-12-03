#pragma once
#include "EditorUI.h"

class TreeUI;

class ContentUI :
    public EditorUI
{
private:
    TreeUI*     m_Tree;


public:
    virtual void render_tick() override;

public:
    ContentUI();
    ~ContentUI();
};

