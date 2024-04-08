#pragma once
#include "CEntity.h"

struct tAnim2DFrame
{
	// 0 ���� 1 ������ UV ��ǥ��� ����ؾ��� (GPU �޸𸮷� ������ ����)
	Vec2	LeftTop;	// ù �ִϸ��̼��� ���� �� ��ǥ
	Vec2	SliceSize;	// Sprite �� ũ��
	Vec2	Offset;

	float	Duration;	// �ִϸ��̼��� ��� �� �ӵ�
	int		padding[3];	// ��� ���� ũ�⸦ ���߱� ���� ���� ( 16byte )
};

class CTexture;
class CAnimator2D;

class CAnim2D : public CEntity
{
private:
	CAnimator2D*			m_Animator; // ������ �����ϰ��ִ� Animator
	vector<tAnim2DFrame>	m_vecFrame; // ������ �������� Animation ����
	Vec2					m_BackGroundSize;

	int						m_CurIdx;	// ����ǰ� �ִ� Index
	bool					m_Finish;	// �ִϸ��̼� ����

	float					m_Time;

	Ptr<CTexture>			m_AtlasTex;	// Texture ����

public:
	bool IsFinish() { return m_Finish; }
	void Reset() { m_CurIdx = 0; m_Time = 0.f; m_Finish = false; }

public:
	void Create(Ptr<CTexture> atlasTex, Vec2 leftTopPixelPos, Vec2 vSlicePixelSize, Vec2 backGroundSize, int frameCount, UINT fps);

	void Save(const wstring& relativeFolderPath);
	void Load(const wstring& relativeFolderPath);

public:
	void FinalTick();
	void Binding();
	static void Clear();


	CLONE(CAnim2D);

public:
	CAnim2D();
	CAnim2D(const CAnim2D& other);
	~CAnim2D();

	friend class CAnimator2D;
};

