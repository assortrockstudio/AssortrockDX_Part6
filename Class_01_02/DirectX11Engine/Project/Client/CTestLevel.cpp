#include "pch.h"


#include "CTestLevel.h"


#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>
#include <Engine/CAnim2D.h>

#include <Scripts/CPlayerScript.h>
#include <Scripts/CCameraMoveScript.h>
#include <Scripts/CBackgroundScript.h>
#include <Scripts/CMissileScript.h>
		 
#include <Engine/CCollisionMgr.h>
#include <Engine/CSetColorCS.h>
		 
#include <Engine/CStructuredBuffer.h>
#include <Engine/CPrefab.h>


void CTestLevel::CreateTestLevel()
{
	// Prefab 제작 및 AssetMgr 에 등록
	CreatePrefab();

	CLevel* pLevel = nullptr;

	// 임시 레벨 설정
	pLevel = new CLevel;
	pLevel->GetLayer(0)->SetName(L"Default");
	pLevel->GetLayer(1)->SetName(L"Player");
	pLevel->GetLayer(2)->SetName(L"Monster");

	// Camera Object 생성
	CGameObject* pCamObj = new CGameObject;
	pCamObj->SetName(L"MainCamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);
	pCamObj->AddComponent(new CCameraMoveScript);

	pCamObj->Camera()->LayerCheckAll();
	pCamObj->Camera()->SetCameraPriority(0); // 메인 카메라로 설정
	pCamObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);

	pLevel->AddObject(0, pCamObj);

	//CGameObject* pCamClone = pCamObj->Clone();
	//pCamClone->Camera()->SetCameraPriority(0);
	//m_CurLevel->AddObject(0, pCamClone);
	//delete pCamObj;

	// 광원 오브젝트 생성
	CGameObject* pLightObj = new CGameObject;
	pLightObj->AddComponent(new CTransform);
	pLightObj->AddComponent(new CLight2D);

	pLightObj->Transform()->SetRelativePos(Vec3(-500.f, 0.f, 0.f));

	pLightObj->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	pLightObj->Light2D()->SetDiffuse(Vec3(1.f, 1.f, 1.f));
	pLightObj->Light2D()->SetRange(700.f);
	//pLightObj->Light2D()->SetAmbient(Vec3(0.1f, 0.1f, 0.1f));

	pLevel->AddObject(0, pLightObj);

	pLightObj = pLightObj->Clone();
	pLightObj->Transform()->SetRelativePos(Vec3(500.f, 0.f, 0.f));
	pLevel->AddObject(0, pLightObj);


	// Player Object
	CGameObject* pPlayer = new CGameObject;
	pPlayer->SetName(L"Player");
	pPlayer->AddComponent(new CTransform);
	pPlayer->AddComponent(new CMeshRender);
	pPlayer->AddComponent(new CAnimator2D);
	pPlayer->AddComponent(new CCollider2D);
	pPlayer->AddComponent(new CPlayerScript);

	pPlayer->Transform()->SetRelativePos(Vec3(0.f, 0.f, 200.f));
	pPlayer->Transform()->SetRelativeScale(Vec3(200.f, 200, 1.f));

	pPlayer->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pPlayer->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	pPlayer->Collider2D()->SetAbsolute(true);
	pPlayer->Collider2D()->SetOffset(Vec3(0.f, 0.f, 0.f));
	pPlayer->Collider2D()->SetScale(Vec3(150.f, 150.f, 1.f));

	pPlayer->Animator2D()->LoadAnimation(L"Animation\\MOVE_DOWN.anim");
	pPlayer->Animator2D()->Play(L"MOVE_DOWN", true);

	pLevel->AddObject(0, pPlayer, false);

	// Background Object
	CGameObject* pBackground = new CGameObject;
	pBackground->AddComponent(new CTransform);
	pBackground->AddComponent(new CMeshRender);
	pBackground->AddComponent(new CBackgroundScript);

	pBackground->Transform()->SetRelativePos(Vec3(0.f, 0.f, 1000.f));
	pBackground->Transform()->SetRelativeScale(Vec3(1600.f, 900.f, 1.f));

	pBackground->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pBackground->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"BackgroundMtrl"));
	pBackground->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Background.jpg", L"texture\\Background.jpg"));
	pBackground->MeshRender()->GetMaterial()->SetTexParam(TEX_1, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\noise\\noise_03.jpg", L"texture\\noise\\noise_03.jpg"));

	pLevel->AddObject(0, pBackground, false);

	pBackground = pBackground->Clone();
	pBackground->Transform()->SetRelativePos(Vec3(0.f, 0.f, 1500.f));
	pLevel->AddObject(0, pBackground, false);


	// TileMap
	CGameObject* pTileMap = new CGameObject;
	pTileMap->SetName(L"TileMap");
	pTileMap->AddComponent(new CTransform);
	pTileMap->AddComponent(new CTileMap);

	pTileMap->TileMap()->SetAltasTexture(CAssetMgr::GetInst()->Load<CTexture>(L"texture\\TILE.bmp", L"texture\\TILE.bmp"));
	pTileMap->TileMap()->SetRowCol(8, 8);
	pTileMap->TileMap()->SetTileEachSize(Vec2(64.f, 64.f));
	pTileMap->TileMap()->SetAltasTileSize(Vec2(64.f, 64.f));

	pTileMap->Transform()->SetRelativePos(Vec3(-500.f, 0.f, 300.f));

	pLevel->AddObject(0, pTileMap, false);

	pTileMap = pTileMap->Clone();
	pTileMap->Transform()->SetRelativePos(Vec3(500.f, 0.f, 300.f));
	pLevel->AddObject(0, pTileMap, false);

	// PostProcee Filter 추가
	CGameObject* pFilterObj = new CGameObject;

	pFilterObj->AddComponent(new CTransform);
	pFilterObj->AddComponent(new CMeshRender);

	pFilterObj->Transform()->SetRelativePos(500.f, 0.f, 200.f);
	pFilterObj->Transform()->SetRelativeScale(200.f, 200.f, 1.f);

	pFilterObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pFilterObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"DistortionMtrl"));
	pFilterObj->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CAssetMgr::GetInst()->FindAsset<CTexture>(L"RenderTargetCopyTex"));
	pFilterObj->MeshRender()->GetMaterial()->SetTexParam(TEX_1, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\noise\\noise_03.jpg", L"texture\\noise\\noise_03.jpg"));

	pLevel->AddObject(0, pFilterObj, false);

	// Level 의 충돌설정
	CCollisionMgr::GetInst()->LayerCheck(1, 1);
	CCollisionMgr::GetInst()->LayerCheck(2, 1);

	ChangeLevel(pLevel, LEVEL_STATE::PLAY);
}





void CTestLevel::CreatePrefab()
{
	// Particle Prefab
	CGameObject* pParticleObj = new CGameObject;
	pParticleObj->SetName(L"Particle");
	pParticleObj->AddComponent(new CTransform);
	pParticleObj->AddComponent(new CParticleSystem);

	pParticleObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
	pParticleObj->ParticleSystem()->SetParticleTexture(CAssetMgr::GetInst()->Load<CTexture>(L"texture\\particle\\AlphaCircle.png", L"texture\\particle\\AlphaCircle.png"));

	CAssetMgr::GetInst()->AddAsset<CPrefab>(L"ParticlePrefab", new CPrefab(pParticleObj));

	// Missile Prefab 
	CGameObject* pNewObj = new CGameObject;
	pNewObj->AddComponent(new CTransform);
	pNewObj->AddComponent(new CMeshRender);
	pNewObj->AddComponent(new CMissileScript);
	pNewObj->Transform()->SetRelativeScale(Vec3(40.f, 40.f, 40.f));
	pNewObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pNewObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	CAssetMgr::GetInst()->AddAsset<CPrefab>(L"MissilePrefab", new CPrefab(pNewObj));
}