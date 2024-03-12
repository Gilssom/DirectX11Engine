#pragma once

// �ڷ��� ũ�⸦ 1Byte �������� ������ �ϰ� ���ش�.
//#pragma pack(1)

// 3���� �������� ��ǥ�� ��Ÿ�� �� �ִ� " Vertex ���� " ������
struct Vtx
{
	// ������� 32Byte ����ü�ε�
	// DX �ý������� ���� 28Byte ����ü�� ���ĵȴ�.
	Vec3 vPos;		// ��ǥ
	Vec4 vColor;	// ���� �� ����
	Vec2 vUv;		// UV ��ǥ
};

// Debug Render ��û ����
struct tDebugShapeInfo
{
	DEBUG_SHAPE		Shape;
	Vec3			Position;
	Vec3			Scale;
	Vec3			Rotation;
	Matrix			matWorld; // ��� ��ġ ȸ�� ũ�⸦ ���� ���� ���
	Vec4			Color;
	float			Duration; // ���� �ð�
	float			Age;	  // ���� �ð�
};

// Task ���� ����ü
struct tTask
{
	TASK_TYPE	Type;

	DWORD_PTR	dwParam_0;
	DWORD_PTR	dwParam_1;
	DWORD_PTR	dwParam_2;
};

// ���� ���� ����ü
struct tLight
{
	Vec4	vDiffuse;		// ���ݻ� (���� ����)
	Vec4	vAmbient;		// ȯ�汤 (������ �߻��ϴ� �ּ����� ���)
	Vec4	vMaxSpecular;	// �ݻ籤 (������ �߻��ϴ� �ݻ籤�� �ִ� ���)
};

// ���� ����
struct tLightInfo
{
	tLight	Light;

	UINT	LightType;	// 0 : Directional Light | 1 : Point Light | 2 : Spot Light
	Vec3	WorldDir;	// World Space ���� ������ ����
	Vec3	WorldPos;	// World Space ���� ������ ��ġ
	float	Range;		// Spot Light �Ǵ� Point Light �� ��� ������ ���� ����
	float	Angle;		// Spot Light �� ��� ������ ����

	Vec3	vPadding;	// 16 Byte ���߱� ���� �뵵
};


// ====================
// ������� ���� ����ü
// ====================
struct tTransform
{
	// ��� ���� ������ 16 Byte �� �޸� ũ�⸦ ��������� �Ѵ�.
	// ��� ���� ���
	Matrix matWorld;
	Matrix matView; // ī�޶� ����
	Matrix matProj; // ���� ���
};

// ���� ���� - extern.cpp ���� �������༭ ��� �����ϰ�
extern tTransform g_Trans;

// ������� Material ���� ����ü
struct tMtrlConst
{
	int		iArr[4];
	float	fArr[4];
	Vec2	v2Arr[4];
	Vec4	v4Arr[4];
	Matrix	matArr[4];
};

struct tAnim2DInfo
{
	Vec2	vLeftTop;
	Vec2	vSliceSize;

	Vec2	vOffset;
	Vec2	vBackGround;

	int		UseAnim2D;
	int		padding[3];
};

struct tGlobalData
{
	Vec2	vResolution;	// ������ �ػ�
	float	DeltaTime;		// DT
	float	Time;			// ���� ������ �� ����� �ð�

	int		Light2DCount;	// 2D ���� ����
	int		Light3DCount;	// 3D ���� ����

	Vec2	Padding;
};

extern tGlobalData g_GlobalData;