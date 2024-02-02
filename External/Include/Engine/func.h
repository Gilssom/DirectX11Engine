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