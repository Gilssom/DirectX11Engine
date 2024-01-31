#pragma once

// ������ ���� �޸� : ���� ����
// ���μ��� ������ �� �ʱ�ȭ
// ���μ��� ���� �� ����
// ���μ����� ���� ���� ��� �����Ǵ� �޸�

class CEngine : public CSingleton<CEngine>
{
	SINGLE(CEngine) // ��ũ�� ����

private:
	HWND	m_hMainHwnd;
	POINT	m_Resolution;

public:
	HWND GetMainWnd() { return m_hMainHwnd; }
	int Init(HWND hwnd, POINT resolution);
	void Progress();
};