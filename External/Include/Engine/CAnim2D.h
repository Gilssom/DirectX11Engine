#pragma once
#include "CEntity.h"

struct tAnim2DFrame
{
	// 0 ���� 1 ������ UV ��ǥ��� ����ؾ��� (GPU �޸𸮷� ������ ����)
	Vec2	LeftTop;	// ù �ִϸ��̼��� ���� �� ��ǥ
	Vec2	SliceSize;	// Sprite �� ũ��
	float	Duration;	// �ִϸ��̼��� ��� �� �ӵ�
};

class CTexture;
class CAnimator2D;

class CAnim2D : public CEntity
{
private:
	CAnimator2D*			m_Animator; // ������ �����ϰ��ִ� Animator
	vector<tAnim2DFrame>	m_vecFrame; // ������ �������� Animation ����
	int						m_CurIdx;	// ����ǰ� �ִ� Index
	bool					m_Finish;	// �ִϸ��̼� ����

	Ptr<CTexture>			m_AtlasTex;	// Texture ����

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

