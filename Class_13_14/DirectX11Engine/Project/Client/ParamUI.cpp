#include "pch.h"
#include "ParamUI.h"

#include "ImGui/imgui.h"
#include "CImGuiMgr.h"

UINT ParamUI::g_ParmUIID = 0;
int ParamUI::g_DescWidth = 0;

int ParamUI::Param_DragInt(const string& _strName, int* _pInOut, int _Speed)
{
    // 파라미터 이름
    ImGui::Text(_strName.c_str());
    ImGui::SameLine(g_DescWidth + 5);

    // 키값 생성
    char key[255] = {};
    sprintf_s(key, 255, "##DragInt_%d", g_ParmUIID++);        
    if (ImGui::DragInt(key, _pInOut, _Speed))
    {
        return true;
    }
        
    return false;
}

int ParamUI::Param_DragFloat(const string& _strName, float* _pInOut, float _Speed)
{
    // 파라미터 이름
    ImGui::Text(_strName.c_str());    
    ImGui::SameLine(g_DescWidth + 5);

    // 키값 생성
    char key[255] = {};
    sprintf_s(key, 255, "##DragFloat_%d", g_ParmUIID++);

    if (ImGui::DragFloat(key, _pInOut, _Speed))
    {
        return true;
    }

    return false;
}

int ParamUI::Param_DragVec2(const string& _strName, Vec2* _pInOut, float _Speed)
{
    // 파라미터 이름
    ImGui::Text(_strName.c_str());
    ImGui::SameLine(g_DescWidth + 5);

    // 키값 생성
    char key[255] = {};
    sprintf_s(key, 255, "##DragVec2_%d", g_ParmUIID++);

    float arr[2] = { _pInOut->x, _pInOut->y };

    if (ImGui::DragFloat2(key, arr, _Speed))
    {
        _pInOut->x = arr[0];
        _pInOut->y = arr[1];

        return true;
    }
}

int ParamUI::Param_DragVec4(const string& _strName, Vec4* _pInOut, float _Speed)
{
    // 파라미터 이름
    ImGui::Text(_strName.c_str());
    ImGui::SameLine(g_DescWidth + 5);

    // 키값 생성
    char key[255] = {};
    sprintf_s(key, 255, "##DragVec4_%d", g_ParmUIID++);

    if (ImGui::DragFloat4(key, *_pInOut, _Speed))
    {
        return true;
    }

    return false;
}

int ParamUI::Param_DragMat(const string& _strName, Matrix* _pInOut, float _Speed)
{

    return false;
}


int ParamUI::Param_Tex(const string& _strName, Ptr<CTexture> _Tex)
{
    // 파라미터 이름
    ImGui::Text(_strName.c_str());
    ImGui::SameLine(g_DescWidth + 5);

    // 키값 생성
    char key[255] = {};
    sprintf_s(key, 255, "##Image_%d", g_ParmUIID++);

    // Image 출력    
    ImTextureID TexID = (nullptr == _Tex) ? nullptr : _Tex->GetSRV().Get();    
    ImGui::Image( TexID
                , ImVec2(150.f, 150.f)
                , ImVec2(0.0f, 0.0f)
                , ImVec2(1.0f, 1.0f)
                , ImGui::GetStyleColorVec4(ImGuiCol_Text));

    return true;
}
