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

// Task 관련 구조체
struct tTask
{
	TASK_TYPE	Type;

	DWORD_PTR	dwParam_0;
	DWORD_PTR	dwParam_1;
	DWORD_PTR	dwParam_2;
};

// 광원 관련 구조체
struct tLight
{
	Vec4	vDiffuse;		// 난반사 (빛의 색상)
	Vec4	vAmbient;		// 환경광 (빛으로 발생하는 최소한의 밝기)
	Vec4	vMaxSpecular;	// 반사광 (빛으로 발생하는 반사광의 최대 밝기)
};

// 광원 정보
struct tLightInfo
{
	tLight	Light;

	UINT	LightType;	// 0 : Directional Light | 1 : Point Light | 2 : Spot Light
	Vec3	WorldDir;	// World Space 에서 광원의 방향
	Vec3	WorldPos;	// World Space 에서 광원의 위치
	float	Range;		// Spot Light 또는 Point Light 인 경우 광원의 영향 범위
	float	Angle;		// Spot Light 인 경우 광원의 각도

	Vec3	vPadding;	// 16 Byte 맞추기 위한 용도
};


// ====================
// 상수버퍼 관련 구조체
// ====================
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
	Vec2	vResolution;	// 렌더링 해상도
	float	DeltaTime;		// DT
	float	Time;			// 게임 시작한 후 경과한 시간

	int		Light2DCount;	// 2D 광원 개수
	int		Light3DCount;	// 3D 광원 개수

	Vec2	Padding;
};

extern tGlobalData g_GlobalData;