#include "Play_UI.h"
#include "Schedule_UI.h"
#include "../Common/list.h"
#include "../Service/Play.h"
#include "../Service/EntityKey.h"
#include "../Common/window.h"
#include <stdio.h>
#include <stdlib.h>
#include "Studio_UI.h"
#include<conio.h>
#include<string.h>


extern account_t gl_CurUser;

/*
* Function:    Play_UI_ShowList
* Function ID:	TTMS_SCU_Play_UI_Show
* Description: ���б�ģʽ��ʾ��Ŀ��Ϣ
* Input:       list��Ŀ��Ϣ�����ͷָ�룬paging��ҳ���ò���
* Output:      ���о�Ŀ����Ϣ
* Return:      ���ز��ҵ��ļ�¼��Ŀ
*/
void Play_UI_ShowList(play_list_t list, Pagination_t paging) {
	int i;
	play_node_t *pos;

	system("cls");
	kuangjia();
	goto_xy(30, 8);
	printf("              ---->>      ��ӳ��Ŀ�б�    <<----\n");

	printf("\t\t\t==============================================================================\n");
	for (i = 0, pos = (play_node_t *)(paging.curPos); pos != list && i < paging.pageSize; i++)
	{
		goto_xy(38, 11);
		printf("Ƭ����%s", pos->data.name);
		goto_xy(38, 13);
		printf("���ࣺ%s", type(pos->data.type));
		goto_xy(38, 15);
		printf("�ȼ���%s", rating(pos->data.rating));
		goto_xy(38, 17);
		printf("ʱ����%d����", pos->data.duration);
		goto_xy(38, 19);
		printf("�۸�%dԪ", pos->data.price);


		goto_xy(68, 11);
		printf("ID��%d", pos->data.id);
		goto_xy(68, 13);
		printf("������%s", pos->data.area);
		goto_xy(68, 15);
		printf("��ӳ���ڣ�%4d-%02d-%02d", pos->data.start_date.year, pos->data.start_date.month, pos->data.start_date.day);
		goto_xy(68, 17);
		printf("�¼����ڣ�%4d-%02d-%02d\n\n\n\n", pos->data.end_date.year, pos->data.end_date.month, pos->data.end_date.day);

		pos = pos->next;
	}
	//��Ŀ���Ͷ��壬1��ʾ��Ӱ��2��ʾ��磬3��ʾ���ֻ�
	//�ݳ��������Ͷ��壬1��ʾ��ͯ�ɹۿ���2��ʾ������ɹۿ���3��ʾ���˿ɹۿ�

}

