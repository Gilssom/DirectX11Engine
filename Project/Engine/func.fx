#ifndef _FUNC
#define _FUNC

#include "value.fx"


float3 CalLight2D(int lightIdx, float3 vWorldPos)
{
    // ==================
    // 광원 처리
    // ==================
    
    tLightInfo info = g_Light2D[lightIdx];
   
    float3 vLightPower = (float3) 0.f;
    
    // Directional Light
    if (info.LightType == 0)
    {
        vLightPower = info.Light.vDiffuse.rgb + info.Light.vAmbient.rgb;
    }
    
    // Point Light
    else if (info.LightType == 1)
    {
        // Pixel World Space
        float fDist = distance(info.WorldPos.xy, vWorldPos.xy);
        
        float fRatio = 0.f;
        
        // 거리에 따른 기준치
        if(g_int_1)
        {
            // saturate : 음수는 0 , 1을 초과하면 1로 맞춰준다
            // 일정한 비율로 떨어지는 선형 방식
            fRatio = 1.f - saturate(fDist / info.Range);
        }
        else
        {
            // cos 그래프를 활용한 거리에 따른 기준치
            // 멀어질 수록 급격하게 Light Power 가 낮아짐
            fRatio = cos((fDist / info.Range) * (PI / 2.f));
        }
        
        if (fDist < info.Range)
        {
            vLightPower = info.Light.vDiffuse * fRatio;
        }
    }
    
    // Spot Light (과제 예정)
    else
    {
        
    }
    
    return vLightPower;
}

#endif