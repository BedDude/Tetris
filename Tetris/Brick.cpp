#include "Brick.h"

extern const short WIDTH = 10;
extern const short HEIGHT = 20;
extern char field[HEIGHT][WIDTH];

bool Brick::isCorrectLeftMove()
{
	removeBrick();

	Point realPosition;
	for (int i = 0; i < 4; i++) 
	{
		realPosition = getRealPosition(_location, _brick[i]);
		if (realPosition.x == 0 || field[realPosition.y][realPosition.x - 1] == '#')
			return false;
	}
	return true;
}

bool Brick::isCorrectRightMove()
{
	removeBrick();

	Point realPosition;
	for (int i = 0; i < 4; i++)
	{
		realPosition = getRealPosition(_location, _brick[i]);
		if (realPosition.x == WIDTH - 1 || field[realPosition.y][realPosition.x + 1] == '#')
			return false;
	}
	return true;
}

bool Brick::isCorrectMoveDown()
{
	Point realPosition;
	for (int i = 0; i < 4; i++)
	{
		realPosition = getRealPosition(_location, _brick[i]);
		if (realPosition.y == HEIGHT - 1)
			return false;
	}
	return true;
}

bool Brick::isCorrectRotate()
{
	removeBrick();

	Point realNewPosition;
	Point newPosition;
	for (int i = 0; i < 4; i++)
	{
		newPosition = { -_brick[i].y, _brick[i].x };
		realNewPosition = getRealPosition(_location, newPosition);
		if (field[realNewPosition.y][realNewPosition.x] == '#' || realNewPosition.x < 0 || realNewPosition.x >= WIDTH)
			return false;
	}
	return true;
}

void Brick::removeBrick()
{
	Point realPosition;
	for (int i = 0; i < 4; i++)
	{
		realPosition = getRealPosition(_location, _brick[i]);
		field[realPosition.y][realPosition.x] = '.';
	}
}

void Brick::addFigureOnField()
{
	Point realPosition;
	for (int i = 0; i < 4; i++)
	{
		realPosition = getRealPosition(_location, _brick[i]);
		field[realPosition.y][realPosition.x] = '#';
	}
}

Point Brick::getRealPosition(Point location, Point localCoordinate)
{
	short realXPosition = location.x + localCoordinate.x;
	short realYPositon = location.y + localCoordinate.y;
	
	Point realPosition = { realXPosition,realYPositon };

	return realPosition;
}

void Brick::generate(Type type)
{
	_type = type;
	isFly = true;

	//Set centre coordinate
	switch (_type)
	{
	case I_TYPE:
		_location = { 5,0 };
		break;
	case O_TYPE:
	case S_TYPE:
	case Z_TYPE:
		_location = { 4,0 };
		break;
	default:
		_location = { 4,1 };
		break;
	}

	//Set local coordinatse for all parts of brick
	switch (type)
	{
	case I_TYPE:
		_brick[0] = { -2,0 };
		_brick[1] = { -1,0 };
		_brick[2] = { 0,0 };
		_brick[3] = { 1,0 };
		break;
	case J_TYPE:
		_brick[0] = { -1,-1 };
		_brick[1] = { 1,0 };
		_brick[2] = { 0,0 };
		_brick[3] = { -1,0 };
		break;
	case L_TYPE:
		_brick[0] = { 1,-1 };
		_brick[1] = { 1,0 };
		_brick[2] = { 0,0 };
		_brick[3] = { -1,0 };
		break;
	case O_TYPE:
		_brick[0] = { 0,0 };
		_brick[1] = { 1,0 };
		_brick[2] = { 0,1 };
		_brick[3] = { 1,1 };
		break;
	case S_TYPE:
		_brick[0] = { 1,0 };
		_brick[1] = { 0,0 };
		_brick[2] = { 0,1 };
		_brick[3] = { -1,1 };
		break;
	case T_TYPE:
		_brick[0] = { 0,-1 };
		_brick[1] = { -1,0 };
		_brick[2] = { 0,0 };
		_brick[3] = { 1,0 };
		break;
	case Z_TYPE:
		_brick[0] = { -1,0 };
		_brick[1] = { 0,0 };
		_brick[2] = { 0,1 };
		_brick[3] = { 1,1 };
		break;
	}

	//can i generate this brick
	Point realPosition;
	for (int i = 0; i < 4; i++)
	{
		realPosition = getRealPosition(_location, _brick[i]);
		if (field[realPosition.y][realPosition.x] == '#')
		{
			isFly = false;
			break;
		}
	}
	if(isFly)
		addFigureOnField();
}

void Brick::rotate()
{
	if (_type != O_TYPE && isCorrectRotate())
	{
		Point newPoint;
		for (int i = 0; i < 4; i++)
		{
			newPoint = { -_brick[i].y, _brick[i].x };
			_brick[i] = newPoint;
		}
	}
	addFigureOnField();
}

void Brick::moveLeft()
{
	if (isCorrectLeftMove())
		_location.x--;
	addFigureOnField();
}

void Brick::moveRight()
{
	if (isCorrectRightMove())
		_location.x++;
	addFigureOnField();
}

void Brick::moveDown()
{
	isFly = isCorrectMoveDown();
	if (isFly)
	{
		removeBrick();
		_location.y++;

		Point realPosition;
		for (int i = 0; i < 4; i++)
		{
			realPosition = getRealPosition(_location, _brick[i]);
			if (field[realPosition.y][realPosition.x] == '#')
			{
				isFly = false;
				_location.y--;
				break;
			}
		}
		addFigureOnField();
	}
}