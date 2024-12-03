#pragma once
#include "EditorUI.h"

class TreeUI;
class TreeNode;

class OutlinerUI :
    public EditorUI
{
private:
    TreeUI* m_Tree;

public:
    // Renew : ����, Reset : �ʱ� ���·� �ǵ���
    void RenewGameObject();


public:
    virtual void render_tick() override;

private:
    void AddGameObject(TreeNode* _Node, CGameObject* _Object);


public:
    OutlinerUI();
    ~OutlinerUI();
};

