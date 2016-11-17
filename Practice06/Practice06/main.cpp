#include <process.h>
#include <iostream>
#include "KeyEvent.h"

using namespace std;

class Game
{
private:
	int x;
	int y;
	int direction;

	void gotoXY(int x, int y)
	{
		COORD pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}

public:
	Game()
	{
		x = 5;
		y = 5;
		direction = 0;
	}

	void setDirection(int i)
	{
		direction = i;
	}

	void move()
	{
		if (direction == 37 && x >= 1)
			x--;
		else if (direction == 38 && y >= 1)
			y--;
		else if (direction == 39 && x <= 30)
			x++;
		else if (direction == 40 && y <= 30)
			y++;

		system("cls");

		this->gotoXY(x, y);

		cout << x << " " << y;
		cout << "¡Ú";
	}
};

Game *game = new Game();

unsigned int __stdcall mythread(void *)
{
	int i = 0;
	while (1)
	{
		game->move();
		Sleep(500);
	}

	return 0;
}

unsigned int __stdcall keyEvent(void *)
{
	KeyEvent k;
	int i;

	while (1)
	{
		i = k.getKey();
		if (i != -1)
			game->setDirection(i);
	}

	return 0;
}

int main()
{
	HANDLE handleA, handleB;

	handleA = (HANDLE)_beginthreadex(0, 0, &mythread, (void *)0, 0, 0);
	handleB = (HANDLE)_beginthreadex(0, 0, &keyEvent, (void *)0, 0, 0);

	WaitForSingleObject(handleA, INFINITE);
	WaitForSingleObject(handleB, INFINITE);

	CloseHandle(handleA);
	CloseHandle(handleB);

	return 0;
}