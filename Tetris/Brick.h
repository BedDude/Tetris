#pragma once
#ifndef BRICK_H
#define BRICK_H

enum Type
{
	I_TYPE,
	J_TYPE,
	L_TYPE,
	O_TYPE,
	S_TYPE,
	T_TYPE,
	Z_TYPE
};

struct Point
{
	short x;
	short y;
};

class Brick
{
	Point _location;
	Type _type;
	Point _brick[4];
	bool isCorrectLeftMove();
	bool isCorrectRightMove();
	bool isCorrectMoveDown();
	bool isCorrectRotate();
	void removeBrick();
	void addFigureOnField();
	Point getRealPosition(Point location, Point localCoordinate);
public:
	bool isFly;
	void generate(Type type);
	void rotate();
	void moveLeft();
	void moveRight();
	void moveDown();
};
#endif