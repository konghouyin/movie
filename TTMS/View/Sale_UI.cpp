#include "Play_UI.h"
#include "Schedule_UI.h"
#include "Sale_UI.h"
#include "../Common/list.h"
#include "../Service/Ticket.h"
#include "../Service/Seat.h"
#include "../Service/Studio.h"
#include "../Service/EntityKey.h"
#include "../Service/Sale.h"
#include "../Service/Schedule.h"
#include "../Persistence/Sale_Persist.h"
#include "../Common/window.h"
#include "Ticket_UI.h"

#define PAGESIZE 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conio.h"

//���õ�½�û���ȫ�����ݽṹ
extern account_t gl_CurUser;

//���ݼƻ�ID����ʾ�ݳ�Ʊ
void Sale_UI_ShowTicket(int schID)
{
	int /*pageSize = 10,*/ i;
	int listSize;
	int ticket_id;
	char choice;
	seat_list_t seat_list;
	seat_node_t *buf;
	Pagination_t paging;
	List_Init(seat_list, seat_node_t);


	int value = 0;
	schedule_list_t list;
	schedule_t sche;
	List_Init(list, schedule_node_t);//�����ݳ��ƻ�����

	Schedule_Srv_FetchByID(schID, &sche);//ͨ���ݳ��ƻ�id�����������ҵ���Ӧ�ݳ��ƻ�
	Seat_Srv_FetchByRoomID(seat_list, sche.studio_id);//�ҵ��ݳ���ID��������λ����
	

	ticket_list_t ticket_list, s;
	List_Init(ticket_list, ticket_node_t);
	Ticket_Srv_FetchBySchID(ticket_list, schID);//����Ʊ����

	do
	{
		int rowmax=0, colmax=0;
		system("cls");
		kuangjia();
		goto_xy(0, 5);
		printf("\n\t\t\t\t========================== ��λ�� ================================\n");
		
		Ticket_UI_show(schID);
		printf("\t\t\t\t        ps:  ��---��ѡ��     ��---������    ��---����ѡ\n");
		printf("\t\t\t\t==================================================================\n");
		printf("\t\t\t          **      [T] ��Ʊ����  �� [B]��Ʊ        [R]������һ��     **\n");
		printf("\t\t\t\t==================================================================\n");
		printf("\t\t\t      ���ѡ��: ");
		choice = getche();
		int row, col;
		switch (choice)
		{
		case 'B':
		case 'b':
			printf("\t\t��������Ҫ������Ʊ�����������ո��������");
			scanf("%d %d", &row,&col);
			getchar();
			buf = Seat_Srv_FindByRowCol(seat_list, row, col);//�����ж�Ӧ����λid
			int flag;
			List_ForEach(ticket_list, s)
			{
				if (s->data.seat_id == buf->data.id)
				{
					flag = 1;
					if (!Sale_UI_SellTicket(s->data.id))
					{
						printf("��Ʊʧ�ܣ�");
					}
				}
			}		
			if (flag == 0)
			{
				printf("��Ʊʧ�ܣ�");
			}
			break;
		case 'r':
		case 'R':
			break;
		case 't':
		case 'T':
			printf("\t\t��������Ҫ�˵�Ʊ��id��");
			scanf("%d", &ticket_id);
			getchar();
			Sale_UI_ReturnTicket(ticket_id);
			break;
	
		}
	} while (choice != 'r' && choice != 'R');
}


void Sale_UI_ReturnTicket(int ticket_id)
{
	ticket_t buf, data;
	sale_t a;
	if (Ticket_Srv_FetchByID(ticket_id, &buf))
	{
		if (buf.status == 0)
		{
			printf("\t\t\t\t\t��Ʊδ�۳����س�����");
			getchar();
		}
		else
		{
			//����Ʊ��id���Ʊ��Ʊ�Ļ�����Ϣ
			Select_Price_By_Playid(buf.id, &a);

			data.id = buf.id;
			data.schedule_id = buf.schedule_id;
			data.seat_id = buf.seat_id;
			data.price = buf.price;
			data.status = (ticket_status_t)0;

			if (Ticket_Srv_Modify(&data) && Sale_Srv_DeleteByID(a.id))
			{
				printf("\t\t\t\t\t�˶��ɹ����س�����");
				getchar();
			}
			else
			{
				printf("\t\t\t\t\t�˶�ʧ�ܣ��س�����");
				getchar();
			}
		}
	}
	else
	{
		printf("\t\t\t\t\t�Ҳ�����Ʊ���س�����");
		getchar();
	}
}

