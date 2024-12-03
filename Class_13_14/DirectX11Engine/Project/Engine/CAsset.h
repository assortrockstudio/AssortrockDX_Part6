#pragma once
#include "CEntity.h"

#include "ptr.h"

class CAsset :
    public CEntity
{
private:
    wstring             m_Key;          // �ε��� Ű��
    wstring             m_RelativePath; // ����� 
    const ASSET_TYPE    m_Type;         // Asset �� Ÿ��
    int                 m_RefCount;     // ���� ī��Ʈ

public:
    const wstring& GetKey() { return m_Key; }
    const wstring& GetRelativePath() { return m_RelativePath; }
    ASSET_TYPE GetAssetType() { return m_Type; }

private:
    virtual int Load(const wstring& _FilePath) = 0;
    virtual int Save(const wstring& _FilePath) = 0;

private:
    void AddRef() { m_RefCount++; }
    void Release() 
    { 
        m_RefCount--; 
        if (m_RefCount <= 0)
        {
            delete this;
        }
    }

public:
    virtual CAsset* Clone() = 0;
public:
    CAsset(ASSET_TYPE _Type);
    CAsset(const CAsset& _Origin);
    ~CAsset();

    template<typename T>
    friend class Ptr;

    friend class CAssetMgr;
};