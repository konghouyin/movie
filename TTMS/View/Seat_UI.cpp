#include "Seat_UI.h"

#include "../Service/Seat.h"
#include "../Service/Studio.h"
#include "../Service/EntityKey.h"
#include "../Common/list.h"
#include <stdio.h>
#include "conio.h"
#include "../Common/window.h"

//����״̬���ض�Ӧ��ʾ״̬����
char Seat_UI_Status2Char(seat_status_t status) {

	char statusChar;
	switch (status) {
	case SEAT_GOOD:		//����λ
		statusChar = '#';
		break;
	case SEAT_BROKEN:	//�𻵵���λ 
		statusChar = '*';
		break;
	case SEAT_NONE:
	default:
		statusChar = ' ';//û����λ
		break;
	}
	return statusChar;
}

//����״̬���ŷ�����λ״̬
seat_status_t Seat_UI_Char2Status(char statusChar) {
	seat_status_t status;
	switch (statusChar) {
	case '#':		//����λ
		status = SEAT_GOOD;
		break;
	case '*':	//�𻵵���λ
		status = SEAT_BROKEN;
		break;
	default:
		status = SEAT_NONE;
		break;
	}
	return status;
}

//��λ�������
void Seat_UI_MgtEntry(int roomID) {
	int i, j;
	char choice;
	int seatCount;
	int changedCount = 0;
	studio_t studioRec;//��������ݳ�������Ϣ�ṹ��

	if (!Studio_Srv_FetchByID(roomID, &studioRec)) {  //��ö�Ӧid��ӳ������Ϣ
		printf("\t\t\t���䲻����!\n\t\t\t�� [Enter] ������!\n\t\t\t");
		getchar();
		return;
	}
	seat_list_t list;
	seat_node_t *p;

	List_Init(list, seat_node_t);
	//����һ�������ݳ�����Ϣ��������λ����

	seatCount = Seat_Srv_FetchByRoomID(list, roomID);
	//��ѯ��Ӧ�ݳ���

	if (!seatCount) {		//����ӳ����û��������λ�����Զ�������λ
		seatCount = Seat_Srv_RoomInit(list, roomID, studioRec.rowsCount,
			studioRec.colsCount);
		//�޸��ݳ��������λ����
		studioRec.seatsCount = seatCount;
		Studio_Srv_Modify(&studioRec);//���ݳ�������λ��Ϣ���²������ļ�
	}
	do {
		system("cls");
		kuangjia();
		goto_xy(0, 5);
		printf("\n\t\t\t\t==================================================================\n");
		printf("\t\t\t\t**********************   %d �ݳ�����λ��  ************************\n", roomID);
		printf("\t\t\t\t%5c ", ' ');
		for (i = 1; i <= studioRec.colsCount; i++) {
			printf("%3d", i);
		}
		printf("\n\t\t\t\t------------------------------------------------------------------\n");
		//��ʾ����
		i = 1;
		j = 1;
		printf("\t\t\t\t%2d��: ", i);
		List_ForEach(list, p)
		{
			while (1)
			{
				if (p->data.row == i && p->data.column == j)
				{
					printf("%3c", Seat_UI_Status2Char(p->data.status));
					j++;
					break;
				}
				else if (p->data.row == i && p->data.column != j)
				{
					printf("   ");
					j++;
				}
				else if (p->data.row != i)
				{
					i++;
					printf("\n\t\t\t\t%2d��: ", i);
					j = 1;
				}
				else
				{
					i++;
					printf("\n\t\t\t\t%2d��: ", i);
					printf("%3c", Seat_UI_Status2Char(p->data.status));
					j = 1;
					break;
				}
			}
		}
		printf("\n\t\t\t\t------------------------------------------------------------------\n");
		printf("\n\t\t\t                [A]���  |  [D]ɾ��  |  [U]�޸�   |   [R]����   \n");
		while (_kbhit())
		{
			getch();
		}
		choice = getch();
		switch (choice) {
		case 'a':
		case 'A':
			changedCount = Seat_UI_Add(list, roomID, studioRec.rowsCount,
				studioRec.colsCount);
			if (changedCount > 0) {
				seatCount += changedCount;
				//�޸��ݳ��������λ����
				studioRec.seatsCount = seatCount;
				Studio_Srv_Modify(&studioRec);
			}
			break;
		case 'd':
		case 'D':
			changedCount = Seat_UI_Delete(list, studioRec.rowsCount,
				studioRec.colsCount);
			if (changedCount > 0) {
				seatCount -= changedCount;
				//�޸��ݳ��������λ����
				studioRec.seatsCount = seatCount;
				Studio_Srv_Modify(&studioRec);//��������ݳ�����λ��Ϣ
			}
			break;
		case 'u':
		case 'U':
			Seat_UI_Modify(list, studioRec.rowsCount, studioRec.colsCount);
			break;
		}
	} while (choice != 'r' && choice != 'R');
	//�ͷ�����ռ�
	List_Destroy(list, seat_node_t);
}

