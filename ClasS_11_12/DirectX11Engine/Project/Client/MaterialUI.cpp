#include "pch.h"
#include "MaterialUI.h"

#include <Engine/CMaterial.h>
#include <Engine/CGraphicShader.h>

MaterialUI::MaterialUI()
	: AssetUI("MaterialUI", "##MaterialUI", ASSET_TYPE::MATERIAL)
{
}

MaterialUI::~MaterialUI()
{
}

void MaterialUI::render_tick()
{
	render_title();

	string strName = ToString(GetTarget()->GetKey());

	Ptr<CMaterial> pMtrl = dynamic_cast<CMaterial*>(GetTarget().Get());
	assert(pMtrl.Get());

	// �޽� �̸�
	ImGui::Text("Material Name");
	ImGui::SameLine(110);
	ImGui::InputText("##MaterialNameMaterialUI", (char*)strName.c_str(), strName.capacity(), ImGuiInputTextFlags_ReadOnly);

	// ����� ���̴� ���� ���
	string strShaderName = nullptr == pMtrl->GetShader() ? "" : ToString(pMtrl->GetShader()->GetKey());

	ImGui::Text("Shader Name");
	ImGui::SameLine(110);
	ImGui::InputText("##ShaderNameShaderUI", (char*)strShaderName.c_str(), strShaderName.capacity(), ImGuiInputTextFlags_ReadOnly);



}