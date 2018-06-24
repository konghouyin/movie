#include "Seat_UI.h"

#include "../Service/Seat.h"
#include "../Service/Studio.h"
#include "../Service/EntityKey.h"
#include "../Common/list.h"
#include <stdio.h>
#include "conio.h"
#include "../Common/window.h"

//根据状态返回对应表示状态符号
char Seat_UI_Status2Char(seat_status_t status) {

	char statusChar;
	switch (status) {
	case SEAT_GOOD:		//有座位
		statusChar = '#';
		break;
	case SEAT_BROKEN:	//损坏的座位 
		statusChar = '*';
		break;
	case SEAT_NONE:
	default:
		statusChar = ' ';//没有座位
		break;
	}
	return statusChar;
}

//根据状态符号返回桌位状态
seat_status_t Seat_UI_Char2Status(char statusChar) {
	seat_status_t status;
	switch (statusChar) {
	case '#':		//有座位
		status = SEAT_GOOD;
		break;
	case '*':	//损坏的座位
		status = SEAT_BROKEN;
		break;
	default:
		status = SEAT_NONE;
		break;
	}
	return status;
}

//座位管理界面
void Seat_UI_MgtEntry(int roomID) {
	int i, j;
	char choice;
	int seatCount;
	int changedCount = 0;
	studio_t studioRec;//建立存放演出厅的信息结构体

	if (!Studio_Srv_FetchByID(roomID, &studioRec)) {  //获得对应id放映厅的信息
		printf("\t\t\t房间不存在!\n\t\t\t按 [Enter] 键返回!\n\t\t\t");
		getchar();
		return;
	}
	seat_list_t list;
	seat_node_t *p;

	List_Init(list, seat_node_t);
	//创建一个根据演出厅信息，创建座位链表

	seatCount = Seat_Srv_FetchByRoomID(list, roomID);
	//查询对应演出厅

	if (!seatCount) {		//若放映厅还没有设置座位，则自动生成座位
		seatCount = Seat_Srv_RoomInit(list, roomID, studioRec.rowsCount,
			studioRec.colsCount);
		//修改演出厅里的座位数量
		studioRec.seatsCount = seatCount;
		Studio_Srv_Modify(&studioRec);//将演出厅的座位信息更新并存入文件
	}
	do {
		system("cls");
		kuangjia();
		goto_xy(0, 5);
		printf("\n\t\t\t\t==================================================================\n");
		printf("\t\t\t\t**********************   %d 演出厅座位表  ************************\n", roomID);
		printf("\t\t\t\t%5c ", ' ');
		for (i = 1; i <= studioRec.colsCount; i++) {
			printf("%3d", i);
		}
		printf("\n\t\t\t\t------------------------------------------------------------------\n");
		//显示数据
		i = 1;
		j = 1;
		printf("\t\t\t\t%2d行: ", i);
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
					printf("\n\t\t\t\t%2d行: ", i);
					j = 1;
				}
				else
				{
					i++;
					printf("\n\t\t\t\t%2d行: ", i);
					printf("%3c", Seat_UI_Status2Char(p->data.status));
					j = 1;
					break;
				}
			}
		}
		printf("\n\t\t\t\t------------------------------------------------------------------\n");
		printf("\n\t\t\t                [A]添加  |  [D]删除  |  [U]修改   |   [R]返回   \n");
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
				//修改演出厅里的座位数量
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
				//修改演出厅里的座位数量
				studioRec.seatsCount = seatCount;
				Studio_Srv_Modify(&studioRec);//更新相关演出厅座位信息
			}
			break;
		case 'u':
		case 'U':
			Seat_UI_Modify(list, studioRec.rowsCount, studioRec.colsCount);
			break;
		}
	} while (choice != 'r' && choice != 'R');
	//释放链表空间
	List_Destroy(list, seat_node_t);
}