/*
* Function:    Play_UI_MgtEntry
* Function ID:	TTMS_SCU_Play_UI_MgtEnt
* Description: ��Ŀ��Ϣ�������
* Input:       flagΪ0���������ҳ�棬flagΪ1�����ѯ����
* Output:      ��Ŀ�������
* Return:      ��
*/
void  Play_UI_MgtEntry(int flag) {
	int i, id;
	char choice;
	play_list_t head;
	play_node_t *pos;
	Pagination_t paging;
	List_Init(head, play_node_t);
	paging.offset = 0;
	paging.pageSize = PLAY_PAGE_SIZE;
	//��������
	paging.totalRecords = Play_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);

	if (flag)
	{
		do {
			system("cls");
			Play_UI_ShowList(head, paging); 
			printf("\t\t\t\t------- ��Ŀ����:%2d ---------------------------- λ�� %2d/%2d ------\n",
				paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));
			printf("\t\t\t    ************************************************************************  \n");
			printf("\t\t\t          [P]��һ��  [N]��һ��                        [Q]��ѯ   [R]����");
			printf("\n\t\t\t================================================================================\n");
			printf("\t\t\t\t��ѡ��:");
			choice = getche();
			char name[30];
			switch (choice)
			{
			case 'q':
			case 'Q':
				printf("\t\t\t\t�������ѯƬ��: ");
				scanf("%s", name);


				getchar();
				if (Play_UI_Query_Name(name)) {	//������������
					paging.totalRecords = Play_Srv_FetchAll(head);
					List_Paging(head, paging, play_node_t);
				}
				break;
			case 'p':
			case 'P':
				if (1 < Pageing_CurPage(paging)) {
					Paging_Locate_OffsetPage(head, paging, -1, play_node_t);
				}
				break;

			case 'n':
			case 'N':
				if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
					Paging_Locate_OffsetPage(head, paging, 1, play_node_t);
				}
				break;
			}
		} while (choice != 'r' && choice != 'R');
	}
	else
	{
		do {
			system("cls");
			Play_UI_ShowList(head, paging);
			goto_xy(0, 22);
			printf("\t\t\t\t--------- ��Ŀ����:%2d ---------------------------- λ�� %2d/%2d ------\n\n",
				paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));
			printf("\t\t\t*******************************************************************************\n");
			printf("\t\t\t[P]��һ��  [N]��һ��   |   [A]����  [D]ɾ��  [U]�޸�  [Q]��ѯ  [S]�ƻ�  [R]����");
			printf("\n\t\t\t================================================================================\n");
			printf("\t\t\t\t��ѡ��: ");
			while (_kbhit())
			{
				getch();
			}
			char ch;
			char name[30];
			choice = getche();
			switch (choice)
			{
			case 's':
			case 'S':
				Schedule_UI_MgtEntry();
				break;
			case 'a':
			case 'A':
				if (Play_UI_Add()) //����ӳɹ����������һҳ��ʾ
				{
					paging.totalRecords = Play_Srv_FetchAll(head);
					Paging_Locate_LastPage(head, paging, play_node_t);
				}
				break;
			case 'd':
			case 'D':
				printf("\t\t\t������ɾ��ID: ");
				scanf("%d", &id);
				getchar();
				if (Play_UI_Delete(id)) {	
					//������������
					paging.totalRecords = Play_Srv_FetchAll(head);
					List_Paging(head, paging, play_node_t);
				}
				break;
			case 'u':
			case 'U':
				printf("\t\t\t������Ҫ�޸ĵ�ID��: ");
				scanf("%d", &id);
				getchar();
				if (Play_UI_Modify(id)) {	//������������
					paging.totalRecords = Play_Srv_FetchAll(head);
					List_Paging(head, paging, play_node_t);
				}
				break;
			case 'q':
			case 'Q':
				printf("\t\t\t������Ҫ��ѯ��Ƭ��: ");
				scanf("%s", name);
				getchar();
				if (Play_UI_Query_Name(name)) {	//������������
					paging.totalRecords = Play_Srv_FetchAll(head);
					List_Paging(head, paging, play_node_t);
				}
				break;
			case 'p':
			case 'P':
				if (1 < Pageing_CurPage(paging)) {
					Paging_Locate_OffsetPage(head, paging, -1, play_node_t);
				}
				break;
			case 'n':
			case 'N':
				if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
					Paging_Locate_OffsetPage(head, paging, 1, play_node_t);
				}
				break;
			}
		} while (choice != 'r' && choice != 'R');
	}
}

int Play_UI_ShowList_schedule(play_list_t list, Pagination_t paging) {
	int i;
	play_node_t *pos;


	goto_xy(25, 11);
	printf("    ---->>     ��ѡ�б�    <<----\n");


	for (i = 0, pos = (play_node_t *)(paging.curPos); pos != list && i < paging.pageSize; i++)
	{
		goto_xy(35, 13);
		printf("Ƭ����%s         ", pos->data.name);
		goto_xy(35, 15);
		printf("���ࣺ%s         ", type(pos->data.type));
		goto_xy(35, 17);
		printf("�ȼ���%s         ", rating(pos->data.rating));
		goto_xy(35, 19);
		printf("ʱ����%d����      ", pos->data.duration);
		goto_xy(35, 21);
		printf("�۸�%dԪ        ", pos->data.price);
		pos = pos->next;
	}
	return pos->prev->data.id;

}

int Play_UI_MgtEntry_schedule(void) {
	int i, id;
	char choice;
	play_list_t head;
	play_node_t *pos;
	Pagination_t paging;
	List_Init(head, play_node_t);
	paging.offset = 0;
	paging.pageSize = PLAY_PAGE_SIZE;
	//��������
	paging.totalRecords = Play_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);

		do {

			id=Play_UI_ShowList_schedule(head, paging);
			printf("\n\n\t\t         --- ��Ŀ����:%2d ------ λ�� %2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));
			printf("\t\t      ********************************************** \n");
			printf("\t\t        [P]��һ�� [N]��һ�� | [Y]ȷ�� [W]�ֶ�����");
			printf("\n\t\t     ===============================================\n");

			choice = getch();
			char name[30];
			switch (choice)
			{
				break;
			case 'p':
			case 'P':
				if (1 < Pageing_CurPage(paging)) {
					Paging_Locate_OffsetPage(head, paging, -1, play_node_t);
				}
				break;

			case 'n':
			case 'N':
				if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
					Paging_Locate_OffsetPage(head, paging, 1, play_node_t);
				}
				break;
			case 'y':
			case 'Y':
				return id;
			case 'w':
			case 'W':
				return 0;
			}
		} while (1);
	

}
//Ϊ�ݳ��ƻ�����ṩ����


