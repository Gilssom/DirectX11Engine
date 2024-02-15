#pragma once
#include "Singletone.h"


enum class KEY
{
    W, S, A, D,
    Z, X, C, V,

    _0,
    _1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
    _9,

    LEFT,
    RIGHT,
    UP,
    DOWN,

    LBTN,
    RBTN,

    ENTER,
    ESC,
    SPACE,
    LSHIFT,
    ALT,
    CTRL,

    KEY_END,
};

enum class KEY_STATE
{
    TAP,        // ������
    PRESSED,    // ���� ����
    RELEASED,   // �����ٰ� �� ����
    NONE,
};

struct KeyInfo
{
    KEY_STATE   State;
    bool        PrevPressed;
};

class CKeyManager : public CSingleton<CKeyManager>
{
    SINGLE(CKeyManager)

private:
    vector<KeyInfo> m_VecKey;
    Vec2            m_CurMousePos;
    Vec2            m_PrevMousePos; // ���� ���콺 ��ǥ
    Vec2            m_DragDir;

public:
    void Init();
    void Tick();

public:
    KEY_STATE GetKeyState(KEY _key) { return m_VecKey[(UINT)_key].State; }

    Vec2 GetMousePos() { return m_CurMousePos; };
    Vec2 GetPrevMousePos() { return m_PrevMousePos; };
    Vec2 GetMouseDrag() { return m_DragDir; };
};

