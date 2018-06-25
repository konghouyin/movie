/*
* File name:  Schedule_UI.c
* File ID:	  TTMS_SSF_Schedule_UI_Sour
* Author:     Huang Ru
* Version:    V1.0
* Date: 	  2015-04-25
*/

#define SCHEDULE_PAGE_SIZE 5;
#include "Schedule_UI.h"
#include "Play_UI.h"

#include "../Common/list.h"
#include "../Service/Schedule.h"
#include "../Service/Play.h"
#include "../Service/Studio.h"
#include "../Service/EntityKey.h"
#include "../Service/Seat.h"
#include "../Service/Ticket.h"
#include "../Common/window.h"

#include "conio.h"
#include <stdio.h>
#include <stdlib.h>

/*
* Function:    Schedule_UI_ListAll
* Function ID:	TTMS_SCU_Schedule_UI_List
* Description: ��ʾ���е��ݳ��ƻ���Ϣ,���в�ѯ��
* Input:       ��
* Output:      ���о�Ŀ����Ϣ
* Return:      ��
*/
void Schedule_UI_ListAll(void) {
	int i;
	schedule_list_t head;          //˫������Ķ���  
	schedule_node_t *pos;          //˫�������һ�����  
	char choice;
	Pagination_t paging;
	List_Init(head, schedule_node_t);        //����
	paging.offset = 0;       //��ʼ��  ��¼ 
	paging.pageSize = SCHEDULE_PAGE_SIZE;
	//��������
	paging.totalRecords = Schedule_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);
	//��ʾ����
	
	printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n");
	printf("\t\t\t%8s %8s %10s %15s    %14s %12s\n", "�ƻ�ID��", "��ĿID��", "��ӳ��ID��", "�ݳ�����", "�ݳ�ʱ��", "��λ����");
	printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n");
	//��ʾ����
	for (i = 0, pos = (schedule_node_t *)(paging.curPos);
		pos != head && i < paging.pageSize; i++) {
		printf("\t\t\t%5d %8d %8d    %8d��%02d��%02d��   %8dʱ%02d��%02d��  %3d\n\n", pos->data.id,
			pos->data.play_id, pos->data.studio_id, pos->data.date.year, pos->data.date.month, pos->data.date.day,
			pos->data.time.hour, pos->data.time.minute, pos->data.time.second, pos->data.seat_count);
		pos = pos->next;
	}
	goto_xy(0, 23);
	printf("\t\t\t      --------- �ƻ�����:%2d ---------------------------- ҳ�� %2d/%2d ------\n\n",
		paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));
	printf("\t\t\t*******************************************************************************\n");
	printf("\t\t\t[P]��һ��  [N]��һ��   |   [A]����   [D]ɾ��   [U]�޸�   [Q]��ѯ   [R]����");
	printf("\n\t\t\t================================================================================\n");
	printf("\t\t\t\t��ѡ��:");
	
}
void Schedule_UI_ListAll1(void)
{
	int id;
	char choice;
	char ch;
	int i;
	schedule_list_t head;          //˫������Ķ���  
	schedule_node_t *pos;          //˫�������һ�����  
	Pagination_t paging;
	List_Init(head, schedule_node_t);        //����
	paging.offset = 0;       //��ʼ��  ��¼ 
	paging.pageSize = SCHEDULE_PAGE_SIZE;
	//��������
	paging.totalRecords = Schedule_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);
	//��ʾ����
	do {
		system("cls");
		kuangjia();
		goto_xy(0, 7);
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n");
		printf("\t\t\t%8s %8s %10s %15s    %14s %12s\n", "�ƻ�ID��", "��ĿID��", "��ӳ��ID��", "�ݳ�����", "�ݳ�ʱ��", "��λ����");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n");
		//��ʾ����
		for (i = 0, pos = (schedule_node_t *)(paging.curPos);
			pos != head && i < paging.pageSize; i++) {
			printf("\t\t\t%5d %8d %8d    %8d��%02d��%02d��   %8dʱ%02d��%02d��  %3d\n\n", pos->data.id,
				pos->data.play_id, pos->data.studio_id, pos->data.date.year, pos->data.date.month, pos->data.date.day,
				pos->data.time.hour, pos->data.time.minute, pos->data.time.second, pos->data.seat_count);
			pos = pos->next;
		}
		goto_xy(0, 23);
		printf("\t\t\t      --------- �ƻ�����:%2d ---------------------------- ҳ�� %2d/%2d ------\n\n",
			paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));
		printf("\t\t\t*******************************************************************************\n");
		printf("\t\t\t       [P]��һ��  [N]��һ��                      [Q]��ѯ   [R]����");
		printf("\n\t\t\t================================================================================\n");
		printf("\t\t\t\t��ѡ��:");
		while (_kbhit()) { getch(); }
		choice = getche();
		while (_kbhit()) { getch(); }
		switch (choice)
		{
		case 'q':
		case 'Q':
			printf("\t\t\t����Ҫ���ҵ�ID:");
			while (scanf("%d", &id) != 1)
			{
				printf("\t\t\t������Ĳ�������");
				printf("\t\t\t���������룺");
				while ((ch = getchar()) != '\n')
					continue;
			}
			while (_kbhit()) { getch(); }
			Schedule_UI_Query(id);
			break;
		case 'p':
		case 'P':
			if (1<Pageing_CurPage(paging))
			{
				Paging_Locate_OffsetPage(head, paging, -1, schedule_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (Pageing_TotalPages(paging)>Pageing_CurPage(paging))
			{
				Paging_Locate_OffsetPage(head, paging, 1, schedule_node_t);
			}
			break;

		}
	}while ((choice != 'r' ) && ( choice != 'R'));
	return;
}

