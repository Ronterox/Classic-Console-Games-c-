#pragma once

struct Vector2
{
	int x, y;

	Vector2() :
		x(0), y(0)
	{
	}
	Vector2(const int& x, const int& y) :
		x(x), y(y)
	{
	}
};

class cBall
{
private:
	Vector2 startPos;
public:
	enum class cDirection
	{
		STOP, RIGHT, RIGHT_UP, RIGHT_DOWN, LEFT, LEFT_UP, LEFT_DOWN,
	};
	enum cDirection dir;
	Vector2 position;

	cBall() :
		startPos(), position(), dir(cDirection::STOP)
	{
	}

	cBall(const int& x, const int& y) :
		startPos(x, y), position(x, y), dir(cDirection::STOP)
	{
	}

	void ChangeDirection(const cDirection& newDir) { dir = newDir; }

	void Move()
	{
		switch (dir)
		{
		case cDirection::RIGHT: position.x++; break;
		case cDirection::RIGHT_UP: position.x++; position.y--; break;
		case cDirection::RIGHT_DOWN: position.x++; position.y++; break;
		case cDirection::LEFT: position.x--; break;
		case cDirection::LEFT_DOWN: position.x--; position.y++; break;
		case cDirection::LEFT_UP: position.x--; position.y--; break;
		case cDirection::STOP: break;
		}
	}
	/*
	* 1 RIGHT
	* 2 LEFT
	* 3 RIGHT_UP
	* 4 LEFT_UP
	* 5 RIGHT_DOWN
	* 6 LEFT_DOWN
	*/
	void RandomDirection(const int& minDir, const int& maxDir)
	{
		switch (rand() % maxDir + minDir)
		{
		case 1:
			dir = cDirection::RIGHT;
			break;
		case 2:
			dir = cDirection::LEFT;
			break;
		case 3:
			dir = cDirection::RIGHT_UP;
			break;
		case 4:
			dir = cDirection::LEFT_UP;
			break;
		case 5:
			dir = cDirection::RIGHT_DOWN;
			break;
		case 6:
			dir = cDirection::LEFT_DOWN;
			break;
		}
	}

	void RandomRight()
	{
		switch (rand() % 3 + 1)
		{
		case 1:
			dir = cDirection::RIGHT;
			break;
		case 2:
			dir = cDirection::RIGHT_UP;
			break;
		case 3:
			dir = cDirection::RIGHT_DOWN;
			break;
		}
	}

	void RandomLeft()
	{
		switch (rand() % 3 + 1)
		{
		case 1:
			dir = cDirection::LEFT;
			break;
		case 2:
			dir = cDirection::LEFT_UP;
			break;
		case 3:
			dir = cDirection::LEFT_DOWN;
			break;
		}
	}

	void RestartPosition()
	{
		dir = cDirection::STOP;
		position = startPos;
	}
};

std::ostream& operator<<(std::ostream& stream, const cBall& other)
{
	stream << "(" << other.position.x << "," << other.position.y << ")";
	return stream;
}

class Paddle
{
private:
	Vector2 startPos;
	int size;
	//bool isCpu;
public:
	Vector2 position;

	Paddle() :
		startPos(0, 0), position(0, 0), size(1)
	{
	}

	Paddle(const int& x, const int& y, const int& size) :
		startPos(x, y), position(x, y), size(size)
	{
	}

	const int& getSize() { return size; }

	bool isHitting(const int& x, const int& y)
	{
		for (int i = 0; i <= size; i++)
		{
			if (x == position.x && y == position.y + i) return true;
		}
		return false;
	}

	void RestartPosition()
	{
		position = startPos;
	}
};

class cGameManager
{
private:
	const int width, height;
public:
	int score1 = 0, score2 = 0;
	cBall ball;
	Paddle paddle1;
	Paddle paddle2;
	bool gameOver;

	cGameManager() :
		width(10), height(10), ball(width / 2, height / 2), paddle1(1, height / 2, 4), paddle2(width - 2, height / 2, 4), gameOver(false)
	{
	}

	cGameManager(const int& width, const int& height) :
		width(width), height(height), ball(width / 2, height / 2), paddle1(1, height / 2, 30 * height / 100), paddle2(width - 2, height / 2, paddle1.getSize()), gameOver(false)
	{
	}

	void ResetRound(const int& score, const int& player)
	{
		if (player == 1)
			score1 += score;
		else if (player == 2)
			score2 += score;
		else
			std::cout << "PLAYER NOT FOUND";

		ball.RestartPosition();
		paddle1.RestartPosition();
		paddle2.RestartPosition();

		ball.RandomDirection(1, 2);
		ball.Move();

		Sleep(250);
	}

	void RestartGame()
	{
		score1 = score2 = 0;

		ball.RestartPosition();
		paddle1.RestartPosition();
		paddle2.RestartPosition();

		ball.RandomDirection(1, 2);
		ball.Move();

		Sleep(250);
	}

	const int& getWidth()const { return width; }
	const int& getHeight()const { return height; }
};