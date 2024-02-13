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


// ������� ���� ����ü
struct tTransform
{
	// ��� ���۴� 16 Byte �� �޸� ũ�⸦ ��������� �Ѵ�.
	// ��� ���� ���
	Matrix matWorld;
	Matrix matView; // ī�޶� ����
};