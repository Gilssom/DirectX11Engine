#pragma once


template<typename T>
class Ptr
{
private:
	T* m_Asset;


public:
	// ���� �����ڷ� ��ü�� �ϸ� �ȵǴ� ����
	// �� ������ ���𰡸� ����Ű�� ���� ���� �ִ�.
	void operator = (T* asset)
	{
		if (m_Asset != nullptr)
			m_Asset->Release();

		m_Asset = asset;
		
		if (m_Asset != nullptr)
			m_Asset->AddRef();
	}

	// �ڽŰ� ���� �༮�� ���� ���� �ִ�.
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