/*
* Function:    Play_UI_Add
* Function ID:	TTMS_SCU_Play_UI_Add
* Description: ���һ����Ŀ��Ϣ
* Input:       ��
* Output:      ������Ϣʱ�ĸ�����ʾ
* Return:      ��ӵļ�¼��
*/
int Play_UI_Add(void) {

	play_t rec;
	char choice;
	int newRecCount = 0;

	do {
		system("cls");
		kuangjia();
		goto_xy(30, 6);
		printf("              ---->>    ����µľ�Ŀ��Ϣ    <<----\n");
		goto_xy(30, 7);
		printf("\t       ==============================================\n");

		printf("\n\t\t\t\t\t��Ŀ����: ");
		fflush(stdin);
		fgets(rec.name, 30, stdin);
		int l = strlen(rec.name);
		rec.name[l - 1] = '\0';

		printf("\n\t\t\t\t\t��Ŀ���ͣ�1--��Ӱ��2--��磬3--���ֻᣩ: ");
		scanf("%d", &rec.type);//��Ŀ���Ͷ��壬1--��Ӱ��2--��磬3--���ֻ�

		printf("\n\t\t\t\t\t��Ŀ����: ");
		getchar();
		fgets(rec.area, 8, stdin);
		l = strlen(rec.area);
		rec.area[l - 1] = '\0';

		printf("\n\t\t\t\t\t��Ŀ�ּ���1--��ͯ��2--�����꣬3--���ˣ�: ");
		scanf("%d", &rec.rating);//�ݳ��������Ͷ��壬1��ʾ��ͯ�ɹۿ���2��ʾ������ɹۿ���3��ʾ���˿ɹۿ�

		printf("\n\t\t\t\t\t����ʱ�䣨��λ-���ӣ�: ");
		scanf("%d", &rec.duration);

		printf("\n\t\t\t\t\t�ϼ����� (�� �� ��): ");
		scanf("%d%d%d", &rec.start_date.year, &rec.start_date.month, &rec.start_date.day);

		printf("\n\t\t\t\t\t�¼����� (�� �� ��): ");
		scanf("%d%d%d", &rec.end_date.year, &rec.end_date.month, &rec.end_date.day);

		printf("\n\t\t\t\t\t��ĿƱ�ۣ�Ԫ��: ");
		scanf("%d", &rec.price);

		getchar();
		printf("\n\t\t\t\t  =======================================================\n");

		//��ȡ����
		char type[] = "Play";
		rec.id = EntKey_Srv_CompNewKey(type);

		if (Play_Srv_Add(&rec)) {
			newRecCount += 1;
			printf("\n\t\t\t\t\t��Ŀ��ӳɹ�!");
		}
		else
			printf("\t\t\t\t\t��Ŀ���ʧ��!");
		printf("\t\t[A]���     [R]����");

		while (_kbhit())
		{
			getch();
		}
		choice = getche();
	} while ('a' == choice || 'A' == choice);
	return newRecCount;
}

