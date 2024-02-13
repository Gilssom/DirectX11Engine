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


// 상수버퍼 관련 구조체
struct tTransform
{
	// 상수 버퍼는 16 Byte 로 메모리 크기를 지정해줘야 한다.
	// 행렬 형태 사용
	Matrix matWorld;
	Matrix matView; // 카메라 전용
};