/*
* Function:    Schedule_UI_Add
* Function ID:	TTMS_SCU_Schedule_UI_Add
* Description: ���һ���ݳ��ƻ���Ϣ
* Input:       ��ؾ�Ŀ��ID��
* Output:      ������Ϣʱ�ĸ�����ʾ
* Return:      ��ӵļ�¼��
*/
int Schedule_UI_Add(void) {
	schedule_t rec;
	seat_list_t list;
	List_Init(list, seat_node_t);
	char choice;
	int newRecCount = 0;
	//rec.play_id = play_id;
	do {
		system("cls");
		kuangjia();
		goto_xy(30, 7);
		printf("              ---->>    �����ݳ��ƻ�    <<----\n");
		goto_xy(30, 8);
		printf("\t       ==============================================\n");

		while (_kbhit()){getch();}
		printf("\n\t\t\t\t\t\t��Ŀ ID: ");
		scanf("%d", &rec.play_id);
		printf("\n\t\t\t\t\t\t�ݳ��� ID: ");
		scanf("%d", &rec.studio_id);
		printf("\n\t\t\t\t\t\t��������: ");
		scanf("%d%d%d", &rec.date.year, &rec.date.month, &rec.date.day);
		printf("\n\t\t\t\t\t\t����ʱ��: ");
		scanf("%d%d%d", &rec.time.hour, &rec.time.minute, &rec.time.second);
		getchar();

		printf("\n\t\t\t\t        ==========================================\n");

		//��ȡ����
		char type[] = "Schedule";
		rec.id = EntKey_Srv_CompNewKey(type);
		rec.seat_count = Seat_Srv_FetchValidByRoomID(list, rec.studio_id);

		if (Schedule_Srv_Add(&rec) && Ticket_Srv_AddBatch(rec.id, rec.studio_id)) {
			newRecCount += 1;
			printf("\t\t\t\t\t\t���ݳ��ƻ���ӳɹ�!\n");
		}
		else {
			printf("\t\t\t\t\t�ݳ��ƻ����ʧ��!\n");
			Schedule_Srv_DeleteByID(rec.id);
		}
		printf("\t\t\t\t-------------------------------------------------------\n");
		printf("\t\t\t\t\t     [A]�������            [R]����:");
		while (_kbhit()){getch();}
		choice = getche();
	} while ('a' == choice || 'A' == choice);
	return newRecCount;
}

