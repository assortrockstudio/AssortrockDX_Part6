#pragma once
#include "CAsset.h"

class CGameObject;

class CPrefab :
    public CAsset
{
private:
    CGameObject*    m_ProtoObj;

public:
    CGameObject* Instantiate();

public:
    virtual int Load(const wstring& _FilePath) {return S_OK;};
    virtual int Save(const wstring& _FilePath) { return S_OK; };


    
public:
    CLONE(CPrefab);
    CPrefab();
    CPrefab(CGameObject* _Proto);
    CPrefab(const CPrefab& _Other);
    ~CPrefab();
};

