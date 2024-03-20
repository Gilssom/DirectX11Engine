#ifndef _STRUCT
#define _STRUCT

// ���� ���� ����ü
struct tLight
{
    float4 vDiffuse;        // ���ݻ� (���� ����)
    float4 vAmbient;        // ȯ�汤 (������ �߻��ϴ� �ּ����� ���)
    float4 vMaxSpecular;    // �ݻ籤 (������ �߻��ϴ� �ݻ籤�� �ִ� ���)
};

// ���� ����
struct tLightInfo
{
    tLight  Light;          // ���� ���� ����

    uint    LightType;      // 0 : Directional Light | 1 : Point Light | 2 : Spot Light
    float3  WorldDir;      // World Space ���� ������ ����
    float3  WorldPos;     // World Space ���� ������ ��ġ
    float   Range;          // Spot Light �Ǵ� Point Light �� ��� ������ ���� ����
    float   Angle;          // Spot Light �� ��� ������ ����
    float3  Padding;       // 16 Byte ���߱� ���� �뵵
};

// ��ƼŬ ����
struct tParticle
{
    float3 vLocalPos;
    float3 vWorldPos;
    float3 vWorldScale;
    float4 vColor;
    float3 vVelocity;

    float Life;
    float Age;
    float NormalizedAge; // ���� ������ ����
    int Active;
};

#endif