/*
* Function:    Schedule_UI_Modify
* Function ID:	TTMS_SCU_Schedule_UI_Mod
* Description: ����ID�Ÿ����ݳ��ƻ���Ϣ
* Input:       �����µľ�ĿID��
* Output:      ������Ϣʱ�ĸ�����ʾ
* Return:      ���µľ�Ŀ��Ϣ����0��ʾδ�ҵ���1��ʾ�ҵ�������
*/
int Schedule_UI_Modify(int id) {

	schedule_t rec;
	int rtn = 0;

	/*Load record*/
	if (!Schedule_Srv_FetchByID(id, &rec)) {
		printf("\t\t\t\t��ĿID������!\t\t\t�� [Enter] ����\n\t\t\t");
		getchar();
		getchar();
		return 0;
	}

	//����	
	system("cls");
	kuangjia();
	goto_xy(30, 7);
	printf("              ---->>    �޸��ݳ��ƻ�    <<----\n");
	goto_xy(30, 8);
	printf("\t       ==============================================\n");

	while (_kbhit()){getch();}
	printf("\t\t\t\t\t\t��Ŀ ID:");
	scanf("%d", &rec.play_id);
	printf("\t\t\t\t\t\t�ݳ��� ID:");
	scanf("%d", &rec.studio_id);
	printf("\t\t\t\t\t\t��������:");
	scanf("%d%d%d", &rec.date.year, &rec.date.month, &rec.date.day);
	printf("\t\t\t\t\t\t����ʱ��:");
	scanf("%d%d%d", &rec.time.hour, &rec.time.minute, &rec.time.second);
	getchar();

	printf("\n\t\t\t\t        ==========================================\n");

	rec.seat_count = Ticket_Srv_AddBatch(rec.id, rec.studio_id);
	if (Schedule_Srv_Modify(&rec)) {
		rtn = 1;
		printf(
			"\t\t\t\t\t�ݳ��ƻ��޸ĳɹ�!\t\t�� [Enter] ����\n\t\t\t");
	}
	else
		printf("\t\t\t\t\t�ݳ��ƻ��޸�ʧ��!\t\t\t�� [Enter] ����\n\t\t\t");
	getchar();
	getchar();
	return rtn;
}


/*
* Function:    Schedule_UI_Delete
* Function ID:	TTMS_SCU_Schedule_UI_Del
* Description: ����ID��ɾ���ݳ��ƻ���Ϣ
* Input:       ��ɾ���ľ�ĿID��
* Output:      ��ʾɾ���Ƿ�ɹ�
* Return:      0��ʾɾ��ʧ�ܣ�1��ʾɾ���ɹ�
*/
int Schedule_UI_Delete(int id) {
	int rtn = 0;
	schedule_t rec;

	if (!Schedule_Srv_FetchByID(id, &rec)) {
		printf("\t\t\t\t��ĿID������!\t\t\t�� [Enter] ����\n\t\t\t");
		getchar();
		getchar();
		return 0;
	}

	goto_xy(0, 28);
	printf("\t\t\t                                                                                            \n");
	printf("\t\t\t                                                                                            \n");
	printf("\t\t\t                                                                                            \n");
	goto_xy(0, 28);
	printf("\t\t\t\t�Ƿ�ȷ��ɾ�� ID �� %d �ļƻ�( Y / N )", id);
	char ch = getche();
	if (ch != 'Y'&&ch != 'y')
		return 0;

	/*if ( Ticket_Srv_DeleteBatch(rec.studio_id) && Schedule_Srv_DeleteByID(id))*/ 
	if (Schedule_Srv_DeleteByID(id)) 
	{
		printf("\t\t\t�ݳ��ƻ�ɾ���ɹ�!\n\t\t\t");
		rtn = 1;
	}
	else {
		printf("\t\t\t�ݳ��ƻ�ɾ��ʧ��!\n\t\t\t�� [Enter] ����\n\t\t\t");
	}
	getchar();
	getchar();
	return rtn;
}

/*
* Function:    Schedule_UI_Query
* Function ID:	TTMS_SCU_Schedule_UI_Qry
* Description: ����ID�Ų�ѯ�ݳ��ƻ���Ϣ
* Input:       �����ҵľ�ĿID��
* Output:      ���ҵ��ľ�Ŀ��Ϣ
* Return:      0��ʾδ�ҵ���1��ʾ�ҵ���
*/
int Schedule_UI_Query(int id) {
	int rtn = 1;
	schedule_t  buf;
	schedule_t rec;

	if (!Schedule_Srv_FetchByID(id, &rec)) {
		printf("\t\t\t\t��ĿID������!\t\t\t�� [Enter] ����\n\t\t\t");
		getchar();
		getchar();
		return 0;
	}


	if (Schedule_Srv_FetchByID(id, &buf)) {
		system("cls");
		kuangjia();
		goto_xy(30, 7);
		printf("              ---->>    IDΪ %2d ���ݳ��ƻ�    <<----\n",buf.id);
		goto_xy(30, 8);
		printf("\t       ==============================================\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n");
		printf("\t\t\t%8s %8s %10s %15s    %14s %12s\n", "�ƻ�ID��", "��ĿID��", "��ӳ��ID��", "�ݳ�����", "�ݳ�ʱ��", "��λ����");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n");
		//��ʾ����

		printf("\t\t\t%5d %8d %8d    %8d��%02d��%02d��   %8dʱ%02d��%02d��  %3d\n\n", buf.id,
			buf.play_id, buf.studio_id, buf.date.year, buf.date.month, buf.date.day,
			buf.time.hour, buf.time.minute, buf.time.second, buf.seat_count);
				
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n");
		printf("\t\t\t\t\t\t���� [Enter] ����");
		while (getchar() != '\n');
	}
	else
	{
		printf("\t\t\t���Ҳ������ݳ��ƻ���");
	}
	getchar();
	return rtn;
}

