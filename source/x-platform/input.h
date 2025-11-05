#pragma once

#include "../modules/system.h"

struct KeyMap
{
    enum
    {
        NONE,
        A = 65,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R = 82,
        S = 83,
        T,
        U,
        V,
        W = 87,
        X,
        Y,
        Z,

        KEY_0 = 48,
        KEY_1,
        KEY_2,
        KEY_3,
        KEY_4,
        KEY_5,
        KEY_6,
        KEY_7,
        KEY_8,
        KEY_9,

        PAD_0 = 48,
        PAD_1,
        PAD_2,
        PAD_3,
        PAD_4,
        PAD_5,
        PAD_6,
        PAD_7,
        PAD_8,
        PAD_9,

        F1 = 241,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,

        ESCAPE = 27,
        TILDE,
        MINUS,
        EQUALS,
        BACKSPACE,
        TAB,
        OPENBRACE,
        CLOSEBRACE,
        ENTER,
        SEMICOLON,
        QUOTE,
        BACKSLASH,
        BACKSLASH2,
        COMMA,
        FULLSTOP,
        SLASH,
        SPACE = 32,

        INSERT,
        DELETE_KEY,
        HOME,
        END,
        PGUP,
        PGDN,
        LEFT,
        RIGHT,
        UP,
        DOWN,

        PAD_SLASH,
        PAD_ASTERISK,
        PAD_MINUS,
        PAD_PLUS,
        PAD_DELETE,
        PAD_ENTER,

        PRINTSCREEN,
        PAUSE,

        ABNT_C1,
        YEN,
        KANA,
        CONVERT,
        NOCONVERT,
        AT,
        CIRCUMFLEX,
        COLON2,
        KANJI,

        KEY_PAD_EQUALS,
        KEY_BACKQUOTE,
        KEY_SEMICOLON2,
        KEY_COMMAND,
        KEY_UNKNOWN,

        /////////////////////////////////////////////

        KEY_MODIFIERS,

        LSHIFT,
        RSHIFT,
        LCTRL,
        RCTRL,
        ALT,
        ALTGR,
        LWIN,
        RWIN,
        MENU,
        SCROLLLOCK,
        NUMLOCK,
        CAPSLOCK,

        SHIFT,
        CTRL,
        COMMAND,
        INALTSEQ,
        ACCENT1,
        ACCENT2,
        ACCENT3,
        ACCENT4
    };
};

const int KEYS = 255;

class Input : public System
{
private:
    bool oldKeys[KEYS];
    bool keys[KEYS];

    struct Mouse
    {
        bool Down;
        bool Dragging;
        int dx, dy;
        int xOld, yOld;
        int x, y;
    };

public:
    KeyMap Key;
    Mouse mouse;

    void OnButton(const unsigned int button, const bool isDown);
    bool Held(int key);
    bool Released(int key);
    bool Pressed(int key);

    bool Init();
    void Update();
};
