#pragma once


void DrawDebugRect(Vec3 worldPos, Vec3 worldScale, Vec3 worldRotation, Vec4 vColor, float duration);
void DrawDebugRect(Matrix matWorld, Vec4 vColor, float duration);

void DrawDebugCircle(Vec3 worldPos, float radius, Vec4 vColor, float duration);

void DrawDebugLine();


template<typename T, int size>
void Safe_Del_Array(T* (&Array)[size])
{
	for (int i = 0; i < size; ++i)
	{
		if (Array[i] != nullptr)
		{
			delete Array[i];
			Array[i] = nullptr;
		}
	}
}

template<typename T>
void Safe_Del_Vector(vector<T*> vector)
{
	for (size_t i = 0; i < vector.size(); ++i)
	{
		delete vector[i];
		vector[i] = nullptr;
	}

	vector.clear();
}

template<typename T1, typename T2>
void Safe_Del_Map(map<T1, T2>& map)
{
	for (const auto& pair : map)
	{
		if (pair.second != nullptr)
			delete pair.second;
	}

	map.clear();
}