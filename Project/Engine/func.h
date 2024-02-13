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
<<<<<<< Updated upstream
=======
<<<<<<< HEAD
void Safe_Del_Vector(vector<T*>& vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		if (nullptr != vec[i])
			delete vec[i];
	}

	vec.clear();
=======
>>>>>>> Stashed changes
void Safe_Del_Vector(vector<T*> vector)
{
	for (size_t i = 0; i < vector.size(); ++i)
	{
		delete vector[i];
		vector[i] = nullptr;
	}

	vector.clear();
<<<<<<< Updated upstream
=======
>>>>>>> a41b0ec58dbec60568cd283e74472e1a6b6b4fa3
>>>>>>> Stashed changes
}