#include "pch.h"
#include "CAnim2D.h"

#include "CDevice.h"
#include "CConstBuffer.h"

#include "CTexture.h"
#include "CTimeManager.h"

CAnim2D::CAnim2D()
	: m_Animator(nullptr)
	, m_CurIdx(0)
	, m_Finish(false)
	, m_Time(0.f)
{

}

CAnim2D::~CAnim2D()
{

}

void CAnim2D::Create(Ptr<CTexture> atlasTex, Vec2 leftTopPixelPos, Vec2 vSlicePixelSize, Vec2 backGroundSize, int frameCount, UINT fps)
{
	assert(atlasTex.Get());

	m_AtlasTex = atlasTex;

	m_BackGroundSize.x = backGroundSize.x / m_AtlasTex->GetWidth();
	m_BackGroundSize.y = backGroundSize.y / m_AtlasTex->GetHeight();

	for (int i = 0; i < frameCount; i++)
	{
		tAnim2DFrame frame = {};

		frame.LeftTop.x = (leftTopPixelPos.x + vSlicePixelSize.x * i) / m_AtlasTex->GetWidth();
		frame.LeftTop.y = leftTopPixelPos.y / m_AtlasTex->GetHeight();

		frame.Duration = 1.f / (float)fps;

		frame.SliceSize.x = vSlicePixelSize.x / m_AtlasTex->GetWidth();
		frame.SliceSize.y = vSlicePixelSize.y / m_AtlasTex->GetHeight();

		m_vecFrame.push_back(frame);
	}
}

void CAnim2D::FinalTick()
{
	if (m_Finish)
		return;

	m_Time += DT;

	// 애니메이션 재생 시간을 넘어서면 다음으로 넘겨준다.
	if (m_vecFrame[m_CurIdx].Duration < m_Time)
	{
		m_Time = m_Time - m_vecFrame[m_CurIdx].Duration;
		++m_CurIdx;

		// 최대 애니메이션을 넘어서면 Finish
		if ((int)m_vecFrame.size() <= m_CurIdx)
		{
			m_CurIdx = m_vecFrame.size() - 1;
			m_Finish = true;
		}
	}
}

void CAnim2D::Binding()
{
	// 아틀라스 텍스쳐
	if (m_AtlasTex != nullptr)
		m_AtlasTex->Binding(14);

	// 프레임 정보
	static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::ANIMATION);

	tAnim2DInfo info = {};
	info.vLeftTop = m_vecFrame[m_CurIdx].LeftTop;
	info.vSliceSize = m_vecFrame[m_CurIdx].SliceSize;
	info.vBackGround = m_BackGroundSize;
	info.UseAnim2D = 1;

	pCB->SetData(&info);
	pCB->Binding();
}

void CAnim2D::Clear()
{
	static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::ANIMATION);
	pCB->Clear();
}