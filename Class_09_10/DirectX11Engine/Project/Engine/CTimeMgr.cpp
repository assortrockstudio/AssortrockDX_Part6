#include "pch.h"
#include "CTimeMgr.h"

#include "CEngine.h"
#include "CLevelMgr.h"
#include "CLevel.h"

CTimeMgr::CTimeMgr()
	: m_llFrequency{}
	, m_llCurCount{}
	, m_llPrevCount{}
	, m_DT(0.f)
	, m_Time(0.f)
	, m_EngineTime(0.f)
	, m_AccTime(0.f)
	, m_FrmCount(0)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// 초당 카운트 수
	QueryPerformanceFrequency(&m_llFrequency);
	QueryPerformanceCounter(&m_llCurCount);
	m_llPrevCount = m_llCurCount;
}

void CTimeMgr::tick()
{
	QueryPerformanceCounter(&m_llCurCount);

	m_EngineDT = m_DT = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (float)m_llFrequency.QuadPart;

	CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	if (nullptr == pLevel || pLevel->GetState() != LEVEL_STATE::PLAY)
		m_DT = 0.f;

	m_llPrevCount = m_llCurCount;

	// 누적시간
	m_Time += m_DT;
	m_EngineTime += m_EngineDT;




	m_AccTime += m_DT;
	++m_FrmCount;
	if (1.f < m_AccTime)
	{
		HWND hMainWnd = CEngine::GetInst()->GetMainWnd();
		wchar_t szText[255] = {};
		swprintf_s(szText, L"FPS : %d,  DeltaTime : %f", m_FrmCount,  m_DT);
		SetWindowText(hMainWnd, szText);

		m_AccTime -= 1.f;
		m_FrmCount = 0;
	}

	// 전역 상수버퍼 데이터 업데이트
	g_GlobalData.DeltaTime = m_DT;
	g_GlobalData.Time += m_DT;

	g_GlobalData.DeltaTimeEngine = m_EngineDT;
	g_GlobalData.TimeEngine = m_EngineTime;
}