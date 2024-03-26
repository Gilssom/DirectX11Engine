#ifndef _PARTICLE_TICK
#define _PARTICLE_TICK

#include "value.fx"

struct tSpawnCount
{
    int     spawnCount;
    uint3   padding;
};

// Tick 을 호출 받을 Particle 들이 Binding 될 곳
RWStructuredBuffer<tParticle>   ParticleBuffer   : register(u0);
RWStructuredBuffer<tSpawnCount> SpawnCountBuffer : register(u1);


// Particle Buffer 의 개수
#define ParticleBufferSize  g_int_0

// Particle Tick Buffer 접근
#define Particle            ParticleBuffer[_ID.x]

// Spawn Count Buffer 접근
#define SpawnCount          SpawnCountBuffer[0].spawnCount


// 유연하게 개수에 대처하기 위해서 적당히 32개만
[numthreads(32, 1, 1)]
void CS_ParticleTick(int3 _ID : SV_DispatchThreadID)
{
    // Thread 간의 동기화가 필요함
    // 1. 병렬 처리 이기 때문에 Count 가 1씩 감소하는 것이 아니라 
    //   전체가 한번에 동작하기 때문에 먹히지가 않음
    // 2. 그리고 랜덤값도 먹히지가 않음 (동시에 병렬처리로 하기 때문에 같은 랜덤값을 가지게 됨)
    // 위의 기능을 제공하는 함수가 내부에 존재함
    
    // Thread ID == Particle Index
    // Thread ID 가 Particle 개수를 초과하면 return
    if (ParticleBufferSize <= _ID.x)
        return;
    
    // InterlockedExchange 도 문제점이 있다.
    // 하나 하나씩 값 비교하면서 실행하는건 맞는데
    // 모두가 1회차, 2회차 ... n회차를 다 함께 실행하는게 아닐 수도 있다.(n이 높을수록 문제가 생길 가능성 상승)
    // 그래서 나중에 실행되는 Interlocked Thread 가 값을 들고있는 값으로 변경시키는 현상이 발생
    
    // InterlockedCompareExchange
    // dest 값과 compare value 를 한번 더 비교를 해서 위와 같은 문제가 발생할 수 없게 방지
    // 평균적으로 n회차의 첫 시도하는 Thread 만 통과를 하게 된다. 
    // (값 변경이 이루어지니 뒤의 Compare 조건이 통과가 안됨)
    
    //비활성화된 파티클을 활성화 시켜야함
    if (Particle.Active == 0)
    {
        // 이번에 활성화 가능한 파티클 수 체크
        int CurSpawnCount = SpawnCount;
        
        // 파티클 활성화 가능 숫자가 0보다 크면
        while (0 < CurSpawnCount)
        {
            // Spawn Count 에 들어있던 값을 받을 변수
            int OriginValue = 0;
            
            // 교체를 시도할 때, SpawnCount 에 들어있는 값이 예상 값과 동일한 경우에만 값을 교체한다.
            InterlockedCompareExchange(SpawnCount, CurSpawnCount, SpawnCount - 1, OriginValue);
            
            // 교체한 값이 원래 예상하던 값과 일치하면 활성화 성공
            // 진입한 Thread 가 존재하면 다음 Thread 들은 아래 조건에 들어올 수 없음
            // 다음 활성화 시도 단계로 진입 대기
            if (OriginValue == CurSpawnCount)
            {
                Particle.Active = 1;
                
                // 파티클의 포지션을 Random Position 으로 지정
                float2 vUV = (float2) 0.f;
                vUV.x = _ID.x / (ParticleBufferSize - 1); // 0 ~ 1 정규화
                
                
                
                break;
            }
            
            // 진입하지 못한 Thread 들은 활성화 가능한 파티클 수를 재체크
            CurSpawnCount = SpawnCount;
        }
    }
    else
    {
        // Global Data 를 Binding_CS 를 통해서 받아왔으니 활용
        Particle.vWorldPos.y += DeltaTime * 100.f;
    }
}

#endif