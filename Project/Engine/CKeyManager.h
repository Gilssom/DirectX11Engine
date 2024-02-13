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
    TAP,        // ´­·¶´Ù
    PRESSED,    // ´­¸° »óÅÂ
    RELEASED,   // ´­·¶´Ù°¡ ¶¾ »óÅÂ
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

public:
    void Init();
    void Tick();

public:
    KEY_STATE GetKeyState(KEY _key) { return m_VecKey[(UINT)_key].State; }
};

