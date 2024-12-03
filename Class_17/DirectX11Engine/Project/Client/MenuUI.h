#pragma once
#include "EditorUI.h"


class MenuUI :
    public EditorUI
{
private:

public:
    void File();

    void GameObject();

    void Level();

    void Asset();

public:
    virtual void tick() override;
    virtual void render_tick() override;

public:
    MenuUI();
    ~MenuUI();
};

