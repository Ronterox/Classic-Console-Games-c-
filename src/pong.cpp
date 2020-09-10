#include <iostream>
#include <conio.h>
#include "prompt_commands.h"
#include "pong.h"

#define SPRITE_PADDLE '\xDB'
#define SPRITE_WALL '\xB2'
#define SPRITE_BALL 'o'

#define KEY_ESCAPE 27

void LogicCallPong(cGameManager& gameManager)
{
	gameManager.ball.Move();

	if (gameManager.score1 == 7 || gameManager.score2 == 7)
		gameManager.RestartGame();
	else if (gameManager.ball.position.y < 1 || gameManager.ball.position.y >= gameManager.getHeight() - 2)
	{
		if (gameManager.ball.position.y < 1)
			gameManager.ball.RandomDirection(5, 6);
		else
			gameManager.ball.RandomDirection(3, 4);
	}
	else if (gameManager.ball.position.x < 1 || gameManager.ball.position.x >= gameManager.getWidth() - 1)
	{
		if (gameManager.ball.position.x < 1)
			gameManager.ResetRound(1, 1);
		else
			gameManager.ResetRound(1, 2);
	}
	else if (gameManager.paddle1.isHitting(gameManager.ball.position.x, gameManager.ball.position.y))
	{
		gameManager.ball.RandomRight();
	}
	else if (gameManager.paddle2.isHitting(gameManager.ball.position.x, gameManager.ball.position.y))
	{
		gameManager.ball.RandomLeft();
	}
}

void InputCallPong(cGameManager& gameManager)
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			if (!gameManager.paddle1.isHitting(1, 1))
				gameManager.paddle1.position.y--;
			break;
		case 's':
			if (!gameManager.paddle1.isHitting(1, gameManager.getHeight() - 2))
				gameManager.paddle1.position.y++;
			break;
		case 'i':
			if (!gameManager.paddle2.isHitting(gameManager.getWidth() - 2, 1))
				gameManager.paddle2.position.y--;
			break;
		case 'k':
			if (!gameManager.paddle2.isHitting(gameManager.getWidth() - 2, gameManager.getHeight() - 2))
				gameManager.paddle2.position.y++;
			break;
		case KEY_ESCAPE:
		case 'x':
			gameManager.gameOver = true;
		case 'r':
			gameManager.RestartGame();
			break;
		}
	}
}

void DrawCallPong(cGameManager& gameManager)
{
	system("cls");
	for (int i = 0; i < gameManager.getHeight(); i++)
	{
		for (int j = 0; j < gameManager.getWidth(); j++)
		{
			if (i == 0 || i == gameManager.getHeight() - 1 || j == 0 || j == gameManager.getWidth() - 1)
			{
				textcolor(8);
				std::cout << SPRITE_WALL;
			}
			else if (gameManager.paddle1.isHitting(j, i) || gameManager.paddle2.isHitting(j, i))
			{
				textcolor(7);
				std::cout << SPRITE_PADDLE;
			}
			else if (gameManager.ball.position.x == j && gameManager.ball.position.y == i)
			{
				textcolor(5);
				std::cout << SPRITE_BALL;
			}
			else
				std::cout << ' ';
		}
		std::cout << "\n";
	}
	textcolor(6);
	std::cout << "Player 1: " << gameManager.score1 << "	Player 2: " << gameManager.score2 << "\n\n";
	textcolor(3);
	std::cout << "R to Start or Restart	Esc or X To Exit\n\n";

	std::cout << gameManager.ball;
}

void UpdatePong(const int& fps, cGameManager& gameManager)
{
	float delay = 1000 / fps;
	while (!gameManager.gameOver)
	{
		FrameTimer timer;
		InputCallPong(gameManager);
		LogicCallPong(gameManager);
		DrawCallPong(gameManager);
		if (delay > timer.getDuration())
			Sleep(delay - timer.getDuration());
	}
}

void PlayPong(const int& fps, const int& width, const int& height)
{
	cGameManager gameManager = cGameManager(width, height);
	UpdatePong(fps, gameManager);
}
