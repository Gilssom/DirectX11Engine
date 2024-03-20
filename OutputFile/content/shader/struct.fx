#ifndef _STRUCT
#define _STRUCT

// 광원 관련 구조체
struct tLight
{
    float4 vDiffuse;        // 난반사 (빛의 색상)
    float4 vAmbient;        // 환경광 (빛으로 발생하는 최소한의 밝기)
    float4 vMaxSpecular;    // 반사광 (빛으로 발생하는 반사광의 최대 밝기)
};

// 광원 정보
struct tLightInfo
{
    tLight  Light;          // 광원 색상 정보

    uint    LightType;      // 0 : Directional Light | 1 : Point Light | 2 : Spot Light
    float3  WorldDir;      // World Space 에서 광원의 방향
    float3  WorldPos;     // World Space 에서 광원의 위치
    float   Range;          // Spot Light 또는 Point Light 인 경우 광원의 영향 범위
    float   Angle;          // Spot Light 인 경우 광원의 각도
    float3  Padding;       // 16 Byte 맞추기 위한 용도
};

// 파티클 정보
struct tParticle
{
    float3 vLocalPos;
    float3 vWorldPos;
    float3 vWorldScale;
    float4 vColor;
    float3 vVelocity;

    float Life;
    float Age;
    float NormalizedAge; // 현재 수명의 비율
    int Active;
};

#endif