int Seat_UI_Add(seat_list_t list, int roomID, int row, int column) {  //����һ����λ
	seat_t rec;
	seat_node_t *p;
	int newRecCount = 0;
	char choice;
	do {
		do {
			goto_xy(0, 20);
			printf("\t\t\t                                                                                      ");
			printf("\n\t\t\t                                                                                      ");
			printf("\n\t\t\t                                                                                      ");
			printf("\n\t\t\t                                                                                      ");
			printf("\n\t\t\t                                                                                      ");
			printf("\n\t\t\t                                                                                      ");
			printf("\n\t\t\t                                                                                      ");
			printf("\n\t\t\t                                                                                      ");
			goto_xy(0, 20);
			printf("\n\t\t\t\t*********************     �����λ     *********************\n");
			printf("\t\t\t\t\t       ��������С�� %d ����С�� %d!\n", row, column);
			printf("\n\t\t\t\t\t���� :");
			scanf("%d", &(rec.row));
			goto_xy(70, 24);
			printf("���� :");
			scanf("%d", &(rec.column));
			getchar();
		} while (rec.row > row || rec.column > column || rec.row<0||rec.column<0);

		p = Seat_Srv_FindByRowCol(list, rec.row, rec.column);
		printf("\t\t\t\t============================================================\n");
		if (p != NULL) {						//����������к�����Ӧ����λ�Ѵ��ڣ����ܲ���
			printf("\t\t\t\t\t�������λ�Ѿ�����!");
		
			printf("\t\t[A]����   [R]����  ");
			while (_kbhit()){getch();}
			choice = getche();
			continue;
		}
		char type[] = "Seat";
		rec.id = EntKey_Srv_CompNewKey(type);		//������λid
		rec.roomID = roomID;
		rec.status = SEAT_GOOD;    //���������λ��״̬Ĭ��Ϊ����λ


		if (Seat_Srv_Add(&rec)) {
			newRecCount++;
			printf("\t\t\t\t\t����λ��ӳɹ�!");
			p = (seat_node_t*)malloc(sizeof(seat_node_t));
			p->data = rec;
			Seat_Srv_AddToSoftedList(list, p); //������������λ�������list
		}
		else
			printf("\t\t\t\t\t����λ���ʧ��!");
		printf("\t\t[A]��Ӹ���   [R]����   ");
		while (_kbhit()){getch();}
		choice = getche();
	} while ('a' == choice || 'A' == choice);
	//getchar();
	return newRecCount;
}

