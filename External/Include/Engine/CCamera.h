#pragma once
#include "CComponent.h"

class CCamera : public CComponent
{
private:
	int m_CamPriority; // Render Manager �� ��ϵɶ� ī�޶��� �켱���� ( 0 : Main Camera , -1 : �̵�� ī�޶�, 0 ���� ũ�� : Sub Camera )

	float m_Far; // ī�޶� �� �� �ִ� �ִ� �Ÿ�

	// View Space �� Ư¡
	// 1. Camera �� �����̴�
	// 2. Camera �� Z ���� �ٶ󺸰� �ִ�.
	Matrix m_matView;
	Matrix m_matProj; // ����


public:
	void SetCameraPriority(int priority);

public:
	virtual	void FinalTick() override; // �ݵ�� ����
	void Render();

public:
	CCamera();
	~CCamera();
};

