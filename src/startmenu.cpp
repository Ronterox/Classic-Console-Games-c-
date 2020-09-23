// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <conio.h>
#include <iostream>
#include "games.h"
#include "prompt_commands.h"

#define KEY_ESCAPE 27
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_RETURN 13

unsigned int selected = 0;
int menulvl = -1;
bool fini = 0;

void Draw(const char* opt1, const char* opt2, const char* opt3)
{
	system("cls");
	textcolor(7);
	std::cout << "-------------------------------------------------------------------" << std::endl;
	std::cout << "---------------- Welcome To Classic Games Package -----------------" << std::endl;
	std::cout << "-------------------------------------------------------------------" << std::endl;
	textcolor(3);
	std::cout << "                         Made By Ricardo" << std::endl;
	std::cout << std::endl << std::endl;
	if (selected == 0)
		textcolor(6);
	else
		textcolor(7);
	std::cout << "             " << opt1 << "     ";
	if (selected == 1)
		textcolor(6);
	else
		textcolor(7);
	std::cout << opt2 << "     ";
	if (selected == 2)
		textcolor(6);
	else
		textcolor(7);
	std::cout << opt3 << std::endl << std::endl << std::endl;
	if (selected == 3)
		textcolor(6);
	else
		textcolor(7);
	if (menulvl == -1)
		std::cout << "                              " << "Exit" << std::endl << std::endl << std::endl;
	else
		std::cout << "                             " << "Go Back" << std::endl << std::endl << std::endl;
}

void CheckSelection()
{
	switch (selected)
	{
	case 0:
		switch (menulvl)
		{
		case -1:
			menulvl = 0;
			break;
		case 0:
			PlaySnake(5, 20, 10);
			menulvl = -1;
			break;
		case 1:
			PlayPong(10, 20, 10);
			menulvl = -1;
			break;
		}
		break;
	case 1:
		switch (menulvl)
		{
		case -1:
			menulvl = 1;
			break;
		case 0:
			PlaySnake(10, 20, 10);
			menulvl = -1;
			break;
		case 1:
			PlayPong(20, 20, 10);
			menulvl = -1;
			break;
		}
		break;
	case 2:
		switch (menulvl)
		{
		case -1:
			fontSize(30);
			PlayHangman();
			fontSize(40);
			break;
		case 0:
			PlaySnake(60, 20, 10);
			menulvl = -1;
			break;
		case 1:
			PlayPong(60, 20, 10);;
			menulvl = -1;
			break;
		}
		break;
	case 3:
		if (menulvl == -1)
			fini = true;
		else
			menulvl = -1;
		break;
	}
}

bool InputMenu()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
		case KEY_LEFT:
			if (selected > 0)
				selected--;
			break;
		case 'd':
		case KEY_RIGHT:
			if (selected < 2)
				selected++;
			break;
		case 'w':
		case KEY_UP:
			if (selected == 3)
				selected = 1;
			break;
		case 'x':
		case 's':
		case KEY_DOWN:
		case KEY_ESCAPE:
			selected = 3;
			break;
		case KEY_RETURN:
			CheckSelection();
			break;
		}
		return true;
	}
	return false;
}

void Start()
{
	fontSize(40);
	MaximizeWindow();
	Draw("Play Snake", "Play Pong", "Play Hangman");

	while (!fini)
	{
		if (InputMenu())
		{
			if (menulvl == -1)
				Draw("Play Snake", "Play Pong", "Play Hangman");
			else if (menulvl == 0)
				Draw("Easy Mode", "Classic Mode", "Hard Mode");
			else if (menulvl == 1)
				Draw("\b\bBoring Mode", "Classic Mode", "60 FPS Mode");
		}
	}
}

int main()
{
	Start();
	return 0;
}
