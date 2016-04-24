#ifndef __InputManager_H__
#define __InputManager_H__

extern bool g_KeyStates[256];
extern bool g_OldKeyStates[256];
extern bool g_MouseButtonStates[3];
extern bool g_OldMouseButtonStates[3];

class Input
{
public:
    static bool KeyIsPressed(uchar aKey)
    {
        return g_KeyStates[aKey];
    }
    static bool KeyJustPressed(uchar aKey)
    {
        return (g_KeyStates[aKey] & !g_OldKeyStates[aKey]);
    }
    static bool KeyJustReleased(uchar aKey)
    {
        return (!g_KeyStates[aKey] & g_OldKeyStates[aKey]);
    }
    static bool KeyNotPressed(uchar aKey)
    {
        return !KeyIsPressed(aKey);
    }

    static bool KeysArePressed(uchar aKeys[], uint numKeys)
    {
        if (numKeys == 0)
            return false;
        bool pressed = KeyIsPressed(aKeys[0]);

        for (uint i = 1; i < numKeys; i++)
            pressed = pressed & KeyIsPressed(aKeys[i]);

        return pressed;
    }
    static bool KeysJustPressed(uchar aKeys[], uint numKeys)
    {
        if (numKeys == 0)
            return false;
        bool pressed = KeyJustPressed(aKeys[0]);

        for (uint i = 1; i < numKeys; i++)
            pressed = pressed & KeyJustPressed(aKeys[i]);

        return pressed;
    }
    static bool KeysJustReleased(uchar aKeys[], uint numKeys)
    {
        if (numKeys == 0)
            return false;
        bool pressed = KeyJustReleased(aKeys[0]);

        for (uint i = 1; i < numKeys; i++)
            pressed = pressed & KeyJustReleased(aKeys[i]);

        return pressed;
    }
    static bool KeysNotPressed(uchar aKeys[], uint numKeys)
    {
        if (numKeys == 0)
            return false;
        bool pressed = KeyNotPressed(aKeys[0]);

        for (uint i = 1; i < numKeys; i++)
            pressed = pressed & KeyNotPressed(aKeys[i]);

        return pressed;
    }

    static bool LeftMousePressed()
    {
        return g_MouseButtonStates[0];
    }
    static bool MiddleMousePressed()
    {
        return g_MouseButtonStates[1];
    }
    static bool RightMousePressed()
    {
        return g_MouseButtonStates[2];
    }
    static bool LeftMouseJustPressed()
    {
        return (g_MouseButtonStates[0] & !g_OldMouseButtonStates[0]);
    }
    static bool LeftMouseJustReleased()
    {
        return (!g_MouseButtonStates[0] & g_OldMouseButtonStates[0]);
    }
    static bool LeftMouseNotPressed()
    {
        return !LeftMousePressed();
    }
    static bool MiddleMouseJustPressed()
    {
        return (g_MouseButtonStates[1] & !g_OldMouseButtonStates[1]);
    }
    static bool MiddleMouseJustReleased()
    {
        return (!g_MouseButtonStates[1] & g_OldMouseButtonStates[1]);
    }
    static bool MiddleMouseNotPressed()
    {
        return !MiddleMousePressed();
    }
    static bool RightMouseJustPressed()
    {
        return (g_MouseButtonStates[2] & !g_OldMouseButtonStates[2]);
    }
    static bool RightMouseJustReleased()
    {
        return (!g_MouseButtonStates[2] & g_OldMouseButtonStates[2]);
    }
    static bool RightMouseNotPressed()
    {
        return !RightMousePressed();
    }

    static vec2 MouseCoordinates()
    {
        int x;
        int y;
        GetMouseCoordinates(&x, &y);

        return vec2(x, y);
    }
	
	static std::vector<uchar> KeysArePressed()
	{
		std::vector<uchar> keys;

		for (uint i = 0; i < 255; i++)
		{
			if (KeyIsPressed(i))
				keys.push_back((uchar)(i));
		}

		return keys;
	}

	static std::vector<uchar> KeysJustPressed()
	{
		std::vector<uchar> keys;

		for (uint i = 0; i < 255; i++)
		{
			if (KeyJustPressed(i))
				keys.push_back((uchar)(i));
		}

		return keys;
	}

};

#endif