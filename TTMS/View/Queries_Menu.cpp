#include <stdio.h>
#include <stdlib.h>

#include "Queries_Menu.h"
#include "Schedule_UI.h"
#include "Studio_UI.h"
#include "Play_UI.h"
#include "conio.h"
#include "../Common/window.h"

void Queries_Menu(void) {
	char choice;
	do {
		system("cls");
		kuangjia();
		goto_xy(50, 5);
		goto_xy(30,6);
		printf("              ---->>    ��Ժ��Ϣ��ѯ    <<----\n");
		goto_xy(30, 7);
		printf("\t       ==============================================\n");
		printf("\n\t\t\t\t\t\t   [S]���ز�ѯ\n");
		printf("\n\t\t\t\t\t\t   [P]��Ŀ��ѯ\n");
		printf("\n\t\t\t\t\t\t   [C]�ݳ��ƻ���ѯ\n");
		printf("\n\t\t\t\t\t\t   [R]����\n");
		
		printf("\n\t\t\t\t        ==========================================\n");
		printf("\t\t\t\t\t���������ѡ��: ");

		while (_kbhit()){getch();}
		choice = getche();
		switch (choice) {
		case 'S':
		case 's':
			Studio_UI_MgtEntry((account_type_t)2);
			break;
		case 'P':
		case 'p':
			Play_UI_MgtEntry(1);
			break;
		case 'C':
		case 'c':
			Schedule_UI_ListAll1();
			break;
		}
	} while ('R' != choice && 'r' != choice);
}
