#pragma once

// ������ ���� �޸� : ���� ����
// ���μ��� ������ �� �ʱ�ȭ
// ���μ��� ���� �� ����
// ���μ����� ���� ���� ��� �����Ǵ� �޸�

//class CEngine
//{
//private:
//	// ��ü�� �� Ʋ� �ϳ���
//	static CEngine* m_This;
//
//public:
//	// ���� ����Լ� : ��ü�� ��� ȣ�� ����
//	static CEngine* GetInst() // �̱��� ����
//	{
//		// ���� ����Լ����� ������ �� �ִ� ������ ���� ����
//		if (m_This == nullptr)
//		{
//			m_This = new CEngine;
//		}
//
//		return m_This;
//	}
//
//	static void Destroy()
//	{
//		if (m_This != nullptr)
//		{
//			delete m_This;
//			// ������ ���� ������ nullptr �� �ٽ� ä���ֱ�
//			m_This = nullptr;
//		}
//	}
//
//private:
//	CEngine();
//};

class CEngine
{
private:
	HWND	m_hMainHwnd;
	POINT	m_Resolution;

public:
	int Init(HWND hwnd, POINT resolution);

	void Progress();

public:
	static CEngine* GetInst()
	{
		// ������ ������ �޸𸮶� ���μ��� ���� �� �޸� ���� ��
		// ������ ���߿��� �޸� ������ �Ұ����ϴ�.
		static CEngine mgr;
		return &mgr;
	}

private:
	CEngine();
	// ���� ������ ������ �̱��� ��ü�� �߰������� �����Ǵ� ���� ����
	CEngine(const CEngine& _origin) = delete;
};