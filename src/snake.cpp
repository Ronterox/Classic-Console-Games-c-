#include <iostream>
#include <conio.h>
#include "prompt_commands.h"

bool gameOver, finished;

int pts;
int width, height;
int posX, posY;
int fruitPosX, fruitPosY;

int tailX[25], tailY[25];
int nTail;

enum class cDirection { Stop, Left, Right, Up, Down };
cDirection dir;

#define KEY_ESCAPE 27
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int score;

char snakeSprite, fruitSprite, wallSprite, tailSprite;

void ChangeFruitPos()
{
	fruitPosX = rand() % (width - 1);
	fruitPosY = rand() % (height - 1);
}

bool HittingTail(const int& x, const int& y)
{
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y) return true;
	}
	return false;
}

void IncrementScore(const int& points)
{
	score += points;
}

void StartSnake(const int& w, const int& h, const int& fps)
{
	gameOver = false;

	nTail = 0;

	width = w;
	height = h;

	pts = fps * 2;

	score = 0;

	srand(time(0));

	posX = width / 2;
	posY = height / 2;

	ChangeFruitPos();

	snakeSprite = 'O';
	tailSprite = 'o';
	fruitSprite = 'm';
	wallSprite = '#';

	dir = cDirection::Stop;
}

void DrawCallSnake()
{
	system("cls");
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
			{
				textcolor(2);
				std::cout << wallSprite;
			}
			else if (i == posY && j == posX)
			{
				textcolor(7);
				std::cout << snakeSprite;
			}
			else if (i == fruitPosY && j == fruitPosX)
			{
				textcolor(4);
				std::cout << fruitSprite;
			}
			else if (HittingTail(j, i))
			{
				textcolor(7);
				std::cout << tailSprite;
			}
			else
				std::cout << " ";
		}
		std::cout << std::endl;
	}
	textcolor(6);
	std::cout << "Score: " << score;
	textcolor(3);
	std::cout << "	Esc or X To Exit\n\n";
	std::cout << "Tail Length: " << nTail << "\n\n";
}

void LogicSnake()
{
	if (nTail > 0)
	{
		int prevX = tailX[0];
		int prevY = tailY[0];
		int tempX, tempY;
		tailX[0] = posX;
		tailY[0] = posY;
		for (int i = 1; i < nTail; i++)
		{
			tempX = tailX[i];
			tempY = tailY[i];
			tailX[i] = prevX;
			tailY[i] = prevY;
			prevX = tempX;
			prevY = tempY;
		}
	}
	else
	{
		tailX[0] = posX;
		tailY[0] = posY;
	}
	switch (dir)
	{
	case cDirection::Up:
		posY--;
		break;
	case cDirection::Down:
		posY++;
		break;
	case cDirection::Left:
		posX--;
		break;
	case cDirection::Right:
		posX++;
		break;
	}

	if (HittingTail(posX, posY))
		gameOver = true;
	else if (posX <= 0 || posY <= 0 || posX >= width - 1 || posY >= height - 1)
	{
		if (posX <= 0) posX = width - 1; else if (posY <= 0) posY = height - 1;
		else if (posX >= width - 1) posX = 0; else if (posY >= height - 1) posY = 0;
	}
	else if (posX == fruitPosX && posY == fruitPosY)
	{
		if (nTail < sizeof(tailX) / sizeof(int)) nTail++;
		ChangeFruitPos();
		IncrementScore(pts);
	}
	else if (fruitPosX == 0 || fruitPosY == 0 || fruitPosX == width - 1 || fruitPosY == height - 1)
		ChangeFruitPos();
}

void InputSnake()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
		case KEY_UP:
			dir = cDirection::Up;
			break;
		case 'a':
		case KEY_LEFT:
			dir = cDirection::Left;
			break;
		case 's':
		case KEY_DOWN:
			dir = cDirection::Down;
			break;
		case 'd':
		case KEY_RIGHT:
			dir = cDirection::Right;
			break;
		case 'x':
		case KEY_ESCAPE:
			gameOver = true;
			finished = true;
			break;
		}
	}
}

void UpdateSnake(const int& fps)
{
	float delay = 1000 / fps;
	while (!gameOver)
	{
		FrameTimer timer;
		InputSnake();
		LogicSnake();
		DrawCallSnake();
		if (delay > timer.getDuration())
			Sleep(delay - timer.getDuration());
	}
	Sleep(300);
}

void PlaySnake(const int& fps, const int& width, const int& height)
{
	finished = false;
	while (!finished)
	{
		StartSnake(width, height, fps);
		UpdateSnake(fps);
		textcolor(7);
		if (!finished)
		{
			std::cout << "OH NO, YOU CRASHED YOUR HEAD!" << std::endl;
			system("pause");
		}
	}
}