/*
* Function:    Play_UI_Modify
* Function ID:	TTMS_SCU_Play_UI_Mod
* Description: ���¾�Ŀ��Ϣ
* Input:       �����µľ�ĿID��
* Output:      ������Ϣʱ�ĸ�����ʾ
* Return:      ���µľ�Ŀ��Ϣ����0��ʾδ�ҵ���1��ʾ�ҵ�������
*/
int Play_UI_Modify(int id) {
	play_t rec;
	int rtn = 0;

	/*Load record*/
	if (!Play_Srv_FetchByID(id, &rec)) {
		printf("\t\t\t\t��Ŀ������!\t\t\t�� [Enter] ����\n");
		getchar();
		return 0;
	}
	//����	
	system("cls");
	kuangjia();
	goto_xy(30, 6);
	printf("              ---->>    �޸ľ�Ŀ��Ϣ    <<----\n");
	goto_xy(30, 7);
	printf("\t       ==============================================\n");
	printf("\n\t\t\t\t\t��Ŀ����: ");
	fflush(stdin);
	fgets(rec.name, 30, stdin);
	int l = strlen(rec.name);
	rec.name[l - 1] = '\0';

	printf("\n\t\t\t\t\t��Ŀ����:��1--��Ӱ��2--��磬3--���ֻᣩ ");
	scanf("%d", &rec.type);//��Ŀ���Ͷ��壬1--��Ӱ��2--��磬3--���ֻ�

	printf("\n\t\t\t\t\t��Ŀ����: ");
	getchar();
	fgets(rec.area, 8, stdin);
	l = strlen(rec.area);
	rec.area[l - 1] = '\0';

	printf("\n\t\t\t\t\t��Ŀ�ּ�:��1--��ͯ��2--�����꣬3--���ˣ�");
	scanf("%d", &rec.rating);//�ݳ��������Ͷ��壬1��ʾ��ͯ�ɹۿ���2��ʾ������ɹۿ���3��ʾ���˿ɹۿ�

	printf("\n\t\t\t\t\t����ʱ�䣨��λ-���ӣ�: ");
	scanf("%d", &rec.duration);

	printf("\n\t\t\t\t\t�ϼ����� (�� �� ��): ");
	scanf("%d%d%d", &rec.start_date.year, &rec.start_date.month, &rec.start_date.day);

	printf("\n\t\t\t\t\t�¼����� (�� �� ��): ");
	scanf("%d%d%d", &rec.end_date.year, &rec.end_date.month, &rec.end_date.day);

	printf("\n\t\t\t\t\t��ĿƱ�ۣ�Ԫ��: ");
	scanf("%d", &rec.price);

	getchar();
	printf("\n\t\t\t\t  =======================================================\n");

	

	if (Play_Srv_Modify(&rec)) {
		rtn = 1;
		printf(
			"\t\t\t\t\t��Ŀ��Ϣ�޸ĳɹ�!\t\t�� [Enter] ����\n\t\t\t");
	}
	else
		printf("\t\t\t\t\t��Ŀ��Ϣ�޸�ʧ��!t\t�� [Enter] ����\n\t\t\t");
	getchar();
	return rtn;
}

/*
* Function:    Play_UI_Delete
* Function ID:	TTMS_SCU_Play_UI_Del
* Description: ����ID��ɾ����Ŀ��Ϣ
* Input:       ��ɾ���ľ�ĿID��
* Output:      ��ʾɾ���Ƿ�ɹ�
* Return:      0��ʾɾ��ʧ�ܣ�1��ʾɾ���ɹ�
*/
int Play_UI_Delete(int id) {

	int rtn = 0;
	play_t rec;
	schedule_list_t head;
	List_Init(head, schedule_node_t);
	Schedule_Srv_FetchAll(head);

	if (!Play_Srv_FetchByID(id, &rec))
	{
		printf("\t\t\t\t��ĿID������!\t\t\t�� [Enter] ����\n\t\t\t");
		getchar();
		return 0;
	}
	goto_xy(0, 27);
	printf("\t\t\t                                                                                            \n");
	printf("\t\t\t                                                                                            \n");
	printf("\t\t\t                                                                                            \n");
	goto_xy(0, 27);
	printf("\t\t\t\t�Ƿ�ȷ��ɾ�� ID �� %d �ľ�Ŀ( Y / N )", id);
	char ch = getche();
	if (ch != 'Y'&&ch != 'y')
		return 0;

	if (Schedule_Srv_DeleteByPlay(head, id))
	{
		goto_xy(35, 29);
		printf("��ص��ݳ��ƻ�ɾ���ɹ�!");
		rtn = 1;
	}
	if (Play_Srv_DeleteByID(id)) {
		goto_xy(50, 29);
		printf("��Ŀɾ���ɹ�!\t\t�� [Enter] ����\n\t\t\t");
		rtn = 1;
	}

	getchar();

	return rtn;
}

