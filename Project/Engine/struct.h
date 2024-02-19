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


// ������� ���� ����ü
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