#include "pch.h"
#include "CAnimator2D.h"

#include "CAnim2D.h"

CAnimator2D::CAnimator2D()
	: CComponent(COMPONENT_TYPE::ANIMATOR2D)
	, m_CurAnim(nullptr)
	, m_Repeat(0.f)
{

}

CAnimator2D::~CAnimator2D()
{
	Safe_Del_Map(m_mapAnim);
}

void CAnimator2D::FinalTick()
{
	if (m_CurAnim == nullptr)
		return;

	if (m_Repeat && m_CurAnim->IsFinish())
	{
		m_CurAnim->Reset();
	}

	m_CurAnim->FinalTick();
}

void CAnimator2D::Binding()
{
	if(m_CurAnim != nullptr)
		m_CurAnim->Binding();
}

void CAnimator2D::CreateAnimation(const wstring& animName, Ptr<CTexture> atlasTex
								, Vec2 leftTopPixelPos, Vec2 vSlicePixelSize, Vec2 backGroundSize, int frameCount, UINT fps)
{
	// 동일한 Anim 이 등록되어 있다면
	assert(!FindAnimation(animName));

	CAnim2D* pAnim = new CAnim2D;
	pAnim->SetName(animName);
	pAnim->Create(atlasTex, leftTopPixelPos, vSlicePixelSize, backGroundSize, frameCount, fps);

	// Animation 에 소유자 등록
	pAnim->m_Animator = this;
	m_mapAnim.insert(make_pair(animName, pAnim));
}

CAnim2D* CAnimator2D::FindAnimation(const wstring& animName)
{
	map<wstring, CAnim2D*>::iterator iter = m_mapAnim.find(animName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator2D::Play(const wstring& strAnimName, bool repeat)
{
	m_CurAnim = FindAnimation(strAnimName);
	m_Repeat = repeat;
}