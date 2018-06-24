#include "Studio_UI.h"

#include "./Main_Menu.h"
#include "../Common/list.h"
#include "../Service/Studio.h"
#include "../Service/Seat.h"
#include "../Service/EntityKey.h"
#include "Seat_UI.h"
#include "conio.h"
#include <string.h>
#include "../Common/window.h"

extern account_t gl_CurUser;

static const int STUDIO_PAGE_SIZE = 5;

#include <stdio.h>
//�����ݳ�������
void Studio_UI_MgtEntry(account_type_t type) {
	int i, id;
	char choice;

	studio_list_t head;
	studio_node_t *pos;
	Pagination_t paging;
	List_Init(head, studio_node_t);
	paging.offset = 0;
	paging.pageSize = STUDIO_PAGE_SIZE;
	//��������
	paging.totalRecords = Studio_Srv_FetchAll(head);//ͳ��һ���ж����ݳ���������������
	Paging_Locate_FirstPage(head, paging);//��λ����ҳ���ĵ�һҳ
	//��ҳ��û�����½��б�ֻ��ͨ����ز�������λ����Ҫ��ӡ��Ϣ�ĵ�ַ
	if (type == 9) {
		do {
			system("cls");
			kuangjia();
			goto_xy(30, 6);
			printf("                  ---->>    �ݳ����б�    <<----\n");
			printf("\t\t\t------------------------------------------------------------------------------\n");
			printf("\t\t\t    %-5s     %-18s    %-12s    %-12s   %-12s\n", "ID", "��������", "����",
				"����", "��λ��");
			printf("\t\t\t------------------------------------------------------------------------------\n");
			//��ʾ����
			for (i = 0, pos = (studio_node_t *)(paging.curPos);
				pos != head && i < paging.pageSize; i++)//forѭ����ӡ��ǰҳ����ʼ�����������Ȼ�ȡ��Ҫ��ӡ��һ����Ϣ�ĵ�ַ����ֹ������ѭ������������ͷ�����ӡ���������ֵ��ȣ�����i��
			{
				printf("\t\t\t    %-5d     %-18s    %-12d    %-12d   %-12d\n\n", pos->data.id,
					pos->data.name, pos->data.rowsCount, pos->data.colsCount,
					pos->data.seatsCount);
				pos = pos->next;//ָ����һ���ڵ�
			}
			//��ӡ��ҳ��Ϣ
			goto_xy(0, 21);
			printf("\t\t\t   --------- �ܸ���:%2d -------------------------------- ҳ�� %2d/%2d --------\n\n",
				paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));//�ܸ��������㵱ǰҳ�������ܸ���
			printf("\t\t\t******************************************************************************\n");
			printf("\t\t\t[P]��һҳ|[N]��һҳ             [A]���� |[D]ɾ�� |[U]�޸� | [S]��λ | [R]����");
			printf("\n\t\t\t==============================================================================\n");
			printf("\t\t\t\t��ѡ����:");
			while (_kbhit())
			{
				getch();
			}
			choice = getche();
			switch (choice)
			{
			case 'a':
			case 'A':
				if (Studio_UI_Add()) //����ӳɹ����������һҳ��ʾ
				{
					paging.totalRecords = Studio_Srv_FetchAll(head);//ͳ���ݳ�������������������
					Paging_Locate_LastPage(head, paging, studio_node_t);//��ҳ�����һҳ׼��
				}
				break;
			case 'd':
			case 'D':
				printf("\t\t\t������Ҫɾ�����ݳ���ID:");
				scanf("%d", &id);
				getchar();
				if (Studio_UI_Delete(id)) {	//������������
					paging.totalRecords = Studio_Srv_FetchAll(head);
					List_Paging(head, paging, studio_node_t);//����ƫ������ʹ������ֵ��ո�ɾ����λ��
				}
				break;
			case 'u':
			case 'U':
				printf("\t\t\t������Ҫ�޸ĵ��ݳ���ID:");
				scanf("%d", &id);
				if (Studio_UI_Modify(id)) {	//������������
					paging.totalRecords = Studio_Srv_FetchAll(head);
					List_Paging(head, paging, studio_node_t);
				}
				break;
			case 's':
			case 'S':
				printf("\t\t\t���������λ������ݳ���ID:");
				scanf("%d", &id);
				getchar();
				Seat_UI_MgtEntry(id);
				paging.totalRecords = Studio_Srv_FetchAll(head);
				List_Paging(head, paging, studio_node_t);
				break;
			case 'p':
			case 'P':
				if (1 < Pageing_CurPage(paging)) {
					Paging_Locate_OffsetPage(head, paging, -1, studio_node_t);
				}
				break;
			case 'n':
			case 'N':
				if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
					Paging_Locate_OffsetPage(head, paging, 1, studio_node_t);
				}
				break;
			}
		} while (choice != 'r' && choice != 'R');
	}
	else//����Ա���޸�Ȩ�ޣ�һ���û�ֻ�ܲ��ң������޸�
	{
		do {
			system("cls");
			kuangjia();
			goto_xy(30, 6);
			printf("                  ---->>    �ݳ����б�    <<----\n");
			printf("\t\t\t------------------------------------------------------------------------------\n");
			printf("\t\t\t    %-5s     %-18s    %-12s    %-12s   %-12s\n", "ID", "��������", "����",
				"����", "��λ��");
			printf("\t\t\t------------------------------------------------------------------------------\n");
			//��ʾ����
			for (i = 0, pos = (studio_node_t *)(paging.curPos);
				pos != head && i < paging.pageSize; i++)//forѭ����ӡ��ǰҳ����ʼ�����������Ȼ�ȡ��Ҫ��ӡ��һ����Ϣ�ĵ�ַ����ֹ������ѭ������������ͷ�����ӡ���������ֵ��ȣ�����i��
			{
				printf("\t\t\t    %-5d     %-18s    %-12d    %-12d   %-12d\n\n", pos->data.id,
					pos->data.name, pos->data.rowsCount, pos->data.colsCount,
					pos->data.seatsCount);
				pos = pos->next;//ָ����һ���ڵ�
			}
			//��ӡ��ҳ��Ϣ
			goto_xy(0, 21);
			printf("\t\t\t   --------- �ܸ���:%2d -------------------------------- ҳ�� %2d/%2d --------\n\n",
				paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));//�ܸ��������㵱ǰҳ�������ܸ���
			printf("\t\t\t******************************************************************************\n");
			printf("\t\t\t             [P]��һҳ | [N]��һҳ                       [R]����");
			printf("\n\t\t\t==============================================================================\n");
			printf("\t\t\t\t��ѡ����:");
			choice = getche();
			switch (choice)
			{
			case 'p':
			case 'P':
				if (1 < Pageing_CurPage(paging)) {
					Paging_Locate_OffsetPage(head, paging, -1, studio_node_t);
				}
				break;
			case 'n':
			case 'N':
				if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
					Paging_Locate_OffsetPage(head, paging, 1, studio_node_t);
				}
				break;
			}
		} while (choice != 'r' && choice != 'R');
	}
	//�ͷ�����ռ�
	List_Destroy(head, studio_node_t);
}

