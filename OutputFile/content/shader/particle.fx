#ifndef _PARTICLE
#define _PARTICLE

#include "value.fx"

StructuredBuffer<tParticle> ParticleBuffer : register(t17);


struct VS_PARTICLE_IN
{
    float3 vPos     : POSITION;
    float2 vUV      : TEXCOORD;
    uint   InstID   : SV_InstanceID; // Instance 대상의 ID
};

struct VS_PARTICLE_OUT
{
    float3 vPos     : POSITION;
    float2 vUV      : TEXCOORD;
    uint InstID     : FOG;
};

VS_PARTICLE_OUT VS_Particle(VS_PARTICLE_IN _in)
{
    VS_PARTICLE_OUT output = (VS_PARTICLE_OUT) 0.f;
    
    output.vPos = _in.vPos;
    output.vUV = _in.vUV;
    output.InstID = _in.InstID;
    
    return output;
}


// Geometry Shader : 정점 추가 생성 가능
// SV_Position 을 이제 Geometry 에서 받아야한다. (원래는 바로 Rasterizer - NDC 좌표계)
// 정점에서 온 정보를 Geometry Shader -> outStream 에다가 넘겼다가 Rasterizer 에 넘기는 구조
// 만약 outStream 에 정보를 넘기지 않으면 최종 정보들이 없어지기 때문에 그대로 중단되버림. (정점이 없기 때문에)
// 불필요한 단계가 있을 경우 outStream 에 정보를 넘기지만 않으면 된다.

// Bill Board 처리
// 정점 하나를 받아와서 활용하게 되면 해당 정점이 원점이자 중점이니까
// 해당 정점을 통해서 확장시켜서 Mesh 를 그리면 편하다. (카메라가 회전을 해도) ( ex) 이펙트가 회전되면 안된다.)
// 복잡한 월드 회전 행렬 계산이 필요없게됨.

struct GS_OUT
{
    float4 vPosition    : SV_Position;
    float2 vUV          : TEXCOORD;
    uint InstID         : FOG;
};

// 정점 사용 최대 개수
[maxvertexcount(6)] // inout : Reference (HLSL 원본)
void GS_Particle(point VS_PARTICLE_OUT _in[1], inout TriangleStream<GS_OUT> _OutStream)
{
    GS_OUT output = (GS_OUT) 0.f;
    
    // 제자리에서 Scale 조절 후, 파티클 입자의 위치로 이동
    //float3 vWorldPos = (_in.vPos * ParticleBuffer[_in.InstID].vWorldScale) + ParticleBuffer[_in.InstID].vWorldPos;
    //float4 vViewPos = mul(float4(vWorldPos, 1.f), g_matView);
    //float4 vProjPos = mul(vViewPos, g_matProj);
}


float4 PS_Particle(GS_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
    
    if (ParticleBuffer[_in.InstID].Active == 0)
    {
        discard;
    }
    
    vOutColor = float4(1.f, 0.f, 0.f, 1.f);
    
    return vOutColor;
}

#endif