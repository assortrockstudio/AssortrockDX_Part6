#include "pch.h"
#include "MenuUI.h"

#include <Engine/CEngine.h>

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>

#include "Inspector.h"


MenuUI::MenuUI()
	: EditorUI("Menu", "##Menu")
{
}

MenuUI::~MenuUI()
{
}



void MenuUI::Asset()
{
}

void MenuUI::tick()
{
	if (ImGui::BeginMainMenuBar())
	{
        File();

        Level();

        GameObject();
             
		ImGui::EndMainMenuBar();
	}
}

void MenuUI::render_tick(){}

void MenuUI::File()
{
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("Exit", "Alt+F4"))
        {
            DestroyWindow(CEngine::GetInst()->GetMainWnd());
        }

        ImGui::EndMenu();
    }
}


void MenuUI::Level()
{
    if (ImGui::BeginMenu("Level"))
    {
        if (ImGui::MenuItem("Save Level"))
        {
            
        }

        if (ImGui::MenuItem("Load Level"))
        {

        }

        ImGui::Separator();

        if (ImGui::MenuItem("Play"))
        {

        }

        if (ImGui::MenuItem("Pause"))
        {

        }

        if (ImGui::MenuItem("Stop"))
        {

        }

        ImGui::EndMenu();
    }
}


void MenuUI::GameObject()
{
    if (ImGui::BeginMenu("GameObject"))
    {
        if (ImGui::MenuItem("Create EmptyObject"))
        {
            CGameObject* pNewObj = new CGameObject;
            pNewObj->AddComponent(new CTransform);
            pNewObj->SetName(L"Empty GameObject");

            SpawnObject(0, pNewObj);
        }

        if (ImGui::MenuItem("Register As Prefab"))
        {

        }


		if (ImGui::BeginMenu("Add Component"))
		{
            Inspector* pInspector = CImGuiMgr::GetInst()->FindEditorUI<Inspector>("Inspector");
            CGameObject* pTargetObj = pInspector->GetTargetObject();


			for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
			{
				if (ImGui::MenuItem(COMPONENT_TYPE_STRING[i]))
				{
					if (nullptr != pTargetObj)
					{
                        switch (COMPONENT_TYPE(i))
                        {
                        case COMPONENT_TYPE::TRANSFORM:
                            pTargetObj->AddComponent(new CTransform);
                            break;
                        case COMPONENT_TYPE::CAMERA:
                            pTargetObj->AddComponent(new CCamera);
                            break;
                        case COMPONENT_TYPE::COLLIDER2D:
                            pTargetObj->AddComponent(new CCollider2D);
                            break;
                        case COMPONENT_TYPE::COLLIDER3D:

                            break;
                        case COMPONENT_TYPE::ANIMATOR2D:
                            pTargetObj->AddComponent(new CAnimator2D);
                            break;
                        case COMPONENT_TYPE::ANIMATOR3D:

                            break;
                        case COMPONENT_TYPE::LIGHT2D:
                            pTargetObj->AddComponent(new CLight2D);
                            break;
                        case COMPONENT_TYPE::LIGHT3D:
                            break;
                        case COMPONENT_TYPE::MESHRENDER:
                            pTargetObj->AddComponent(new CMeshRender);
                            break;
                        case COMPONENT_TYPE::DECAL:
                            break;
                        case COMPONENT_TYPE::PARTICLESYSTEM:
                            pTargetObj->AddComponent(new CParticleSystem);
                            break;
                        case COMPONENT_TYPE::TILEMAP:
                            pTargetObj->AddComponent(new CTileMap);
                            break;
                        case COMPONENT_TYPE::LANDSCAPE:
                            break;                        
                        }
					}
				}
			}
            pInspector->SetTargetObject(pTargetObj);

            ImGui::EndMenu();
           
		}

        ImGui::EndMenu();
    }
}
