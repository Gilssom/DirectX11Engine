#ifndef _PARTICLE
#define _PARTICLE

#include "value.fx"

StructuredBuffer<tParticle> ParticleBuffer : register(t17);


struct VS_PARTICLE_IN
{
    float3 vPos     : POSITION;
    float2 vUV      : TEXCOORD;
    uint   InstID   : SV_InstanceID; // Instance ����� ID
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


// Geometry Shader : ���� �߰� ���� ����
// SV_Position �� ���� Geometry ���� �޾ƾ��Ѵ�. (������ �ٷ� Rasterizer - NDC ��ǥ��)
// �������� �� ������ Geometry Shader -> outStream ���ٰ� �Ѱ�ٰ� Rasterizer �� �ѱ�� ����
// ���� outStream �� ������ �ѱ��� ������ ���� �������� �������� ������ �״�� �ߴܵǹ���. (������ ���� ������)
// ���ʿ��� �ܰ谡 ���� ��� outStream �� ������ �ѱ����� ������ �ȴ�.

// Bill Board ó��
// ���� �ϳ��� �޾ƿͼ� Ȱ���ϰ� �Ǹ� �ش� ������ �������� �����̴ϱ�
// �ش� ������ ���ؼ� Ȯ����Ѽ� Mesh �� �׸��� ���ϴ�. (ī�޶� ȸ���� �ص�) ( ex) ����Ʈ�� ȸ���Ǹ� �ȵȴ�.)
// ������ ���� ȸ�� ��� ����� �ʿ���Ե�.

struct GS_OUT
{
    float4 vPosition    : SV_Position;
    float2 vUV          : TEXCOORD;
    uint InstID         : FOG;
};

// ���� ��� �ִ� ����
[maxvertexcount(6)] // inout : Reference (HLSL ����)
void GS_Particle(point VS_PARTICLE_OUT _in[1], inout TriangleStream<GS_OUT> _OutStream)
{
    GS_OUT output = (GS_OUT) 0.f;
    
    // ���ڸ����� Scale ���� ��, ��ƼŬ ������ ��ġ�� �̵�
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