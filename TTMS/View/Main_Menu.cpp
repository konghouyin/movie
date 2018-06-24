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

void Main_Menu(account_t usr)//������������ͣ���Ϊ��ӡ��ͬ�˵�������
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
			printf("��ƱԱ!   ��ӭʹ��\n");
			goto_xy(30, 7);
			printf("              ---->>    ��ԺƱ�����ϵͳ    <<----\n");
			goto_xy(30, 8);
			printf("\t        ==========================================\n");
			printf("\n\t\t\t\t\t\t   [T]��Ʊ����Ʊ\n");
			printf("\n\t\t\t\t\t\t   [Q]��ѯ\n");
			printf("\n\t\t\t\t\t\t   [N]����ͳ�������\n");
			printf("\n\t\t\t\t\t\t   [A]�޸�����\n");
			printf("\n\t\t\t\t\t\t   [E]�˳�\n");
			printf("\n\t\t\t\t        ==========================================\n");
			printf("\t\t\t\t\t���������ѡ��: ");
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
			printf("����!   ��ӭʹ��\n");
			goto_xy(30, 7);
			printf("              ---->>    ��ԺƱ�����ϵͳ    <<----\n");
			goto_xy(30, 8);
			printf("\t        ==========================================\n");
			printf("\n\t\t\t\t\t\t   [P]��Ŀ����\n");
			printf("\n\t\t\t\t\t\t   [Q]��ѯ\n");
			printf("\n\t\t\t\t\t\t   [N]����ͳ�������\n");
			printf("\n\t\t\t\t\t\t   [A]�޸�����\n");
			printf("\n\t\t\t\t\t\t   [E]�˳�\n");


			printf("\n\t\t\t\t        ==========================================\n");
			printf("\t\t\t\t\t���������ѡ��: ");
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
			printf("����Ա!   ��ӭʹ��\n");

			goto_xy(30, 7);
			printf("              ---->>    ��ԺƱ�����ϵͳ    <<----\n");
			goto_xy(30,8);
			printf("\t       ==============================================\n");
			printf("\n\t\t\t\t\t\t   [S] �ݳ�������\n");
			printf("\n\t\t\t\t\t\t   [A] �˻�����\n");
			printf("\n\t\t\t\t\t\t   [E] �˳�\n");
			printf("\n\t\t\t\t        ==========================================\n");
			printf("\t\t\t\t\t���������ѡ��:");
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
			printf("\t\t\t**************** ��ԺƱ�����ϵͳ ****************\n");
			printf("\t\t\t[P]�ݳ�������\n");
			printf("\t\t\t[Q]��ѯ\n");
			printf("\t\t\t[E]�˳�\n");
			printf("\n\t\t\t==================================================================\n");
			printf("\t\t\t���������ѡ��:");
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
