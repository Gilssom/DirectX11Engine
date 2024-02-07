#pragma once


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