#include "Records.h"

Record list[10];
bool listIsEmpty = true;

short recordsTable()
{
	if (listIsEmpty)
	{
		fillList();
		listIsEmpty = false;
	}

	system("cls");
	printf("##############################\n");
	printf("# Pos |  Name   |    Score   #\n");
	for (int i = 0; i < 10; i++)
	{
		printf("#-----|---------|------------#\n");
		printf("#%3d  |  %s  | %10d #\n", i + 1, list[i].name, list[i].score);
	}
	printf("##############################\n");
	printf("#    ESC - go to main menu   #\n");
	printf("##############################\n");

	while (true)
		if (kbhit())
			if (getch() == ESCAPE_KEY)
				return -4;
}

void fillList()
{
	std::ifstream file("list.rec", std::ios::binary);

	for (int i = 0; i < 10; i++)
		file.read((char*)&list[i], sizeof(Record));

	file.close();
}

void createNewList()
{
	std::ofstream file("list.rec", std::ios::binary);

	for (int i = 0; i < 10; i++)
		file.write((char*)&list[i], sizeof(Record));

	file.close();
}

short addNewRecord(int score)
{
	if (listIsEmpty)
	{
		fillList();
		listIsEmpty = false;
	}

	if (isNewRecord(score))
	{
		char name[6] = "_____";
		char key;
		int short i = 0;

		while (i < 6)
		{
			printRecordWindow(name, score);
			getch();
			key = getch();

			switch (key)
			{
			case BACKSPACE_KEY:
				if (i > 0)
				{
					i--;
					name[i] = '_';
				}
				break;
			case ENTER_KEY:
				i = 6;
				break;
			case SPACE_KEY:
				if (i < 4)
					i++;
				break;
			case ESCAPE_KEY:
				return -2;
				break;
			default:
				if (i < 5)
				{
					name[i] = toupper(key);
					i++;
				}
				break;
			}
		}

		Record newRecord = createNewRecord(name, score);

		for (int i = 0; i < 10; i++)
		{
			if (newRecord.score >= list[i].score)
				std::swap(newRecord, list[i]);
		}

		createNewList();

		return -2;
	}

	return -4;
}

bool isNewRecord(int score)
{
	for (int i = 0; i < 10; i++)
		if (score > list[i].score)
			return true;
	return false;
}

Record createNewRecord(char name[6], int score)
{
	Record newRecord;

	newRecord.score = score;
	for (int i = 0; i < 6; i++)
		newRecord.name[i] = name[i];

	return newRecord;
}

void printRecordWindow(char name[6], int score)
{
	system("cls");
	printf("###########################\n");
	printf("#       NEW RECORD!       #\n");
	printf("###########################\n");
	printf("#                         #\n");
	printf("# Name: %s             #\n", name);
	printf("# Score: %10d       #\n", score);
	printf("#                         #\n");
	printf("###########################\n");
}
