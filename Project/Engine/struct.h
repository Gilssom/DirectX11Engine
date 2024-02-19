#pragma once

// 자료형 크기를 1Byte 기준으로 정렬을 하게 해준다.
//#pragma pack(1)

// 3차원 공간에서 좌표를 나타낼 수 있는 " Vertex 정점 " 정보들
struct Vtx
{
	// 원래라면 32Byte 구조체인데
	// DX 시스템으로 인해 28Byte 구조체로 정렬된다.
	Vec3 vPos;		// 좌표
	Vec4 vColor;	// 색상 및 투명도
	Vec2 vUv;		// UV 좌표
};

// Debug Render 요청 정보
struct tDebugShapeInfo
{
	DEBUG_SHAPE		Shape;
	Vec3			Position;
	Vec3			Scale;
	Vec3			Rotation;
	Matrix			matWorld; // 모든 위치 회전 크기를 가진 월드 행렬
	Vec4			Color;
	float			Duration; // 유지 시간
	float			Age;	  // 존재 시간
};


// 상수버퍼 관련 구조체
struct tTransform
{
	// 상수 버퍼 변수는 16 Byte 로 메모리 크기를 지정해줘야 한다.
	// 행렬 형태 사용
	Matrix matWorld;
	Matrix matView; // 카메라 전용
	Matrix matProj; // 투영 행렬
};

// 전역 변수 - extern.cpp 에서 선언해줘서 사용 가능하게
extern tTransform g_Trans;

// 상수버퍼 Material 관련 구조체
struct tMtrlConst
{
	int		iArr[4];
	float	fArr[4];
	Vec2	v2Arr[4];
	Vec4	v4Arr[4];
	Matrix	matArr[4];
};