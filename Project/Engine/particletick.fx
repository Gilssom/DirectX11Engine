#ifndef _PARTICLE_TICK
#define _PARTICLE_TICK

#include "value.fx"

struct tSpawnCount
{
    uint spawnCount;
    uint3 padding;
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
    // Thread ID == Particle Index
    // Thread ID 가 Particle 개수를 초과하면 return
    if (ParticleBufferSize <= _ID.x)
        return;
    
    // n개의 Thread 를 순차적으로 수행하도록 해주는 함수
    // 이 방법도 문제가 있다. 값을 확인하는 동안 다음 Thread 가 갑자기 들어올 수도 있기 때문
    // 그 문제의 해결 방안은 InterlockedExchange 함수 활용 (다른 Thread 의 영향을 받지 않고 값 확인이 가능)
    InterlockedAdd(SpawnCount, 1);
    
    //InterlockedExchange();
    
    // 비활성화된 파티클을 활성화 시켜야함
    //if (SpawnCount > 0 && !Particle.Active)
    //{
    //    SpawnCount -= 1;
        
    //    Particle.Active = 1;
    //}
    
    //// Thread 간의 동기화가 필요함
    //// 1. 병렬 처리 이기 때문에 Count 가 1씩 감소하는 것이 아니라 
    ////   전체가 한번에 동작하기 때문에 먹히지가 않음
    //// 2. 그리고 랜덤값도 먹히지가 않음 (동시에 병렬처리로 하기 때문에 같은 랜덤값을 가지게 됨)
    
    //// 위의 기능을 제공하는 함수가 내부에 존재함
    
    //if(Particle.Active)
    //{
    //    // Global Data 를 Binding_CS 를 통해서 받아왔으니 활용
    //    Particle.vWorldPos.y += DeltaTime * 100.f;
    //}
}

#endif