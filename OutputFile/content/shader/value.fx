#ifndef _VALUE
#define _VALUE

#include "struct.fx"

cbuffer TRANSFORM : register(b0)
{
    // 행으로 읽을 수 있게
    row_major matrix g_matWorld;
    row_major matrix g_matView;
    row_major matrix g_matProj;
};

cbuffer MATERIAL_CONST : register(b1)
{
    // 배열은 메모리 접근에 문제가 생긴다.
    int     g_int_0;
    int     g_int_1;
    int     g_int_2;
    int     g_int_3;
    
    float   g_float_0;
    float   g_float_1;
    float   g_float_2;
    float   g_float_3;
    
    float2  g_vec2_0;
    float2  g_vec2_1;
    float2  g_vec2_2;
    float2  g_vec2_3;
    
    float4  g_vec4_0;
    float4  g_vec4_1;
    float4  g_vec4_2;
    float4  g_vec4_3;
    
    row_major Matrix  g_mat_0;
    row_major Matrix g_mat_1;
    row_major Matrix g_mat_2;
    row_major Matrix g_mat_3;
};


cbuffer ANIMATION2D : register(b2)
{
    float2  vLeftTop;
    float2  vSliceSize;
    float2  vOffset;
    float2  vBackGround;
    int     UseAnim2D;
    int3    padding;
};


SamplerState g_sam_0 : register(s0);
SamplerState g_sam_1 : register(s1);

Texture2D       g_tex_0     : register(t0);
Texture2D       g_tex_1     : register(t1);
Texture2D       g_tex_2     : register(t2);
Texture2D       g_tex_3     : register(t3);
Texture2D       g_tex_4     : register(t4);
Texture2D       g_tex_5     : register(t5);

TextureCube     g_texcube_0 : register(t6);
TextureCube     g_texcube_1 : register(t7);
TextureCube     g_texcube_2 : register(t8);
TextureCube     g_texcube_3 : register(t9);

Texture2DArray  g_texarr_0  : register(t10);
Texture2DArray  g_texarr_1  : register(t11);
Texture2DArray  g_texarr_2  : register(t12);
Texture2DArray  g_texarr_3  : register(t13);

// Animation Atlas 바인딩
Texture2D       g_Atlas     : register(t14);


// Light2DInfo
StructuredBuffer<tLightInfo> g_Light2D : register(t15);

// Light3DInfo
StructuredBuffer<tLightInfo> g_Light3D : register(t16);

#endif