// �ߺ� ��� ���� ���� ���� = #progma once
#ifndef _STD2D
#define _STD2D

#include "value.fx"

StructuredBuffer<float4> g_TestBuffer : register(t20);

// ���� ������ ���� ��ȭ�� �ʿ� ����.
// ��ü�� ��ǥ�� �������� �ȴ�.

// ������ ��� ������ �ʿ� ����.
// ���� ���� ������ �ʿ��� �����鸸 �������� �ȴ�. = Input Layout

struct VS_IN // �Է� Ÿ��
{
    float3 vPos : POSITION;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};


struct VS_OUT // ��ȯ Ÿ��
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
    
    float3 vWorldPos : POSITION;
};


VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    // ����� ���Ҷ� 3���� ��ǥ�� 4�������� Ȯ�� (������ǥ)
    
    // 1. ���� ��ġ�� ��ü�� ��ġ ��Ų��.
    float4 vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);
    
    // 2. ī�޶� ��ġ�� �������� View Space ��ǥ ���ġ
    //   ��� ��ü�� ī�޶� ������ �Ǵ� ��ǥ��� �� �Ѿ�´�.
    float4 vViewPos = mul(vWorldPos, g_matView);
    
    // 3. ���� ��ǥ�� �����ش�. ( ���� ��ǥ X )
    float4 vProjPos = mul(vViewPos, g_matProj);
    
    // 4. Rasterizer �ܰ迡�� ����� 4��° w ���� �˾Ƽ� ������ ���� ��ǥ�� ����� ���ش�.
    // ���� ���� ��ǥ�� ������ ������ؼ� �Ѱ��ְ� �� �ʿ䰡 ����.
    // ������ 1 �� ���� ������ ���� �״���� ���¸� �׸��� ���ؼ�.
    // ���� ����� ������ ��� ��ü�� ������ �ִ� ���´� ������ �� ���ٰ� �Ǵ�.
    // �׷��� ���ο��� w ���� �����ִ� �ý����� ������.
    output.vWorldPos = vWorldPos;
    output.vPosition = vProjPos;
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    return output;
}


float4 PS_Std2D(VS_OUT _in) : SV_Target // ��ȯ Ÿ��
{
    float4 vColor = (float4) 0.f;
    
    if (g_TestBuffer[0].w == 4.f)
        return float4(1.f, 0.f, 0.f, 1.f);
    
    if (UseAnim2D)
    {
        float2 vBackGroundLeftTop = vLeftTop - ((vBackGround - vSliceSize) * 0.5f);
        float2 vUV = (vBackGroundLeftTop + _in.vUV * vBackGround) - vOffset;
        
        if(vUV.x < vLeftTop.x || vUV.x > vSliceSize.x + vLeftTop.x
            || vUV.y < vLeftTop.y || vUV.y > vSliceSize.y + vLeftTop.y)
        {
            // �ش� ������ ����
            discard;
        }
        else
        {
            vColor = g_Atlas.Sample(g_sam_0, vUV);
        }
    }
    else
    {
        // ���ø� ( �� �ȼ������� ������ �����;��� )
        vColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    }
    
    // ==================
    // ���� ó��
    float3 vLightPower = (float3) 0.f;
    
    // Directional Light
    if(g_Light2D[0].LightType == 0)
    {
        vLightPower = g_Light2D[0].Light.vDiffuse.rgb + g_Light2D[0].Light.vAmbient.rgb;
    }
    
    // Point Light
    else if (g_Light2D[0].LightType == 1)
    {
        // Pixel World Space
        float fDist = distance(g_Light2D[0].WorldPos.xy, _in.vWorldPos.xy);
        
        if (fDist < g_Light2D[0].Range)
        {
            vLightPower = g_Light2D[0].Light.vDiffuse;
        }
    }
    
    // Spot Light
    else
    {
        
    }
    
    vColor.rgb *= vLightPower;
    
    // ===================
    // ���� ������ �� Color
    // �� ������ Color ���� ��� �ֱ� ������
    // ����ġ ���� ������ �� �ȼ� ������ ���� ���� �����ش�. ( Rasterize Stage )
    return vColor;
}

#endif