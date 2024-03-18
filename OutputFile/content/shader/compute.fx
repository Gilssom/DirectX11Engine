#ifndef _COMPUTE
#define _COMPUTE


// thread ���� ��� (HLSL 5.0 ver Max = 1,024)
// 3���� ���� ���� ��� ex) 2, 2, 2 = 8�� / Max = 32, 32, 1 or 1024, 1, 1
// = Group �� Thread ����

// int  SV_GroupIndex        : �׷� �������� Thread 1���� ��ǥ
// int3 SV_GroupThreadID     : �׷� �������� Thread 3���� ��ǥ
// int3 SV_GroupID           : Thread�� ���� �׷��� 3���� ��ǥ
// int3 SV_DispatchThreadID  : ��� �׷� ������, ��, ��ü ���� 3���� ��ǥ (Pixel ��ǥ�� ��ȯ�ؼ� ����� �� �ִ�.)

// �б⸸ ����
//Texture2D TargetTex : register(t21);

// �б� �� ���� ���� (register �� u �� ����) = unordered register
RWTexture2D<float4> TargetTex : register(u0);


[numthreads(32, 32, 1)]
void CS_Test(int3 _ThreadID : SV_DispatchThreadID)
{
    TargetTex[_ThreadID.xy] = float4(1.f, 0.f, 0.f, 1.f);
}


#endif