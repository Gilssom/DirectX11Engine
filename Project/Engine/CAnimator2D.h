#pragma once
#include "CComponent.h"

#include "CTexture.h"

class CAnim2D;

class CAnimator2D : public CComponent
{
private:
	map<wstring, CAnim2D*>	m_mapAnim; // Animation Sprite ����
	CAnim2D*				m_CurAnim; // ����ǰ� �ִ� Animation
	bool					m_Repeat;  // �ݺ� ����


public:
	void CreateAnimation(const wstring& animName, Ptr<CTexture> atlasTex, Vec2 leftTopPixelPos, Vec2 vSlicePixelSize, int frameCount, UINT fps);
	CAnim2D* FindAnimation(const wstring& animName);

public:
	virtual void FinalTick() override;


public:
	CAnimator2D();
	~CAnimator2D();
};

