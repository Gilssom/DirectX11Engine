#pragma once
#include "Singletone.h"
class CTimeManager : public CSingleton<CTimeManager>
{
    SINGLE(CTimeManager)

private:
    LARGE_INTEGER m_llFrequency;    // �ʴ� ī��Ʈ ��
    LARGE_INTEGER m_llCurCount;     // ���� ī��Ʈ ��
    LARGE_INTEGER m_llPrevCount;    // ���� ������ ī��Ʈ ��

    float m_DT;                     // Delta Time : 1 Frame ���� �ϴµ� �ɸ� �ð�
    float m_Time;                   // ���μ��� ���� ���� ���� �ð�
    float m_AccTime;                // 1�ʸ� üũ�ϱ� ���� �ð� ���� ����

    UINT m_FrameCount;
public:
    void Init();
    void Tick();
};

