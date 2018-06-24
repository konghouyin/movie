#include <stdio.h>
#include "Main_Menu.h"
#include "Studio_UI.h"
#include "../Service/Account.h"	
#include "Queries_Menu.h"
#include "Query_Play_UI.h"
#include "Sale_UI.h"
#include "Play_UI.h"
#include "SalesAnalysis_UI.h"
#include "Play_UI.h"	
#include "../Common/window.h"
#include <conio.h>


extern account_t gl_CurUser;

void Main_Menu(account_t usr)//传入的内容类型，作为打印不同菜单的依据
{

	switch (usr.type)
	{
	case 1:
		char choice;
	
		do {
			system("cls");
			kuangjia();
			goto_xy(50, 5);
			printf("%s  ", gl_CurUser.username);
			printf("售票员!   欢迎使用\n");
			goto_xy(30, 7);
			printf("              ---->>    剧院票务管理系统    <<----\n");
			goto_xy(30, 8);
			printf("\t        ==========================================\n");
			printf("\n\t\t\t\t\t\t   [T]售票与退票\n");
			printf("\n\t\t\t\t\t\t   [Q]查询\n");
			printf("\n\t\t\t\t\t\t   [N]销售统计与分析\n");
			printf("\n\t\t\t\t\t\t   [A]修改密码\n");
			printf("\n\t\t\t\t\t\t   [E]退出\n");
			printf("\n\t\t\t\t        ==========================================\n");
			printf("\t\t\t\t\t请输入你的选择: ");
			choice = getche();
			switch (choice) {
			case 'A':
			case 'a':
				Account_UI_MgtEntry();
				break;
			case 'Q':
			case 'q':
				Queries_Menu();
				break;
			case 'T':
			case 't':
				Sale_UI_MgtEntry();
				break;
			case 'N':
			case 'n':
				SalesAanalysis_UI_MgtEntry();
				break;
			}
		} while ('E' != choice && 'e' != choice);

		break;
	case 2:

		do {
			system("cls");
			kuangjia();
			goto_xy(50, 5);
			printf("%s  ", gl_CurUser.username);
			printf("经理!   欢迎使用\n");
			goto_xy(30, 7);
			printf("              ---->>    剧院票务管理系统    <<----\n");
			goto_xy(30, 8);
			printf("\t        ==========================================\n");
			printf("\n\t\t\t\t\t\t   [P]剧目管理\n");
			printf("\n\t\t\t\t\t\t   [Q]查询\n");
			printf("\n\t\t\t\t\t\t   [N]销售统计与分析\n");
			printf("\n\t\t\t\t\t\t   [A]修改密码\n");
			printf("\n\t\t\t\t\t\t   [E]退出\n");


			printf("\n\t\t\t\t        ==========================================\n");
			printf("\t\t\t\t\t请输入你的选择: ");
			choice = getche();
			switch (choice) {
			case 'A':
			case 'a':
				Account_UI_MgtEntry();
				break;
			case 'P':
			case 'p':
				Play_UI_MgtEntry(0);
				break;

			case 'Q':
			case 'q':
				Queries_Menu();
				break;
			case 'N':
			case 'n':
				SalesAanalysis_UI_MgtEntry();
				break;
			}
		} while ('E' != choice && 'e' != choice);
		break;
	case 9:
		do {
			system("cls");
			kuangjia();
			goto_xy(50, 5);
			printf("%s  ", gl_CurUser.username);
			printf("管理员!   欢迎使用\n");

			goto_xy(30, 7);
			printf("              ---->>    剧院票务管理系统    <<----\n");
			goto_xy(30,8);
			printf("\t       ==============================================\n");
			printf("\n\t\t\t\t\t\t   [S] 演出厅管理\n");
			printf("\n\t\t\t\t\t\t   [A] 账户管理\n");
			printf("\n\t\t\t\t\t\t   [E] 退出\n");
			printf("\n\t\t\t\t        ==========================================\n");
			printf("\t\t\t\t\t请输入你的选择:");
			choice = getche();
			switch (choice) {
			case 'S':
			case 's':
				Studio_UI_MgtEntry(usr.type);
				break;
			case 'A':
			case 'a':
				Account_UI_MgtEntry();
				break;
			}
		} while ('E' != choice && 'e' != choice);
		break;
	case 0:
	default:
		system("cls");
		kuangjia();
		goto_xy(50, 5);
		do {
			printf("\n\t\t\t==================================================================\n");
			printf("\t\t\t**************** 剧院票务管理系统 ****************\n");
			printf("\t\t\t[P]演出厅管理\n");
			printf("\t\t\t[Q]查询\n");
			printf("\t\t\t[E]退出\n");
			printf("\n\t\t\t==================================================================\n");
			printf("\t\t\t请输入你的选择:");
			choice = getche();
			switch (choice) {
			case 'Q':
			case 'q':
				Queries_Menu();
				break;
			case 'P':
			case 'p':
				Play_UI_MgtEntry(1);
				break;
			}
		} while ('E' != choice && 'e' != choice);
		break;
	}
	printf("\n\t\t\t");
	getchar();
}
