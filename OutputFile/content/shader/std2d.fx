// �ߺ� ��� ���� ���� ���� = #progma once
#ifndef _STD2D
#define _STD2D

#include "value.fx"

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
    output.vPosition = vProjPos;
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    
    return output;
}


float4 PS_Std2D(VS_OUT _in) : SV_Target // ��ȯ Ÿ��
{
    float4 vColor = (float4) 0.f;
    
    // Material ���� �Ѱܹ��� ����� ���� �бⰡ ����
    if(g_int_0 == 0)
    {
        // ���ø� ( �� �ȼ������� ������ �����;��� )
        vColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    }
    else if(g_vec4_3.y == 3.14f)
    {
        vColor = float4(1.f, 1.f, 0.f, 1.f);
    }
    else if (g_mat_1[3][3] == 2.1f)
    {
        vColor = float4(0.f, 1.f, 0.f, 1.f);
    }
    
    // ���� ������ �� Color
    // �� ������ Color ���� ��� �ֱ� ������
    // ����ġ ���� ������ �� �ȼ� ������ ���� ���� �����ش�. ( Rasterize Stage )
    return vColor;
}


#endif