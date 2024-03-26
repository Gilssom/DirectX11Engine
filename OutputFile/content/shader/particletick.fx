#ifndef _PARTICLE_TICK
#define _PARTICLE_TICK

#include "value.fx"

struct tSpawnCount
{
    int     spawnCount;
    uint3   padding;
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
    // Thread ���� ����ȭ�� �ʿ���
    // 1. ���� ó�� �̱� ������ Count �� 1�� �����ϴ� ���� �ƴ϶� 
    //   ��ü�� �ѹ��� �����ϱ� ������ �������� ����
    // 2. �׸��� �������� �������� ���� (���ÿ� ����ó���� �ϱ� ������ ���� �������� ������ ��)
    // ���� ����� �����ϴ� �Լ��� ���ο� ������
    
    // Thread ID == Particle Index
    // Thread ID �� Particle ������ �ʰ��ϸ� return
    if (ParticleBufferSize <= _ID.x)
        return;
    
    // InterlockedExchange �� �������� �ִ�.
    // �ϳ� �ϳ��� �� ���ϸ鼭 �����ϴ°� �´µ�
    // ��ΰ� 1ȸ��, 2ȸ�� ... nȸ���� �� �Բ� �����ϴ°� �ƴ� ���� �ִ�.(n�� �������� ������ ���� ���ɼ� ���)
    // �׷��� ���߿� ����Ǵ� Interlocked Thread �� ���� ����ִ� ������ �����Ű�� ������ �߻�
    
    // InterlockedCompareExchange
    // dest ���� compare value �� �ѹ� �� �񱳸� �ؼ� ���� ���� ������ �߻��� �� ���� ����
    // ��������� nȸ���� ù �õ��ϴ� Thread �� ����� �ϰ� �ȴ�. 
    // (�� ������ �̷������ ���� Compare ������ ����� �ȵ�)
    
    //��Ȱ��ȭ�� ��ƼŬ�� Ȱ��ȭ ���Ѿ���
    if (Particle.Active == 0)
    {
        // �̹��� Ȱ��ȭ ������ ��ƼŬ �� üũ
        int CurSpawnCount = SpawnCount;
        
        // ��ƼŬ Ȱ��ȭ ���� ���ڰ� 0���� ũ��
        while (0 < CurSpawnCount)
        {
            // Spawn Count �� ����ִ� ���� ���� ����
            int OriginValue = 0;
            
            // ��ü�� �õ��� ��, SpawnCount �� ����ִ� ���� ���� ���� ������ ��쿡�� ���� ��ü�Ѵ�.
            InterlockedCompareExchange(SpawnCount, CurSpawnCount, SpawnCount - 1, OriginValue);
            
            // ��ü�� ���� ���� �����ϴ� ���� ��ġ�ϸ� Ȱ��ȭ ����
            // ������ Thread �� �����ϸ� ���� Thread ���� �Ʒ� ���ǿ� ���� �� ����
            // ���� Ȱ��ȭ �õ� �ܰ�� ���� ���
            if (OriginValue == CurSpawnCount)
            {
                Particle.Active = 1;
                
                // ��ƼŬ�� �������� Random Position ���� ����
                float2 vUV = (float2) 0.f;
                vUV.x = _ID.x / (ParticleBufferSize - 1); // 0 ~ 1 ����ȭ
                
                
                
                break;
            }
            
            // �������� ���� Thread ���� Ȱ��ȭ ������ ��ƼŬ ���� ��üũ
            CurSpawnCount = SpawnCount;
        }
    }
    else
    {
        // Global Data �� Binding_CS �� ���ؼ� �޾ƿ����� Ȱ��
        Particle.vWorldPos.y += DeltaTime * 100.f;
    }
}

#endif