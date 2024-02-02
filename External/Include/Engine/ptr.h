#pragma once


template<typename T>
class Ptr
{
private:
	T* m_Asset;


public:
	// 복사 생성자로 대체를 하면 안되는 이유
	// 그 이전에 무언가를 가르키고 있을 수도 있다.
	void operator = (T* asset)
	{
		if (m_Asset != nullptr)
			m_Asset->Release();

		m_Asset = asset;
		
		if (m_Asset != nullptr)
			m_Asset->AddRef();
	}

	// 자신과 같은 녀석을 받을 수도 있다.
	void operator = (const Ptr<T>& other)
	{
		if (m_Asset != nullptr)
			m_Asset->Release();

		m_Asset = other.m_Asset;

		if (m_Asset != nullptr)
			m_Asset->AddRef();
	}

	T* operator -> ()
	{
		return m_Asset;
	}

public:
	Ptr()
		: m_Asset(nullptr)
	{

	}

	Ptr(T* asset)
		: m_Asset(asset)
	{
		if (m_Asset != nullptr)
			m_Asset->AddRef();
	}

	Ptr(const Ptr<T>& other)
		: m_Asset(other.m_Asset)
	{
		if (m_Asset != nullptr)
			m_Asset->AddRef();
	}

	~Ptr()
	{
		if (m_Asset != nullptr)
			m_Asset->Release();
	}
};