int Studio_UI_Add(void) {
	studio_t rec;
	int newRecCount = 0;
	char choice;
	do {
		system("cls");
		kuangjia();
		goto_xy(30, 6);
		printf("              ---->>    �����µ��ݳ���    <<----\n");
		printf("\t\t\t\t    -------------------------------------------------------\n");
		printf("\n\t\t\t\t\t\t    ��������: ");
		fgets(rec.name, 30, stdin);
		int l = strlen(rec.name);
		rec.name[l - 1] = '\0';
		printf("\n\t\t\t\t\t\t    ����: ");
		scanf("\n\t\t\t%d", &rec.rowsCount);
		printf("\n\t\t\t\t\t\t    ����: ");
		scanf("%d", &rec.colsCount);
		getchar();
		rec.seatsCount = 0;
		printf("\t\t\t\t\t=============================================\n");

		//��ȡ����
		char type[] = "Studio";
		rec.id = EntKey_Srv_CompNewKey(type);  //Ϊ���ݷ�������

		if (Studio_Srv_Add(&rec)) {
			newRecCount += 1;
			printf("\t\t\t\t\t\t     ��ӳɹ�!\n");
		}
		else
			printf("\t\t\t\t\t���ʧ��\n");
		printf("\t\t\t\t    -------------------------------------------------------\n");
		printf("\t\t\t\t\t    [A]�ٴ����               [R]����:");
		choice = getche();
	} while ('a' == choice || 'A' == choice);
	return newRecCount;//����ֵ��ȷ���Ƿ���ӳɹ�
}

