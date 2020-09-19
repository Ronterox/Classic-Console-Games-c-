#pragma once
#include <Windows.h>
#include <chrono>

/*
0	black
1	blue
2	green
3	cyan
4	red
5	magenta
6	yellow / brown
7	white
8	gray
9	bright blue
*/
static void textcolor(const int& color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

static void fontSize(const int& fontSize)
{
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = fontSize;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &info);
}

static void MaximizeWindow()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
}

class FrameTimer
{
private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;
public:
	FrameTimer() :
		start(std::chrono::high_resolution_clock::now()), duration(std::chrono::milliseconds(0))
	{	
	}

	const float getDuration()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		return duration.count();
	}
};