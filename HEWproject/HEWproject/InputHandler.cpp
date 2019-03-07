#include "InputHandler.h"



InputHandler::InputHandler()
{
	initCommand();
}


InputHandler::~InputHandler()
{
	uninitCommand();
}

Command * InputHandler::handleInput(int num)
{
	if (num==1)
	{
		if (inputSth('A'))
		{
			return buttonA_;
		}
		if (inputSth('D'))
		{
			return buttonD_;
		}
		if (inputSth(VK_SPACE))
		{
			return buttonSpace_;
		}
		if (inputSth('W'))
		{
			return buttonW_;
		}
		if (inputSth('S'))
		{
			return buttonS_;
		}
	}
	if (num==2)
	{
		if (inputSth(VK_LEFT))
		{
			return buttonA_;
		}
		if (inputSth(VK_RIGHT))
		{
			return buttonD_;
		}
		if (inputSth(VK_SPACE))
		{
			return buttonSpace_;
		}
		if (inputSth(VK_UP))
		{
			return buttonW_;
		}
		if (inputSth(VK_DOWN))
		{
			return buttonS_;
		}
	}

	return nullptr;
}

void InputHandler::initCommand()
{
	buttonA_ = new leftCommand();
	buttonD_ = new rightCommand();
	buttonW_ = new upCommand();
	buttonS_ = new downCommand();
	buttonSpace_ = new upCommand();

}

void InputHandler::uninitCommand()
{
	delete buttonA_;
	delete buttonD_;
	delete buttonW_;
	delete buttonS_;
	delete buttonSpace_;
}

int InputHandler::inputSth(int port)
{

	DWORD	dwEvent;
	HANDLE	h;

	/* ゲームパッド入力 */
	if ((port & 0xfe00) == 0x0200) {
		int		id = (port & 0x01f0) >> 4;
		int		func = port & 0x0f;
		JOYINFO	ji;

		switch (func) {
		case 0:	case 1:	case 2:	case 3:
			if (joyGetPos(id, &ji) != JOYERR_NOERROR)
				return -1;
			switch (func) {
			case 0:
				return ji.wXpos;
			case 1:
				return ji.wYpos;
			case 2:
				return ji.wZpos;
			case 3:
				return ji.wButtons;
			}
			break;
		default:
			break;
		}
		return 0;
	}
	// キー/マウス イベント チェック
	dwEvent = 0;
	h = GetStdHandle(STD_INPUT_HANDLE);
	if (GetNumberOfConsoleInputEvents(h, &dwEvent) && dwEvent) {
		DWORD			dwRead = 0;
		PINPUT_RECORD	pInpRec = (PINPUT_RECORD)_alloca(dwEvent * sizeof(INPUT_RECORD));

		if (ReadConsoleInput(h, pInpRec, dwEvent, &dwRead) && dwRead) {
			PINPUT_RECORD	pir = pInpRec;
			DWORD			dw;
			for (dw = 0; dw < dwRead; dw++, pir++) {
				switch (pir->EventType) {
				case KEY_EVENT: {
					KEY_EVENT_RECORD*	pker = &pir->Event.KeyEvent;
					if (pker->wVirtualKeyCode > 0x0FF)
						break;
					if (pker->bKeyDown)
						dwKeyMap[pker->wVirtualKeyCode >> 5] |= (0x01 << (pker->wVirtualKeyCode & 31));
					else
						dwKeyMap[pker->wVirtualKeyCode >> 5] &= ~(0x01 << (pker->wVirtualKeyCode & 31));
					if (pker->dwControlKeyState & (LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED))
						dwKeyMap[VK_MENU >> 5] |= (0x01 << (VK_MENU & 31));
					else
						dwKeyMap[VK_MENU >> 5] &= ~(0x01 << (VK_MENU & 31));
					if (pker->dwControlKeyState & (LEFT_CTRL_PRESSED | RIGHT_CTRL_PRESSED))
						dwKeyMap[VK_CONTROL >> 5] |= (0x01 << (VK_CONTROL & 31));
					else
						dwKeyMap[VK_CONTROL >> 5] &= ~(0x01 << (VK_CONTROL & 31));
					if (pker->dwControlKeyState & SHIFT_PRESSED)
						dwKeyMap[VK_SHIFT >> 5] |= (0x01 << (VK_SHIFT & 31));
					else
						dwKeyMap[VK_SHIFT >> 5] &= ~(0x01 << (VK_SHIFT & 31));
					break;
				}
				case MOUSE_EVENT: {
					MOUSE_EVENT_RECORD	*pmer = &pir->Event.MouseEvent;
					crdMouse = pmer->dwMousePosition;
					if (pmer->dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
						dwKeyMap[VK_LBUTTON >> 5] |= (0x01 << (VK_LBUTTON & 31));
					else
						dwKeyMap[VK_LBUTTON >> 5] &= ~(0x01 << (VK_LBUTTON & 31));
					if (pmer->dwButtonState & FROM_LEFT_2ND_BUTTON_PRESSED)
						dwKeyMap[VK_MBUTTON >> 5] |= (0x01 << (VK_MBUTTON & 31));
					else
						dwKeyMap[VK_MBUTTON >> 5] &= ~(0x01 << (VK_MBUTTON & 31));
					if (pmer->dwButtonState & RIGHTMOST_BUTTON_PRESSED)
						dwKeyMap[VK_RBUTTON >> 5] |= (0x01 << (VK_RBUTTON & 31));
					else
						dwKeyMap[VK_RBUTTON >> 5] &= ~(0x01 << (VK_RBUTTON & 31));
					break;
				}
				default:
					break;
				}
			}
		}
	}

	// マウス座標を返す
	switch (port) {
	case PM_CURX:
		return crdMouse.X + 1;
	case PM_CURY:
		return crdMouse.Y + 1;
	default:
		break;
	}
	// キー状態を返す
	return (dwKeyMap[(port & 0x0FF) >> 5] & (0x01 << (port & 31))) != 0;

}

