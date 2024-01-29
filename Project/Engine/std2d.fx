// �ߺ� ��� ���� ���� ���� = #progma once
#ifndef _STD2D
#define _STD2D

// ������ ��� ������ �ʿ� ����.
// ���� ���� ������ �ʿ��� �����鸸 �������� �ȴ�. = Input Layout

struct VS_IN // �Է� Ÿ��
{
    float3 vPos : POSITION;
    //float4 vColor : COLOR;
};

struct VS_OUT // ��ȯ Ÿ��
{
    float4 vPosition : SV_Position;
};

VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = float4(_in.vPos, 1.f);
    
    return output;
}


#endif