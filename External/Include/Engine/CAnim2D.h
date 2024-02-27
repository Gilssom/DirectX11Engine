#pragma once
#include "CEntity.h"

struct tAnim2DFrame
{
	// 0 에서 1 사이의 UV 좌표계로 계산해야함 (GPU 메모리로 보내기 위한)
	Vec2	LeftTop;	// 첫 애니메이션의 왼쪽 위 좌표
	Vec2	SliceSize;	// Sprite 의 크기
	float	Duration;	// 애니메이션이 재생 될 속도
};

class CTexture;
class CAnimator2D;

class CAnim2D : public CEntity
{
private:
	CAnimator2D*			m_Animator; // 본인을 소유하고있는 Animator
	vector<tAnim2DFrame>	m_vecFrame; // 프레임 간격으로 Animation 관리
	int						m_CurIdx;	// 재생되고 있는 Index
	bool					m_Finish;	// 애니메이션 종료

	Ptr<CTexture>			m_AtlasTex;	// Texture 정보

public:
	void Create(Ptr<CTexture> atlasTex
		, Vec2 leftTopPixelPos, Vec2 vSlicePixelSize, int frameCount, UINT fps);

public:
	void FinalTick();

public:
	CAnim2D();
	~CAnim2D();

	friend class CAnimator2D;
};

