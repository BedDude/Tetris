#include "Menu.h"
#include "Records.h"
#include "Game.h"

enum Codes
{
	MAIN_MENU_CODE = -4,
	EXIT_CODE,
	RECORDS_CODE,
	NEW_GAME_CODE
};

int main()
{
	int something = mainMenu();
	while (true)
		switch (something)
		{
		case MAIN_MENU_CODE:
			something = mainMenu();
			break;
		case RECORDS_CODE:
			something = recordsTable();
			break;
		case NEW_GAME_CODE:
			something = game();
			break;
		case EXIT_CODE:
			return 0;
		default:
			something = addNewRecord(something);
			break;
		}
}