#pragma once
#include "CComponent.h"

class CCamera : public CComponent
{
private:
	PROJ_TYPE	m_ProjType;

	int m_CamPriority;		// Render Manager 에 등록될때 카메라의 우선순위 ( 0 : Main Camera , -1 : 미등록 카메라, 0 보다 크다 : Sub Camera )

	float m_FOV;			// Field of View (카메라 시야각)
	float m_Far;			// 카메라가 볼 수 있는 최대 거리

	float m_Width;			// 시야 가로 길이
	float m_AspectRatio;	// 종횡비

	float m_Scale;			// 직교투영 배율

	// View Space 의 특징
	// 1. Camera 가 원점이다
	// 2. Camera 는 Z 축을 바라보고 있다.
	Matrix m_matView;
	Matrix m_matProj; // 투영


public:
	void SetCameraPriority(int priority);

	void SetProjType(PROJ_TYPE type) { m_ProjType = type; }
	void SetFar(float _far) { m_Far = _far; }
	void SetFOV(float _fov) { m_FOV = _fov; }
	void SetWidth(float width) { m_Width = width; }
	void SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; }
	void SetScale(float scale) { m_Scale = scale; }

	int GetCameraPriority() { return m_CamPriority; }
	PROJ_TYPE GetProjType() { return m_ProjType; }
	float GetFar() { return m_Far; }
	float GetFOV() { return m_FOV; }
	float GetWidth() { return m_Width; }
	float GetAspectRatio() { return m_AspectRatio; }
	float GetScale() { return m_Scale; }

public:
	virtual	void FinalTick() override; // 반드시 구현
	void Render();

public:
	CCamera();
	~CCamera();
};

