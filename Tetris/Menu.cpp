#include "Menu.h"

short mainMenu()
{
	short mode = 0;
	char key = 0;
	printMenu(mode);

	while (true)
	{
		if (kbhit())
		{
			key = getch();
			switch (key)
			{
			case ENTER_KEY:
				return -(mode + 1);
			case MAGIC:
				key = getch();
				mode += changeCursorPosition(key);
				if (mode < 0)
					mode = 0;
				if (mode > 2)
					mode = 2;
				break;
			}
			printMenu(mode);
		}
	}
}

void printMenu(int cursorPosition)
{
	system("cls");

	char cursor[3] = { ' ',' ',' ' };
	cursor[cursorPosition] = '>';

	printf("##########################################\n");
	printf("#                                        #\n");
	printf("# #####   ####  #####   ###   ###   #### #\n");
	printf("#   #    #        #    #   #   #   #     #\n");
	printf("#   #     ####    #      # #   #    ###  #\n");
	printf("#   #    #        #    #   #   #       # #\n");
	printf("#   #     ####    #    #   #  ###  ####  #\n");
	printf("#                                        #\n");
	printf("##########################################\n");
	printf("#                                        #\n");
	printf("# %c Start game                           #\n", cursor[0]);
	printf("#                                        #\n");
	printf("# %c Records table                        #\n", cursor[1]);
	printf("#                                        #\n");
	printf("# %c Exit                                 #\n", cursor[2]);
	printf("#                                        #\n");
	printf("##########################################\n\n");

}

short changeCursorPosition(char key)
{
	switch (key)
	{
	case UP_KEY:
		return -1;
	case DOWN_KEY:
		return 1;
	default:
		return 0;
	}
}