//�޸���λ��Ϣ
int Seat_UI_Modify(seat_list_t list, int row, int column) {
	int rtn = 0;
	int newrow, newcolumn;
	char choice;
	seat_node_t *p;

	
	do {
		do {	
			goto_xy(0, 20);
			printf("\t\t\t                                                                                      ");
			printf("\n\t\t\t                                                                                      ");
			printf("\n\t\t\t                                                                                      ");
			printf("\n\t\t\t                                                                                      ");
			printf("\n\t\t\t                                                                                      ");
			printf("\n\t\t\t                                                                                      ");
			printf("\n\t\t\t                                                                                      ");
			printf("\n\t\t\t                                                                                      ");
			goto_xy(0, 20);
			printf("\n\t\t\t\t*********************     �޸���λ     *********************\n");
			//���µ���λ������Ϣ���ܳ�����ӳ����������
			printf("\t\t\t\t\t       ��������С�� %d ����С�� %d!\n", row, column);
			printf("\n\t\t\t\t\t���� :");
			scanf("%d", &newrow);
			goto_xy(70, 24);
			printf("���� :");
			scanf("%d", &newcolumn);
			getchar();
		} while (newrow > row || newcolumn > column || newrow<0 || newcolumn<0);

		p = Seat_Srv_FindByRowCol(list, newrow, newcolumn);
		if (p) {
			printf("\t\t\t\t\t��ѡ������λ [%d,%d]: [%c]������λ--#  ��--*��:", newrow, newcolumn, Seat_UI_Status2Char(p->data.status));
			//while (_kbhit()){getch();}
			//getchar();
			p->data.status = Seat_UI_Char2Status(getchar());
			printf("\t\t\t\t-------------------------------------------------------------------\n");
			if (Seat_Srv_Modify(&(p->data))) //���޸ĵ���Ϣ���ļ��д洢
			{
				rtn = 1;
				printf("\t\t\t\t    ��λ��Ϣ�޸ĳɹ�!");
			}
			else
				printf("\t\t\t\t    ��λ��Ϣ�޸�ʧ��!");
		
		}
		else
		{
			printf("\t\t\t\t-------------------------------------------------------------------\n");
			printf("\t\t\t\t    �������λ������!");
		}
			
		printf("\t[U]�޸ĸ���     [R]����   ");
		choice = getche();
	} while ('u' == choice || 'U' == choice);
	return rtn;//���ر�ʾ�Ƿ�ɹ�
}

int Seat_UI_Delete(seat_list_t list, int row, int column) {
	//ɾ����Ϣ���ܳ����������������
	int delSeatCount = 0;
	int newrow, newcolumn;
	seat_node_t *p;
	char choice;

	do {
		do {
			goto_xy(0, 20);
			printf("\t\t\t                                                                                      ");
			printf("\n\t\t\t                                                                                      ");
			printf("\n\t\t\t                                                                                      ");
			printf("\n\t\t\t                                                                                      ");
			printf("\n\t\t\t                                                                                      ");
			printf("\n\t\t\t                                                                                      ");
			printf("\n\t\t\t                                                                                      ");
			printf("\n\t\t\t                                                                                      ");
			goto_xy(0, 20);
			printf("\n\t\t\t\t*********************     ɾ����λ     *********************\n");
			while (_kbhit()){getch();}
			printf("\t\t\t\t\t       ��������С�� %d ����С�� %d!\n", row, column);
			printf("\n\t\t\t\t\t���� :");
			scanf("%d", &(newrow));
			goto_xy(70, 24);
			printf("���� :");
			scanf("%d", &(newcolumn));
			getchar();
		} while (newrow > row || newcolumn > column || newrow<0 || newcolumn<0);

		p = Seat_Srv_FindByRowCol(list, newrow, newcolumn);//������Ҫɾ�����к��У����������ҵ���صĽڵ㣬������p
		printf("\t\t\t\t============================================================\n");
		if (p) {
			if (Seat_Srv_DeleteByID(p->data.id))//��ȡ��Ҫ�޸ĵĽڵ�p��id������ɾ�� 
			{
				printf("\t\t\t\t\t��λɾ���ɹ�!");

				delSeatCount++;
				List_FreeNode(p);	//�ͷŽ����λ���p
			}
		}
		else {
			printf("\t\t\t\t\t��ѡ��λ������!");
		}

		printf("\t\t[D]ɾ������    [R]����   ");
		choice = getche();
	} while ('d' == choice || 'D' == choice);
	return delSeatCount;//����ֵ��ʾ�Ƿ�ɾ���ɹ�
}

