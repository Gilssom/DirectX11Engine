#include "pch.h"

#include "CDbgRenderManager.h"

// 각 포지션 정보 함수
void DrawDebugRect(Vec3 worldPos, Vec3 worldScale, Vec3 worldRotation, Vec4 vColor, float duration)
{
	tDebugShapeInfo info = {};
	info.Shape = DEBUG_SHAPE::RECT;

	info.Position = worldPos;
	info.Scale = worldScale;
	info.Rotation = worldRotation;
	info.matWorld = XMMatrixIdentity();

	info.Color = vColor;

	info.Duration = duration;
	info.Age = 0.f;

	CDbgRenderManager::GetInst()->AddDebugShapeInfo(info);
}

// 행렬 정보 함수
void DrawDebugRect(Matrix matWorld, Vec4 vColor, float duration)
{
	tDebugShapeInfo info = {};
	info.Shape = DEBUG_SHAPE::RECT;
	info.matWorld = matWorld;

	info.Color = vColor;

	info.Duration = duration;
	info.Age = 0.f;

	CDbgRenderManager::GetInst()->AddDebugShapeInfo(info);
}
