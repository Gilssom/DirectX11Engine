#pragma once
#include "Singletone.h"
class CTimeManager : public CSingleton<CTimeManager>
{
    SINGLE(CTimeManager)

private:
    LARGE_INTEGER m_llFrequency;    // 초당 카운트 수
    LARGE_INTEGER m_llCurCount;     // 현재 카운트 수
    LARGE_INTEGER m_llPrevCount;    // 이전 프레임 카운트 수

    float m_DT;                     // Delta Time : 1 Frame 동작 하는데 걸린 시간
    float m_Time;                   // 프로세스 실행 이후 누적 시간
    float m_AccTime;                // 1초를 체크하기 위한 시간 누적 변수

    UINT m_FrameCount;
public:
    void Init();
    void Tick();
};