/*
* Function:    Play_UI_Query
* Function ID:	TTMS_SCU_Play_UI_Qry
* Description: ����ID�Ų�ѯ��Ŀ��Ϣ
* Input:       �����ҵľ�ĿID��
* Output:      ���ҵ��ľ�Ŀ��Ϣ
* Return:      0��ʾδ�ҵ���1��ʾ�ҵ���
*/
int Play_UI_Query(int id) {
	int rtn = 0;
	play_t rec;
	if (!Play_Srv_FetchByID(id, &rec)) {
		printf("\t\t\t\t��ĿID�������!\t\t\t�� [Enter] ����\n\t\t\t");
		getchar();
		return 0;
	}
	//����	
	system("cls");
	kuangjia();
	goto_xy(30, 10);
	printf("              ---->>      ��ѯ�ľ�Ŀ��Ϣ    <<----\n");

	printf("\t\t\t==============================================================================\n");
	goto_xy(38, 13);
	printf("Ƭ����%s", rec.name);
	goto_xy(38, 15);
	printf("���ࣺ%s", type(rec.type));
	goto_xy(38, 17);
	printf("�ȼ���%s", rating(rec.rating));
	goto_xy(38, 19);
	printf("ʱ����%d", rec.duration);
	goto_xy(38, 21);
	printf("�۸�%d", rec.price);


	goto_xy(68, 13);
	printf("ID��%d", rec.id);
	goto_xy(68, 15);
	printf("������%s", rec.area);
	goto_xy(68, 17);
	printf("��ӳ���ڣ�%4d-%02d-%02d", rec.start_date.year, rec.start_date.month, rec.start_date.day);
	goto_xy(68, 19);
	printf("�¼����ڣ�%4d-%02d-%02d\n\n\n\n", rec.end_date.year, rec.end_date.month, rec.end_date.day);

	printf("\n\t\t\t================================================================================\n");

	printf("\t\t\t\t\t�� [Enter] ����\n\t\t\t");
	getchar();
	return 1;
}


int Play_UI_Query_Name(char* name)
{
	int rtn = 0;
	play_t rec;
	play_list_t head;
	List_Init(head, play_node_t);
	Play_Srv_FetchAll(head);

	if (rec=Play_Srv_FetchByName1(head, name),rec.id==0) {
		printf("\t\t\t\t��ѯ�޹�!\t\t\t\t�� [Enter] ����\n\t\t\t");
		getchar();
		return 0;
	}

	//����	
	system("cls");
	kuangjia();
	goto_xy(30, 9);
	printf("              ---->>      ��ѯ�ľ�Ŀ��Ϣ    <<----\n");

	printf("\t\t\t==============================================================================\n");
	goto_xy(38, 12);
	printf("Ƭ����%s", rec.name);
	goto_xy(38, 14);
	printf("���ࣺ%s", type(rec.type));
	goto_xy(38, 16);
	printf("�ȼ���%s", rating(rec.rating));
	goto_xy(38, 18);
	printf("ʱ����%d ����", rec.duration);
	goto_xy(38, 20);
	printf("�۸�%d Ԫ", rec.price);


	goto_xy(68, 12);
	printf("ID��%d", rec.id);
	goto_xy(68, 14);
	printf("������%s", rec.area);
	goto_xy(68, 16);
	printf("��ӳ���ڣ�%4d-%02d-%02d", rec.start_date.year, rec.start_date.month, rec.start_date.day);
	goto_xy(68, 18);
	printf("�¼����ڣ�%4d-%02d-%02d\n\n\n\n", rec.end_date.year, rec.end_date.month, rec.end_date.day);

	printf("\n\t\t\t================================================================================\n");

	printf("\t\t\t\t\t\t\t�� [Enter] ����\n\t\t\t");
	getchar();
	return 1;
}




char *type(int type)
{
	static char back[5];
	if (type == 1)
	{
		strcpy(back, "��Ӱ");
	}
	else if (type == 2)
	{
		strcpy(back,"���" );
	}
	else if (type == 3)
	{
		strcpy(back,"����" );
	}
	else
		strcpy(back,"����" );
	return back;
}
char *rating(int rating)
{
	static char back[8];
	if (rating == 1)
	{
		strcpy(back, "��ͯ��");
	}
	else if (rating == 2)
	{
		strcpy(back, "�����");
	}
	else if (rating == 3)
	{
		strcpy(back,"���˾�" );
	}
	else
		strcpy(back, "����");
	return back;
}
