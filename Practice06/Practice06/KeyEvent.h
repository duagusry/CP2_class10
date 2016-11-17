#include <windows.h>

enum {
	BLACK, D_BLUE, D_GREEN, D_SKYBLUE, D_RED,
	D_VIOLET, D_YELLOW, GRAY, D_GRAY, BLUE,
	GREEN, SKYBLUE, RED, VIOLET, YELLOW, WHITE
};

class KeyEvent
{
private:
	HANDLE hin;
	COORD KeyWhere;
	DWORD EventCount;
	INPUT_RECORD InRec;
	DWORD NumRead;
	int downKey;
public:
	KeyEvent()
	{
		hin = GetStdHandle(STD_INPUT_HANDLE);
		EventCount = 1;
	}
	int getKey()
	{
		ReadConsoleInput(hin, &InRec, 1, &NumRead);

		if (InRec.EventType == KEY_EVENT)
		{
			if (InRec.Event.KeyEvent.bKeyDown)
			{
				downKey = InRec.Event.KeyEvent.wVirtualKeyCode;
				return downKey;
			}
			else
			{
				return -1;
			}
		}

		return -1;
	}
};

void gotoXY(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setColor(char color, char backGround)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (backGround << 4) + color);
}

void clearConsole()
{
	system("cls");
}