int Sale_UI_SellTicket(int ticket_id)
{
	ticket_t buf, data;
	sale_t sale;

	if (Ticket_Srv_FetchByID(ticket_id, &buf))
	{
		if (buf.status == 1)
		{
			printf("\t\t\t��Ʊ���۳����س�����");
			getchar();
		}
		else
		{
			char type[] = "Sale";
			sale.id = EntKey_Srv_CompNewKey(type);
			sale.user_id = gl_CurUser.id;
			sale.date = DateNow();
			sale.time = TimeNow();
			sale.ticket_id = buf.id;
			data.id = buf.id;
			data.schedule_id = buf.schedule_id;
			data.seat_id = buf.seat_id;
			sale.value = data.price = buf.price;
			data.status = (ticket_status_t)1;
			if (Ticket_Srv_Modify(&data) && Sale_Srv_Add(&sale))
			{
				system("cls");
				kuangjia();
				goto_xy(0, 5);
				Ticket_Info(&data,ticket_id);
				printf("\n");
				printf("\t\t\t\t��������ʱ��:%d��-%02d��-%02d��   %dʱ-%02d��-%02d��\n", sale.date.year, sale.date.month, sale.date.day, sale.time.hour, sale.time.minute, sale.time.second);
				printf("\t\t\t\t��ƱԱID: %d\n", sale.user_id);
				
				printf("\n\t\t\t\t\t\t�����ɹ����س�����");
				getchar();
			}
			else
			{
				printf("\t\t\t\t\t\t����ʧ�ܣ��س�����");
				getchar();
			}
		}
	}
	else
	{
		printf("\t\t\t�Ҳ�����Ʊ���س�����");
		getchar();
	}
	return 0;
}

