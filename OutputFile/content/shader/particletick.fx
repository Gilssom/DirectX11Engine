#ifndef _PARTICLE_TICK
#define _PARTICLE_TICK

#include "value.fx"

// 유연하게 개수에 대처하기 위해서 적당히 32개만
[numthreads(32, 1, 1)]
void CS_ParticleTick(int3 _ID : SV_DispatchThreadID)
{
    
}


#endif