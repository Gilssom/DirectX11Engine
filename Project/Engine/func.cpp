#include "pch.h"

#include "CDbgRenderManager.h"
#include "CTaskManager.h"

#include "CGameObject.h"

// ������Ʈ ���� �Լ�
void SpawnObject(int layerIdx, CGameObject* object)
{
	tTask task = {};
	task.Type = TASK_TYPE::SPAWN_OBJECT;
	task.dwParam_0 = layerIdx;
	task.dwParam_1 = (DWORD_PTR)object;

	CTaskManager::GetInst()->AddTask(task);
}

// ������Ʈ ��ȿ�� üũ
bool IsValid(CGameObject*& object)
{
	// Ȥ�� �ش� ������Ʈ �ּҰ� null ����
	if (object == nullptr)
	{
		return false;
	}
	// �ƴϸ� �ش� ������Ʈ�� ���� ��������
	else if (object->IsDead())
	{
		object = nullptr;
		return false;
	}
	// �װ͵� �ƴ϶�� �ش� ������Ʈ�� ���� �����Ѵ�.
	else
	{
		return true;
	}
}

// �� ������ ���� �Լ�
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

// ��� ���� �Լ�
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

void DrawDebugCircle(Vec3 worldPos, float radius, Vec4 vColor, float duration)
{
	tDebugShapeInfo info = {};
	info.Shape = DEBUG_SHAPE::CIRCLE;

	info.Position = worldPos;
	info.Scale = Vec3(radius * 2.f, radius * 2.f, 1.f);
	info.matWorld = XMMatrixIdentity();

	info.Color = vColor;

	info.Duration = duration;
	info.Age = 0.f;

	CDbgRenderManager::GetInst()->AddDebugShapeInfo(info);
}

void SaveWString(const wstring& str, FILE* file)
{
	size_t len = str.length();
	fwrite(&len, sizeof(size_t), 1, file);
	fwrite(str.c_str(), sizeof(wchar_t), len, file);
}

void LoadWString(wstring& str, FILE* file)
{
	//wchar_t szBuffer[256] = {};

	size_t len = 0;
	fread(&len, sizeof(size_t), 1, file);

	str.resize(len);

	fread((wchar_t*)str.c_str(), sizeof(wchar_t), len, file);
}