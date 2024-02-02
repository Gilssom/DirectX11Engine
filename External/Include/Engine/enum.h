#pragma once


enum class ASSET_TYPE
{
	PREFAB,
	MESH,
	MESH_DATA,
	MATERIAL,
	TEXTURE,
	SOUND,
	GRAPHICS_SHADER,
	COMPUTE_SHADER,

	END,
};

// 상수 버퍼 갯수는 거의 고정적임
enum class CB_TYPE
{
	TRANSFORM,

	MATERIAL,

	ANIMATION,

	GLOBAL,

	END,
};