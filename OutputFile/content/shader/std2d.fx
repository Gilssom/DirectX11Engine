// �ߺ� ��� ���� ���� ���� = #progma once
#ifndef _STD2D
#define _STD2D


// ���� ������ ���� ��ȭ�� �ʿ� ����.
// ��ü�� ��ǥ�� �������� �ȴ�.

cbuffer TRANSFORM : register(b0)
{
    float4 g_Position;
    float g_Scale;
};

// ������ ��� ������ �ʿ� ����.
// ���� ���� ������ �ʿ��� �����鸸 �������� �ȴ�. = Input Layout

struct VS_IN // �Է� Ÿ��
{
    float3 vPos : POSITION;
    float4 vColor : COLOR;
};


struct VS_OUT // ��ȯ Ÿ��
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
};


VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = float4(_in.vPos + g_Position.xyz, 1.f);
    output.vColor = _in.vColor;
    
    return output;
}


float4 PS_Std2D(VS_OUT _in) : SV_Target // ��ȯ Ÿ��
{
    // ���� ������ �� Color
    // �� ������ Color ���� ��� �ֱ� ������
    // ����ġ ���� ������ �� �ȼ� ������ ���� ���� �����ش�. ( Rasterize Stage )
    return _in.vColor;
}


#endif