#pragma once
#include "EditorUI.h"

class TreeUI;

class TreeNode
{
private:
    TreeUI*             m_Owner;
    TreeNode*           m_Parent;
    vector<TreeNode*>   m_vecChildNode;
    string              m_Name;

    DWORD_PTR           m_Data;
    
    bool                m_bFrame;

public:
    void SetName(const string& _Name) { m_Name = _Name; }
    void SetData(DWORD_PTR _Data) { m_Data = _Data; }
    void SetFrame(bool _Frame) { m_bFrame = _Frame; }

    const string& GetName() { return m_Name; }
    DWORD_PTR GetData() { return m_Data; }

    void AddChildNode(TreeNode* _Child)
    {
        m_vecChildNode.push_back(_Child);
        _Child->m_Parent = this;
    }
    const vector<TreeNode*>& GetChildNode() { return m_vecChildNode; }



public:
    void render_tick();

public:
    TreeNode()
        : m_Parent(nullptr)
        , m_Data(0)
        , m_bFrame(false)
    {}

    TreeNode(const string& _Name, DWORD_PTR _Data)
        : m_Parent(nullptr)
        , m_Name(_Name)
        , m_Data(_Data)
        , m_bFrame(false)
    {}

    ~TreeNode();

    friend class TreeUI;
};



class TreeUI :
    public EditorUI
{
private:
    TreeNode*   m_RootNode;
    bool        m_bShowRoot;
    bool        m_bShowFileName;

public:
    void ShowRoot(bool _Show) { m_bShowRoot = _Show; }
    void ShowFileNameOnly(bool _ShowFileName) { m_bShowFileName = _ShowFileName; }
    TreeNode* AddTreeNode(TreeNode* _Parent, const string& _NodeName, DWORD_PTR _dwData = 0);
    void Clear()
    {
        if (nullptr != m_RootNode)
        {
            delete m_RootNode;
            m_RootNode = nullptr;
        }         
    }


public:
    virtual void render_tick() override;

public:
    TreeUI();
    ~TreeUI();

    friend class TreeNode;
};