void Ticket_Info(ticket_t *data,int id)
{
	schedule_t p;
	play_t buf;
	seat_t s;
	studio_t studio;

	Seat_Srv_FetchByID(data->seat_id, &s);
	Schedule_Srv_FetchByID(data->schedule_id, &p);
	if (Play_Srv_FetchByID(p.play_id, &buf))
	{
		Studio_Srv_FetchByID(p.studio_id, &studio);
		printf("\n\t\t\t\t=================ӰƱ��Ϣ:ID:%3d===================\n",id);
		printf("\t\t\t\t\t��Ŀ����: %s\n", buf.name);
		printf("\t\t\t\t\t���ͣ�%s\n", type(buf.type));
		printf("\t\t\t\t\t��Ʒ������%s\n", buf.area);
		printf("\t\t\t\t\t��Ŀ�ȼ���%s\n", rating(buf.rating));
		printf("\t\t\t\t\tʱ��: %d ����\n", buf.duration);
		printf("\t\t\t\t\t��ӳʱ��: %4d��%02d��%02d��\n", p.date.year, p.date.month, p.date.day);
		printf("\t\t\t\t\t��ӳʱ��: %2dʱ%02d��%02d��\n", p.time.hour, p.time.minute, p.time.second);
		printf("\t\t\t\t\tƱ�ۣ�%d Ԫ\n", buf.price);
		printf("\t\t\t\t\t�ݳ���:%s\n", studio.name);
		printf("\t\t\t\t\tλ��: %d��%d��\n", s.row , s.column );
		printf("\t\t\t\t==================================================\n");

		getchar();
	}
}
//���ݾ�ĿID��ʾ�ݳ��ƻ�
void Sale_UI_ShowScheduler(int playID)
{
	play_t buf;
	if (Play_Srv_FetchByID(playID, &buf))
	{
		int listSize, sal_id, i;
		char choice;
		Pagination_t paging;
		schedule_list_t list, pos, p;
		schedule_t buf;
		List_Init(list, schedule_node_t);
		listSize = Schedule_Srv_FetchByPlay(list, playID);
		paging.pageSize = PAGESIZE;
		paging.totalRecords = listSize;
		Paging_Locate_FirstPage(list, paging);
		do {
			system("cls");
			kuangjia();
			goto_xy(0, 5);
			printf("\n\t\t\t\t    ========================= �ƻ��� ==========================\n");
			printf("\t\t\t\t    -----------------------------------------------------------\n");
			printf("\t\t\t\t      %-3s  %-6s    %8s%12s  %8s   %6s\n", "ID", "��ĿID", "�ݳ���ID", "��ӳ����", "��ӳʱ��", "��λ��");
			printf("\t\t\t\t    -----------------------------------------------------------\n");
			//Paging_ViewPage_ForEach(list, paging, schedule_node_t, pos, i)
			for (i = 0, pos = (schedule_node_t *)(paging.curPos); pos != list && i < paging.pageSize; i++, pos = pos->next)
			{
				printf("\t\t\t\t      %-3d     %-3d   %4d     %6d-%2d-%2d  %2d:%02d:%02d  %6d\n", pos->data.id, pos->data.play_id, pos->data.studio_id, pos->data.date.year, pos->data.date.month, pos->data.date.day, pos->data.time.hour, pos->data.time.minute, pos->data.time.second, pos->data.seat_count);
			}
			goto_xy(0, 21);
			printf("\t\t\t\t       ----�ܼ�¼��:%2d ------------------- ҳ���� %2d/%2d ---- \n", paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));
			printf("\t\t\t\t    ===========================================================\n");
			printf("\t\t\t\t         ** [P]��һҳ [N]��һҳ [R]���� [S]��Ʊϵͳ  **\n");
			printf("\t\t\t\t    ===========================================================\n");
			printf("\t\t\t\t\t��ѡ��");
			while (_kbhit()){getch();}
			choice = getche();
			switch (choice)
			{
			case 'S':;
			case 's':
				printf("\t\t�������ݳ��ƻ�id��");
				scanf("%d", &sal_id);
				getchar();
				if (!Schedule_Srv_FetchByID(sal_id, &buf))
				{
					printf("\t\t��������ݳ��ƻ������ڣ��س�����");
					getchar();
				}
				else
				{
					Sale_UI_ShowTicket(sal_id);
				}
				paging.totalRecords = Schedule_Srv_FetchByPlay(list, playID);
				List_Paging(list, paging, schedule_node_t);
				break;
			case 'r':
			case 'R':
				break;
			case 'p':
			case 'P':
				if (1 < Pageing_CurPage(paging))
				{
					Paging_Locate_OffsetPage(list, paging, -1, schedule_node_t);
				}
				choice = 'r';
				break;
			case 'n':
			case 'N':
				if (Pageing_TotalPages(paging) > Pageing_CurPage(paging))
				{
					Paging_Locate_OffsetPage(list, paging, 1, schedule_node_t);
				}
				choice = 'r';
				break;
			}
		} while (choice != 'r' && choice != 'R');
	}
	else
	{
		printf("Not Found !");
		getchar();
	}
}

