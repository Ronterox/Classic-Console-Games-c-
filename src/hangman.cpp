#include <iostream>
#include <string>

#define height 20
#define width 29

int h_guesses;
std::string h_word;
std::string p_word;

void StartHangman()
{
	h_guesses = 10;
	h_word = "HangDUDE";
	p_word = "";
}

void PrintLetters(const char& from, const char& to)
{
	std::cout << "  ";
	bool printed;
	for (char i = from; i <= to; i++)
	{
		printed = false;
		if ((int)p_word.length() != 0)
		{
			for (int j = 0; j < (int)p_word.length(); j++)
			{
				if (toupper(p_word[j]) == i)
				{
					std::cout << "  ";
					printed = true;
					break;
				}
			}
		}
		if (!printed)
			std::cout << i << " ";
	}
	std::cout << " ";
}

void PrintSpaces(const int& numSpaces)
{
	for (int i = 0; i < numSpaces; i++)
		std::cout << " ";
}

void PrintWord()
{
	PrintSpaces((width + 1 - h_word.length() * 2) / 2);
	bool printed;
	for (int i = 0; i < (int)h_word.length(); i++)
	{
		printed = false;
		if ((int)p_word.length() != 0)
		{
			for (int j = 0; j < (int)p_word.length(); j++)
			{
				if (toupper(p_word[j]) == toupper(h_word[i]))
				{
					std::cout << h_word[i] << " ";
					printed = true;
					break;
				}
			}
		}
		if (!printed)
			std::cout << "_ ";
	}
	PrintSpaces((width - h_word.length() * 2) / 2);
}

void DrawHangman()
{
	system("cls");
	for (int i = 0; i < height; i++)
	{
		switch (i)
		{
		case 0: case 2: case 10: case 12: case 15: case 17: case height - 1:
			std::cout << "+";
			break;

		default: std::cout << "|"; break;
		}

		switch (i)
		{
		case 1: std::cout << "          " << "HANG MAN" << "           "; break;
		case 11: std::cout << "      " << "Available Letters" << "      "; break;
		case 13: PrintLetters('A', 'M'); break;
		case 14: PrintLetters('N', 'Z'); break;
		case 16: std::cout << "       " << "Guess The Word" << "        "; break;
		case 18:
			PrintWord();
			break;

		default:
			if (h_guesses < 10 && i == 3)
				std::cout << "             |               ";
			else if (h_guesses < 9 && i == 4)
				std::cout << "             |               ";
			else if (h_guesses < 8 && i == 5)
				std::cout << "             O               ";
			else if (h_guesses < 5 && i == 6)
				std::cout << "            /|\\              ";
			else if (h_guesses < 6 && i == 6)
				std::cout << "             |\\              ";
			else if (h_guesses < 7 && i == 6)
				std::cout << "             |               ";
			else if (h_guesses < 3 && i == 7)
				std::cout << "            / \\              ";
			else if (h_guesses < 4 && i == 7)
				std::cout << "              \\              ";
			else if (h_guesses < 2 && i == 8)
				std::cout << "         +--------+          ";
			else if (h_guesses < 1 && i == 9)
				std::cout << "         |        |          ";
			else
				for (int j = 0; j < width; j++)
				{
					switch (i)
					{
					case 0: case 2: case 10: case 12: case 15: case 17: case height - 1:
						std::cout << "-";
						break;

					default: std::cout << " "; break;
					}
				}
			break;
		}

		switch (i)
		{
		case 0: case 2: case 10: case 12: case 15: case 17: case height - 1:
			std::cout << "+\n";
			break;

		default: std::cout << "|\n"; break;
		}
	}
	std::cout << "You have " << h_guesses << " guesses!\n" << std::endl;
}

bool WasInput(const char& p_char)
{
	if ((int)p_word.length() != 0)
	{
		for (int i = 0; i < (int)p_word.length(); i++)
		{
			if (toupper(p_word[i]) == p_char) return true;
		}
	}
	return false;
}

bool IsInWord(const char& p_char)
{
	for (int i = 0; i < (int)h_word.length(); i++)
	{
		if (toupper(h_word[i]) == p_char) return true;
	}
	return false;
}

void InputHangman()
{
	std::cout << "Write a letter: ";
	char p_char = toupper(getchar());

	if (p_char == '\n') return;

	if (!WasInput(p_char))
	{
		p_word += p_char;
		if (!IsInWord(p_char))
			h_guesses--;
	}
}
//FIX THIS
void ComparePWord()
{
	int counter = 0;
	for (int i = 0; i < (int)h_word.length(); i++)
	{
		if (p_word.find(h_word[i]) != std::string::npos) counter++;
	}
	if (counter == (int)h_word.length())
		h_guesses = 100;
}

void PlayHangman()
{
	bool isFinished = false;
	StartHangman();
	DrawHangman();
	while (!isFinished)
	{
		InputHangman();
		DrawHangman();
		ComparePWord();
		isFinished = h_guesses < 1 || h_guesses == 100;
	}
	if (h_guesses == 100)
		std::cout << "YOU WON, NICE!\n";
	else
		std::cout << "YOU LOST HAHAHAHA\n";
	system("pause");
}