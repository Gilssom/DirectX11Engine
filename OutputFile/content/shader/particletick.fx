#ifndef _PARTICLE_TICK
#define _PARTICLE_TICK

#include "value.fx"

struct tSpawnCount
{
    uint spawnCount;
    uint3 padding;
};

// Tick �� ȣ�� ���� Particle ���� Binding �� ��
RWStructuredBuffer<tParticle>   ParticleBuffer   : register(u0);
RWStructuredBuffer<tSpawnCount> SpawnCountBuffer : register(u1);


// Particle Buffer �� ����
#define ParticleBufferSize  g_int_0

// Particle Tick Buffer ����
#define Particle            ParticleBuffer[_ID.x]

// Spawn Count Buffer ����
#define SpawnCount          SpawnCountBuffer[0].spawnCount


// �����ϰ� ������ ��ó�ϱ� ���ؼ� ������ 32����
[numthreads(32, 1, 1)]
void CS_ParticleTick(int3 _ID : SV_DispatchThreadID)
{
    // Thread ID == Particle Index
    // Thread ID �� Particle ������ �ʰ��ϸ� return
    if (ParticleBufferSize <= _ID.x)
        return;
    
    // n���� Thread �� ���������� �����ϵ��� ���ִ� �Լ�
    // �� ����� ������ �ִ�. ���� Ȯ���ϴ� ���� ���� Thread �� ���ڱ� ���� ���� �ֱ� ����
    // �� ������ �ذ� ����� InterlockedExchange �Լ� Ȱ�� (�ٸ� Thread �� ������ ���� �ʰ� �� Ȯ���� ����)
    InterlockedAdd(SpawnCount, 1);
    
    //InterlockedExchange();
    
    // ��Ȱ��ȭ�� ��ƼŬ�� Ȱ��ȭ ���Ѿ���
    //if (SpawnCount > 0 && !Particle.Active)
    //{
    //    SpawnCount -= 1;
        
    //    Particle.Active = 1;
    //}
    
    //// Thread ���� ����ȭ�� �ʿ���
    //// 1. ���� ó�� �̱� ������ Count �� 1�� �����ϴ� ���� �ƴ϶� 
    ////   ��ü�� �ѹ��� �����ϱ� ������ �������� ����
    //// 2. �׸��� �������� �������� ���� (���ÿ� ����ó���� �ϱ� ������ ���� �������� ������ ��)
    
    //// ���� ����� �����ϴ� �Լ��� ���ο� ������
    
    //if(Particle.Active)
    //{
    //    // Global Data �� Binding_CS �� ���ؼ� �޾ƿ����� Ȱ��
    //    Particle.vWorldPos.y += DeltaTime * 100.f;
    //}
}

#endif