void Sale_UI_MgtEntry()
{

	int listSize, i, id;
	char choice;
	char name[31];
	Pagination_t paging;
	play_list_t list, p, data, pos;
	List_Init(data, play_node_t);
	List_Init(list, play_node_t);
	listSize = Play_Srv_FetchAll(list);
	paging.pageSize = PAGESIZE;
	paging.totalRecords = listSize;
	Paging_Locate_FirstPage(list, paging);
	do {
		system("cls");
		kuangjia();
		goto_xy(0, 5);
		printf("\n\t\t========================================== ��Ŀ�б� ========================================\n");
		printf("\t\t    ------------------------------------------------------------------------------------    \n");
		printf("\t\t        %-5s  %-12s  %-4s    %8s    %8s       %8s     %5s\n",
			"ID", "  Ƭ��  ", "����", "����", "�ȼ�", "����ʱ��", "�۸�");
		printf("\t\t    ------------------------------------------------------------------------------------    \n");
		for (i = 0, p = (play_node_t *)(paging.curPos); p != list && i < paging.pageSize; i++, p = p->next)
		{
			printf("\t\t        %-5d  %-12s  %-4s    %8s    %8s      %5d           %-5d\n\n", p->data.id, p->data.name, type(p->data.type),
				p->data.area, rating(p->data.rating), p->data.duration,p->data.price);
		}
		goto_xy(0, 21);
		printf("\t\t    --------- ӰƬ���� :%2d ---------------------------------------- ҳ�룺 %2d/%2d -------    \n", paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));
		printf("\t\t============================================================================================\n");
		printf("\t\t           ***               [P]��һҳ               [N]��һҳ                 ***\n");
		printf("\t\t           ***      [S]��ѯ��Ŀ         [C]Ʊ��ϵͳ	          [R]����      ***\n");
		printf("\t\t============================================================================================\n");
		printf("\t\t\t\t��ѡ��");
		while (_kbhit()){getch();}
		choice = getche();
		switch (choice)
		{
		case 'C':;
		case 'c':
			printf("\t\t\t�������빺��ľ�Ŀid:");
			scanf("%d", &id);
			getchar();
			Sale_UI_ShowScheduler(id);
			paging.totalRecords = Play_Srv_FetchAll(list);
			List_Paging(list, paging, play_node_t);
			break;
		case 'S':
		case 's':
			printf("\t\t\t��������Ҫ��ѯ�ľ�Ŀ����:");
			scanf("%s", name);
			getchar();
			if (Play_UI_Query_Name(name))
			{
				paging.totalRecords = Play_Srv_FetchAll(list);
				List_Paging(list, paging, play_node_t);
			}
			break;
		case 'r':
		case 'R':
			break;
		case 'p':
		case 'P':
			if (1 < Pageing_CurPage(paging))
			{
				Paging_Locate_OffsetPage(list, paging, -1, play_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (Pageing_TotalPages(paging) > Pageing_CurPage(paging))
			{
				Paging_Locate_OffsetPage(list, paging, 1, play_node_t);
			}
			break;
		}
	} while (choice != 'r'&&choice != 'R');
	List_Destroy(list, play_node_t);
}

void Print_Play(play_list_t list)
{
	play_list_t p;
	p = list->next;
	do
	{
		printf("\n\t\t\t=================��Ŀ��Ϣ============================\n");
		printf("\t\t\t��Ŀid: %d\n", p->data.id);
		printf("\t\t\t��Ŀ����: %s\n", p->data.name);
		printf("\t\t\t���ͣ�%s\n", type(p->data.type));
		printf("\t\t\t��Ʒ������%s\n", p->data.area);
		printf("\t\t\t��Ŀ�ȼ���%s\n", rating(p->data.rating));
		printf("\t\t\tʱ��: %d ����\n", p->data.duration);
		printf("\t\t\t��ӳʱ��: %d��%d�� %d��\n", p->data.start_date.year, p->data.start_date.month, p->data.start_date.day);
		printf("\t\t\t������ӳʱ�䣺%d��%d��%d��\n", p->data.end_date.year, p->data.end_date.month, p->data.end_date.day);
		printf("\t\t\tƱ�ۣ�%d Ԫ\n", p->data.price);
		printf("\t\t\t======================================================\n");
		p = p->next;
	} while (p != list);
	printf("\t\t\tPress Any Key To Continue......");
	getchar();
}


char * Status(int i)
{
	static char back[5];
	if (i == 1)
	{
		strcpy(back, "��");
		return back;
	}
	else if (i == 0)
	{
		strcpy(back, "��");
		return back;
	}
	else if (i == -1)
	{
		strcpy(back, "��");
		return back;
	}
	else
	{
		strcpy(back, "��");
		return back;
	}
}