/*
* Function:    Schedule_UI_ListByPlay
* Function ID:	TTMS_SCU_Schedule_UI_ListByPlay
* Description: ���б�ģʽ��ʾ������Ŀ���ݳ��ƻ���Ϣ
* Input:       listΪ���ҵ����ݳ��ƻ���Ϣ�����ͷָ�룬playΪ��Ŀ��Ϣ��pagingΪ��ʾ��ҳ���ò���
* Output:      ��
* Return:      ���ز��ҵ��ļ�¼��Ŀ
*/
void Schedule_UI_ListByPlay(const play_t *play, schedule_list_t list, Pagination_t paging) {


}

/*
* Function:    Schedule_UI_MgtEntry
* Function ID:	TTMS_SCU_Schedule_UI_MgtEnt
* Description: �ݳ��ƻ�������棬�ݳ��ƻ����վ�Ŀ���й����Ծ�ĿID��Ϊ����
* Input:       ��ؾ�ĿID��
* Output:      �ݳ��ƻ���Ϣ
* Return:      ��
*/
void Schedule_UI_MgtEntry(void) {
	int id;
	char choice;
	char ch;
	schedule_list_t head;
	//schedule_node_t *pos;
	Pagination_t paging;
	List_Init(head, schedule_node_t);
	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;
	//��������
	paging.totalRecords = Schedule_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);
	do {
		system("cls");
		kuangjia();
		goto_xy(30, 5);
		printf("              ---->>      ��ӳ��Ŀ�б�    <<----\n");

		printf("\t\t\t==============================================================================\n\n");
		Schedule_UI_ListAll();

		while (_kbhit()){getch();}
		choice = getche();
		while (_kbhit()){getch();}
		switch (choice)
		{
		case 'a':
		case 'A':
			//����ݳ��ƻ�
			if (Schedule_UI_Add())     //����ӳɹ����������һҳ��ʾ
			{
				paging.totalRecords = Schedule_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, schedule_node_t);
			}
			break;
		case 'u':
		case 'U':
			//�޸��ݳ��ƻ�
			printf("\t\t\t���� ID:");
			while (scanf("%d", &id) != 1)
			{
				printf("\t\t\t������Ĳ�������\n");
				printf("\t\t\t���������룺");
				while ((ch = getchar()) != '\n')
					continue;
			}
			while (_kbhit()){getch();}
			if (Schedule_UI_Modify(id)) {	//������������
				paging.totalRecords = Schedule_Srv_FetchAll(head);
				List_Paging(head, paging, schedule_node_t);
			}
			break;
		case 'd':
		case 'D':
			//ɾ���ݳ��ƻ�
			printf("\t\t\t���� ID:");
			scanf("%d", &id);
			while (_kbhit()){getch();}
			if (Schedule_UI_Delete(id)) {	//������������
				paging.totalRecords = Schedule_Srv_FetchAll(head);
				List_Paging(head, paging, schedule_node_t);
			}
			break;
		case 'q':
		case 'Q':
			printf("\t\t\t����Ҫ���ҵ�ID:");
			while (scanf("%d", &id) != 1)
			{
				printf("\t\t\t������Ĳ�������\n");
				printf("\t\t\t���������룺");
				while ((ch = getchar()) != '\n')
					continue;
			}
			while (_kbhit()){getch();}
			Schedule_UI_Query(id);
			break;
		case 'p':
		case 'P':
			if (1<Pageing_CurPage(paging))
			{
				Paging_Locate_OffsetPage(head, paging, -1, schedule_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (Pageing_TotalPages(paging)>Pageing_CurPage(paging))
			{
				Paging_Locate_OffsetPage(head, paging, 1, schedule_node_t);
			}
			break;
		}
	} while (choice != 'R' && choice != 'r');
	//�ͷ�����ռ�
	List_Destroy(head, schedule_node_t);
}
