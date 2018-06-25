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
		printf("              ---->>    剧院信息查询    <<----\n");
		goto_xy(30, 7);
		printf("\t       ==============================================\n");
		printf("\n\t\t\t\t\t\t   [S]场地查询\n");
		printf("\n\t\t\t\t\t\t   [P]剧目查询\n");
		printf("\n\t\t\t\t\t\t   [C]演出计划查询\n");
		printf("\n\t\t\t\t\t\t   [R]返回\n");
		
		printf("\n\t\t\t\t        ==========================================\n");
		printf("\t\t\t\t\t请输入你的选择: ");

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
