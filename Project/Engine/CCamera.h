#pragma once
#include "CComponent.h"

class CCamera : public CComponent
{
private:
	int m_CamPriority; // Render Manager 에 등록될때 카메라의 우선순위 ( 0 : Main Camera , -1 : 미등록 카메라, 0 보다 크다 : Sub Camera )

	float m_Far; // 카메라가 볼 수 있는 최대 거리

	// View Space 의 특징
	// 1. Camera 가 원점이다
	// 2. Camera 는 Z 축을 바라보고 있다.
	Matrix m_matView;
	Matrix m_matProj; // 투영


public:
	void SetCameraPriority(int priority);

public:
	virtual	void FinalTick() override; // 반드시 구현
	void Render();

public:
	CCamera();
	~CCamera();
};