int Seat_UI_Add(seat_list_t list, int roomID, int row, int column) {  //输入一个座位
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
			printf("\n\t\t\t\t*********************     添加座位     *********************\n");
			printf("\t\t\t\t\t       输入行数小于 %d 列数小于 %d!\n", row, column);
			printf("\n\t\t\t\t\t行数 :");
			scanf("%d", &(rec.row));
			goto_xy(70, 24);
			printf("列数 :");
			scanf("%d", &(rec.column));
			getchar();
		} while (rec.row > row || rec.column > column || rec.row<0||rec.column<0);

		p = Seat_Srv_FindByRowCol(list, rec.row, rec.column);
		printf("\t\t\t\t============================================================\n");
		if (p != NULL) {						//若输入的行列号所对应的座位已存在，则不能插入
			printf("\t\t\t\t\t输入的座位已经存在!");
		
			printf("\t\t[A]增加   [R]返回  ");
			while (_kbhit()){getch();}
			choice = getche();
			continue;
		}
		char type[] = "Seat";
		rec.id = EntKey_Srv_CompNewKey(type);		//设置座位id
		rec.roomID = roomID;
		rec.status = SEAT_GOOD;    //插入的新座位的状态默认为好座位


		if (Seat_Srv_Add(&rec)) {
			newRecCount++;
			printf("\t\t\t\t\t新座位添加成功!");
			p = (seat_node_t*)malloc(sizeof(seat_node_t));
			p->data = rec;
			Seat_Srv_AddToSoftedList(list, p); //若增加了新座位，需更新list
		}
		else
			printf("\t\t\t\t\t新座位添加失败!");
		printf("\t\t[A]添加更多   [R]返回   ");
		while (_kbhit()){getch();}
		choice = getche();
	} while ('a' == choice || 'A' == choice);
	//getchar();
	return newRecCount;
}

//修改座位信息
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
			printf("\n\t\t\t\t*********************     修改座位     *********************\n");
			//更新的座位行列信息不能超出放映厅的行列数
			printf("\t\t\t\t\t       输入行数小于 %d 列数小于 %d!\n", row, column);
			printf("\n\t\t\t\t\t行数 :");
			scanf("%d", &newrow);
			goto_xy(70, 24);
			printf("列数 :");
			scanf("%d", &newcolumn);
			getchar();
		} while (newrow > row || newcolumn > column || newrow<0 || newcolumn<0);

		p = Seat_Srv_FindByRowCol(list, newrow, newcolumn);
		if (p) {
			printf("\t\t\t\t\t所选定的座位 [%d,%d]: [%c]（有座位--#  损坏--*）:", newrow, newcolumn, Seat_UI_Status2Char(p->data.status));
			//while (_kbhit()){getch();}
			//getchar();
			p->data.status = Seat_UI_Char2Status(getchar());
			printf("\t\t\t\t-------------------------------------------------------------------\n");
			if (Seat_Srv_Modify(&(p->data))) //将修改的信息在文件中存储
			{
				rtn = 1;
				printf("\t\t\t\t    座位信息修改成功!");
			}
			else
				printf("\t\t\t\t    座位信息修改失败!");
		
		}
		else
		{
			printf("\t\t\t\t-------------------------------------------------------------------\n");
			printf("\t\t\t\t    输入的座位不存在!");
		}
			
		printf("\t[U]修改更多     [R]返回   ");
		choice = getche();
	} while ('u' == choice || 'U' == choice);
	return rtn;//返回表示是否成功
}

int Seat_UI_Delete(seat_list_t list, int row, int column) {
	//删除信息不能超过相关行数和列数
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
			printf("\n\t\t\t\t*********************     删除座位     *********************\n");
			while (_kbhit()){getch();}
			printf("\t\t\t\t\t       输入行数小于 %d 列数小于 %d!\n", row, column);
			printf("\n\t\t\t\t\t行数 :");
			scanf("%d", &(newrow));
			goto_xy(70, 24);
			printf("列数 :");
			scanf("%d", &(newcolumn));
			getchar();
		} while (newrow > row || newcolumn > column || newrow<0 || newcolumn<0);

		p = Seat_Srv_FindByRowCol(list, newrow, newcolumn);//输入需要删除的行和列，从链表中找到相关的节点，并返回p
		printf("\t\t\t\t============================================================\n");
		if (p) {
			if (Seat_Srv_DeleteByID(p->data.id))//获取需要修改的节点p的id，进行删除 
			{
				printf("\t\t\t\t\t座位删除成功!");

				delSeatCount++;
				List_FreeNode(p);	//释放结点座位结点p
			}
		}
		else {
			printf("\t\t\t\t\t所选座位不存在!");
		}

		printf("\t\t[D]删除更多    [R]返回   ");
		choice = getche();
	} while ('d' == choice || 'D' == choice);
	return delSeatCount;//返回值表示是否删除成功
}

