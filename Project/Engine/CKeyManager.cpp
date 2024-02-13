#include "pch.h"
#include "CKeyManager.h"

UINT g_KeyValue[(UINT)KEY::KEY_END]
=
{
    'W', 'S', 'A', 'D',
    'Z', 'X', 'C', 'V',

    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',

    VK_LEFT,
    VK_RIGHT,
    VK_UP,
    VK_DOWN,

    VK_RETURN,
    VK_ESCAPE,
    VK_SPACE,
    VK_LSHIFT,
    VK_LMENU,
    VK_LCONTROL
};

CKeyManager::CKeyManager()
{

}

CKeyManager::~CKeyManager()
{

}

void CKeyManager::Init()
{
	for (UINT i = 0; i < (UINT)KEY::KEY_END; ++i)
	{
		KeyInfo info = {};
		info.State = KEY_STATE::NONE;
		info.PrevPressed = false;

		m_VecKey.push_back(info);
	}
}

void CKeyManager::Tick()
{
	for (size_t i = 0; i < m_VecKey.size(); ++i)
	{
        // Key �� ���ȴ�.
        if (GetAsyncKeyState(g_KeyValue[i]) & 0x8001)
        {
            // ������ �ȴ����־���.
            if (!m_VecKey[i].PrevPressed)
            {
                // ó�� ���� ����
                m_VecKey[i].State = KEY_STATE::TAP;
            }
            else
            {
                // ��� ������ �ִ� ����
                m_VecKey[i].State = KEY_STATE::PRESSED;
            }

            m_VecKey[i].PrevPressed = true;
        }

        else
        {
            // �ش� Key �� �ȴ����ִ�.
            if (m_VecKey[i].PrevPressed)
            {
                // ���� Frame ������ �����־���. = �� ����
                m_VecKey[i].State = KEY_STATE::RELEASED;
            }
            else
            {
                // �������� �ȴ��� �־��� ���ݵ� �ȴ����ִ�.
                m_VecKey[i].State = KEY_STATE::NONE;
            }

            m_VecKey[i].PrevPressed = false;
        }
	}
}
