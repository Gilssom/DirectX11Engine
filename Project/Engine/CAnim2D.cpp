#include "pch.h"
#include "CAnim2D.h"

#include "CTexture.h"

CAnim2D::CAnim2D()
	: m_CurIdx(0)
	, m_Finish(false)
{

}

CAnim2D::~CAnim2D()
{

}

void CAnim2D::Create(Ptr<CTexture> atlasTex, Vec2 leftTopPixelPos, Vec2 vSlicePixelSize, int frameCount, UINT fps)
{
	assert(atlasTex.Get());

	m_AtlasTex = atlasTex;

	for (int i = 0; i < frameCount; i++)
	{
		tAnim2DFrame frame = {};

		frame.LeftTop.x = (leftTopPixelPos.x + leftTopPixelPos.x * i) / m_AtlasTex->GetWidth();
		frame.LeftTop.y = leftTopPixelPos.y / m_AtlasTex->GetHeight();

		frame.Duration = 1.f / (float)fps;

		frame.SliceSize.x = vSlicePixelSize.x / m_AtlasTex->GetWidth();
		frame.SliceSize.y = vSlicePixelSize.y / m_AtlasTex->GetHeight();

		m_vecFrame.push_back(frame);
	}
}

void CAnim2D::FinalTick()
{
	m_CurIdx = 0;
}