int Studio_UI_Modify(int id) {
	studio_t rec;
	int rtn = 0;
	int newrow, newcolumn;
	seat_list_t list;
	int seatcount;

	//�����ļ����Ƿ�������ID
	if (!Studio_Srv_FetchByID(id, &rec)) {
		printf("\t\t\t������ݳ���������!\n\t\t\t�� [Enter] ����\n");
		getchar();
		return 0;
	}

	system("cls");
	kuangjia();
	goto_xy(30, 6);
	printf("              ---->>    �޸�%d���ݳ�����Ϣ    <<----\n", id);
	printf("\t\t\t\t----------------------------------------------------------\n");
	printf("\n\t\t\t\t\t\t�ݳ��� ID:%d\n", rec.id);
	printf("\n\t\t\t\t\t\t�ݳ������� [%s]:", rec.name);
	getchar();
	fgets(rec.name, 30, stdin);
	int l = strlen(rec.name);
	rec.name[l - 1] = '\0';

	List_Init(list, seat_node_t);
	seatcount = Seat_Srv_FetchByRoomID(list, rec.id);
	if (seatcount) {
		do {			//�����λ�ļ���������λ��Ϣ������µ����б������ǰ�󣬷����������
			printf("\n\t\t\t\t\t\t��������Ӧ >= [%d]:", rec.rowsCount);
			scanf("\t\t\t%d", &(newrow));
			printf("\n\t\t\t\t\t\t���������Ӧ >= [%d]:", rec.colsCount);
			scanf("%d", &(newcolumn));
		} while (newrow<rec.rowsCount || newcolumn<rec.colsCount);
		getchar();
		rec.rowsCount = newrow;
		rec.colsCount = newcolumn;
		rec.seatsCount = seatcount;
	}
	else {
		printf("\n\t\t\t\t\t\t��������:");
		scanf("%d", &rec.rowsCount);
		printf("\n\t\t\t\t\t\t��������:");
		scanf("%d", &rec.colsCount);
		rec.seatsCount = 0;
	}

	printf("\n\t\t\t\t---------------------------------------------------------\n");

	if (Studio_Srv_Modify(&rec)) {
		rtn = 1;
		printf("\t\t\t\t\t�ݳ�����Ϣ�������!\t\t�� [Enter] ����\n\t\t\t");
	}
	else
		printf("\t\t\t\t\t�ݳ�����Ϣ����ʧ��!\t\t���Ժ�����!\n\t\t\t");
	getchar();
	getchar();
	return rtn;
}

int Studio_UI_Delete(int id) {

	int rtn = 0;

	if (Studio_Srv_DeleteByID(id)) {
		//��ɾ����ӳ��ʱ��ͬʱ���ݷ�ӳ��idɾ����λ�ļ��е���λ

		if (Seat_Srv_DeleteAllByRoomID(id))//ɾ���ݳ���id��������λ
			printf("\t\t\t\t\t\t�ݳ�����Ӧ����λ��Ϣɾ���ɹ�!\n");
		printf(
			"\t\t\t\t�ݳ�����Ϣɾ���ɹ�!!\t\t�� [Enter] ����\n");
		rtn = 1;
	}
	else {
		printf("\t\t\t\t������ݳ���������!\t\t�� [Enter] ����\n");
	}
	printf("\t\t\t");
	getchar();
	return rtn;//����ֵ��ʾ�Ƿ񷵻سɹ�
}
