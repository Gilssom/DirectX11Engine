#ifndef _PARTICLE_TICK
#define _PARTICLE_TICK

#include "value.fx"
#include "func.fx"

struct tSpawnCount
{
    int     spawnCount;
    uint3   padding;
};

struct tParticleModule
{
    // Spawn Module
    uint    vSpawnRate;     // �ʴ� ��ƼŬ ���� ����
    float4  vSpawnColor;    // ���� ���� ����
    float4  vSpawnMinScale; // ���� ��, �ּ� ũ��
    float4  vSpawnMaxScale; // ���� ��, �ִ� ũ��

    float   MinLife;        // ��ƼŬ �ּ� ����
    float   MaxLife;        // ��ƼŬ �ִ� ����

	// Module On / Off
    int     Module[1];
    
    float4 padding;
};

// Tick �� ȣ�� ���� Particle ���� Binding �� ��
RWStructuredBuffer<tParticle>   ParticleBuffer   : register(u0);
RWStructuredBuffer<tSpawnCount> SpawnCountBuffer : register(u1);
Texture2D                       NoiseTex         : register(t20);
StructuredBuffer<tParticleModule> Module         : register(t21);


// Particle Buffer �� ����
#define ParticleBufferSize  g_int_0

// Particle Object �� ��ġ
#define ParticleObjectPos   g_vec4_0

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
        if (Module[0].Module[0])
        {
            // �̹��� Ȱ��ȭ ������ ��ƼŬ �� üũ
            int CurSpawnCount = SpawnCount;
        
            // ��ƼŬ Ȱ��ȭ ���� ���ڰ� 0���� ũ��
            while (0 < CurSpawnCount)
            {
                // Spawn Count �� ����ִ� ���� ���� ����
                int OriginValue = 0;
            
                //InterlockedExchange(SpawnCount, SpawnCount - 1, OriginValue);
                // ��ü�� �õ��� ��, SpawnCount �� ����ִ� ���� ���� ���� ������ ��쿡�� ���� ��ü�Ѵ�.
                InterlockedCompareExchange(SpawnCount, CurSpawnCount, SpawnCount - 1, OriginValue);
            
                // ��ü�� ���� ���� �����ϴ� ���� ��ġ�ϸ� Ȱ��ȭ ����
                // ������ Thread �� �����ϸ� ���� Thread ���� �Ʒ� ���ǿ� ���� �� ����
                // ���� Ȱ��ȭ �õ� �ܰ�� ���� ���
                if (OriginValue == CurSpawnCount)
                {
                    // Random �Լ�ȭ
                    float3 vRandom = GetRandom(NoiseTex, _ID.x / (ParticleBufferSize - 1));
                    
                    // 300 * 300 * 300 �� �ڽ� ���� �ȿ� ���� �׽�Ʈ
                    float BoxScale = 300.f;
                    float3 vRandomPos = (float3) 0.f;
                    
                    vRandomPos.x = vRandom.x * BoxScale - (BoxScale / 2.f);
                    vRandomPos.y = vRandom.y * BoxScale - (BoxScale / 2.f);
                    vRandomPos.z = vRandom.z * BoxScale - (BoxScale / 2.f);
                    
                    Particle.vLocalPos = vRandomPos;
                    Particle.vWorldPos = Particle.vLocalPos + ParticleObjectPos.xyz;                   
                    
                    // Min ~ Max Random
                    Particle.vWorldScale = clamp(vRandom.x, Module[0].vSpawnMinScale, Module[0].vSpawnMaxScale);
                    
                    Particle.vColor = Module[0].vSpawnColor;
                    
                    Particle.Age = 0.f;
                    Particle.Life = clamp(vRandom.y, Module[0].MinLife, Module[0].MaxLife);
                    Particle.Active = 1;
                
                    break;
                }
            
                // �������� ���� Thread ���� Ȱ��ȭ ������ ��ƼŬ ���� ��üũ
                CurSpawnCount = SpawnCount;
            }
        }
    }
    else
    {
        // Global Data �� Binding_CS �� ���ؼ� �޾ƿ����� Ȱ��
        Particle.Age += DeltaTime;
        
        if(Particle.Life <= Particle.Age)
        {
            Particle.Active = 0;
        }
    }
}

#endif