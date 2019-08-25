#include "Game.h"

char field[HEIGHT][WIDTH];
Brick brick;

int game()
{
	srand(time(NULL));
	system("cls");

	char key;
	char nextType[7];
	int score = 0;
	short counter = 0;
	Type newType = (Type)(rand() % 7);

	newFigure(nextType, newType);

	initField();
	brick.generate((Type)(rand() % 7));

	while (!defeat())
	{
		printField(score, nextType);

		counter++;
		if (counter % getDelay(score) == 0)
		{
			counter = 0;
			brick.moveDown();
		}

		if (!brick.isFly)
		{
			for (int i = 0; i < HEIGHT; i++)
				if (hasFullLine(i))
				{
					score++;
					cleanLine(i);
				}

			brick.generate(newType);
			newType = (Type)(rand() % 7);
			newFigure(nextType, newType);
		}

		if (kbhit())
		{
			key = getch();

			switch (key)
			{
			case MAGIC:
				key = getch();
				control(key);
				break;
			case ESCAPE_KEY:
				return -4;
			}
		}

		_sleep(50);
	}
	return score;
}

bool defeat()
{
	if (!brick.isFly && (field[0][3] == '#' || field[0][4] == '#'))
		return true;
	return false;
}

void control(char key)
{
	switch (key)
	{
	case UP_KEY:
		brick.rotate();
		break;
	case DOWN_KEY:
		brick.moveDown();
		break;
	case LEFT_KEY:
		brick.moveLeft();
		break;
	case RIGHT_KEY:
		brick.moveRight();
		break;
	}
}

void initField()
{
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			field[i][j] = '.';
}

void printField(int score, char nextBrick[7])
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
	printf("###################################################\n");
	printf("#                                                 #\n");
	printf("#  -------------------\t\tScore: %10d #\n", score);
	for (int i = 0; i < HEIGHT; i++)
	{
		printf("# |");

		for (int j = 0; j < WIDTH - 1; j++)
			printf("%c ", field[i][j]);
		printf("%c", field[i][WIDTH - 1]);

		if (i == 3)
			printf("|\t\tNext:             #\n");
		else if (i == 5)
			printf("|\t\t%c %c %c %c           #\n", nextBrick[0], nextBrick[1], nextBrick[2], nextBrick[3]);
		else if (i == 6)
			printf("|\t\t%c %c %c             #\n", nextBrick[4], nextBrick[5], nextBrick[6]);
		else
			printf("|                           #\n");
	}
	printf("#  -------------------                            #\n");
	printf("#                                                 #\n");
	printf("###################################################\n\n\n\n");
}

bool hasFullLine(short line)
{
	for (int i = 0; i < WIDTH; i++)
		if (field[line][i] == '.')
			return false;
	return true;
}

void cleanLine(short line)
{
	for (int i = line; i > 0; i--)
		for (int j = 0; j < WIDTH; j++)
			field[i][j] = field[i - 1][j];
}

void newFigure(char field[7], Type type)
{
	switch (type)
	{
	case I_TYPE:
		createFigure("####   ", field);
		break;
	case J_TYPE:
		createFigure("#   ###", field);
		break;
	case L_TYPE:
		createFigure("  # ###", field);
		break;
	case O_TYPE:
		createFigure("##  ## ", field);
		break;
	case S_TYPE:
		createFigure(" ## ## ", field);
		break;
	case T_TYPE:
		createFigure(" #  ###", field);
		break;
	case Z_TYPE:
		createFigure("##   ##", field);
		break;
	}
}

void createFigure(const char figure[8], char field[7])
{
	for (int i = 0; i < 7; i++)
		field[i] = figure[i];
}

short getDelay(int score)
{
	if (score >= 1000)
		return 1;
	else
		return 10 - (score / 100);
}
