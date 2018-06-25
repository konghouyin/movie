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
* Description: 显示所有的演出计划信息,进行查询。
* Input:       无
* Output:      所有剧目的信息
* Return:      无
*/
void Schedule_UI_ListAll(void) {
	int i;
	schedule_list_t head;          //双向链表的定义  
	schedule_node_t *pos;          //双向链表的一个结点  
	char choice;
	Pagination_t paging;
	List_Init(head, schedule_node_t);        //链表
	paging.offset = 0;       //初始化  记录 
	paging.pageSize = SCHEDULE_PAGE_SIZE;
	//载入数据
	paging.totalRecords = Schedule_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);
	//显示数据
	
	printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n");
	printf("\t\t\t%8s %8s %10s %15s    %14s %12s\n", "计划ID号", "剧目ID号", "放映厅ID号", "演出日期", "演出时间", "座位数量");
	printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n");
	//显示数据
	for (i = 0, pos = (schedule_node_t *)(paging.curPos);
		pos != head && i < paging.pageSize; i++) {
		printf("\t\t\t%5d %8d %8d    %8d年%02d月%02d日   %8d时%02d分%02d秒  %3d\n\n", pos->data.id,
			pos->data.play_id, pos->data.studio_id, pos->data.date.year, pos->data.date.month, pos->data.date.day,
			pos->data.time.hour, pos->data.time.minute, pos->data.time.second, pos->data.seat_count);
		pos = pos->next;
	}
	goto_xy(0, 23);
	printf("\t\t\t      --------- 计划总数:%2d ---------------------------- 页数 %2d/%2d ------\n\n",
		paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));
	printf("\t\t\t*******************************************************************************\n");
	printf("\t\t\t[P]上一个  [N]下一个   |   [A]增加   [D]删除   [U]修改   [Q]查询   [R]返回");
	printf("\n\t\t\t================================================================================\n");
	printf("\t\t\t\t请选择:");
	
}
void Schedule_UI_ListAll1(void)
{
	int id;
	char choice;
	char ch;
	int i;
	schedule_list_t head;          //双向链表的定义  
	schedule_node_t *pos;          //双向链表的一个结点  
	Pagination_t paging;
	List_Init(head, schedule_node_t);        //链表
	paging.offset = 0;       //初始化  记录 
	paging.pageSize = SCHEDULE_PAGE_SIZE;
	//载入数据
	paging.totalRecords = Schedule_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);
	//显示数据
	do {
		system("cls");
		kuangjia();
		goto_xy(0, 7);
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n");
		printf("\t\t\t%8s %8s %10s %15s    %14s %12s\n", "计划ID号", "剧目ID号", "放映厅ID号", "演出日期", "演出时间", "座位数量");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n");
		//显示数据
		for (i = 0, pos = (schedule_node_t *)(paging.curPos);
			pos != head && i < paging.pageSize; i++) {
			printf("\t\t\t%5d %8d %8d    %8d年%02d月%02d日   %8d时%02d分%02d秒  %3d\n\n", pos->data.id,
				pos->data.play_id, pos->data.studio_id, pos->data.date.year, pos->data.date.month, pos->data.date.day,
				pos->data.time.hour, pos->data.time.minute, pos->data.time.second, pos->data.seat_count);
			pos = pos->next;
		}
		goto_xy(0, 23);
		printf("\t\t\t      --------- 计划总数:%2d ---------------------------- 页数 %2d/%2d ------\n\n",
			paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));
		printf("\t\t\t*******************************************************************************\n");
		printf("\t\t\t       [P]上一个  [N]下一个                      [Q]查询   [R]返回");
		printf("\n\t\t\t================================================================================\n");
		printf("\t\t\t\t请选择:");
		while (_kbhit()) { getch(); }
		choice = getche();
		while (_kbhit()) { getch(); }
		switch (choice)
		{
		case 'q':
		case 'Q':
			printf("\t\t\t输入要查找的ID:");
			while (scanf("%d", &id) != 1)
			{
				printf("\t\t\t您输入的不是数字");
				printf("\t\t\t请重新输入：");
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
* Description: 添加一条演出计划信息
* Input:       相关剧目的ID号
* Output:      输入信息时的各种提示
* Return:      添加的记录数
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
		printf("              ---->>    增加演出计划    <<----\n");
		goto_xy(30, 8);
		printf("\t       ==============================================\n");

		while (_kbhit()){getch();}
		printf("\n\t\t\t\t\t\t剧目 ID: ");
		scanf("%d", &rec.play_id);
		printf("\n\t\t\t\t\t\t演出厅 ID: ");
		scanf("%d", &rec.studio_id);
		printf("\n\t\t\t\t\t\t播放日期: ");
		scanf("%d%d%d", &rec.date.year, &rec.date.month, &rec.date.day);
		printf("\n\t\t\t\t\t\t播放时间: ");
		scanf("%d%d%d", &rec.time.hour, &rec.time.minute, &rec.time.second);
		getchar();

		printf("\n\t\t\t\t        ==========================================\n");

		//获取主键
		char type[] = "Schedule";
		rec.id = EntKey_Srv_CompNewKey(type);
		rec.seat_count = Seat_Srv_FetchValidByRoomID(list, rec.studio_id);

		if (Schedule_Srv_Add(&rec) && Ticket_Srv_AddBatch(rec.id, rec.studio_id)) {
			newRecCount += 1;
			printf("\t\t\t\t\t\t新演出计划添加成功!\n");
		}
		else {
			printf("\t\t\t\t\t演出计划添加失败!\n");
			Schedule_Srv_DeleteByID(rec.id);
		}
		printf("\t\t\t\t-------------------------------------------------------\n");
		printf("\t\t\t\t\t     [A]继续添加            [R]返回:");
		while (_kbhit()){getch();}
		choice = getche();
	} while ('a' == choice || 'A' == choice);
	return newRecCount;
}

/*
* Function:    Schedule_UI_Modify
* Function ID:	TTMS_SCU_Schedule_UI_Mod
* Description: 按照ID号更新演出计划信息
* Input:       待更新的剧目ID号
* Output:      输入信息时的各种提示
* Return:      更新的剧目信息数，0表示未找到，1表示找到并更新
*/
int Schedule_UI_Modify(int id) {

	schedule_t rec;
	int rtn = 0;

	/*Load record*/
	if (!Schedule_Srv_FetchByID(id, &rec)) {
		printf("\t\t\t\t剧目ID不存在!\t\t\t按 [Enter] 返回\n\t\t\t");
		getchar();
		getchar();
		return 0;
	}

	//界面	
	system("cls");
	kuangjia();
	goto_xy(30, 7);
	printf("              ---->>    修改演出计划    <<----\n");
	goto_xy(30, 8);
	printf("\t       ==============================================\n");

	while (_kbhit()){getch();}
	printf("\t\t\t\t\t\t剧目 ID:");
	scanf("%d", &rec.play_id);
	printf("\t\t\t\t\t\t演出厅 ID:");
	scanf("%d", &rec.studio_id);
	printf("\t\t\t\t\t\t播放日期:");
	scanf("%d%d%d", &rec.date.year, &rec.date.month, &rec.date.day);
	printf("\t\t\t\t\t\t播放时间:");
	scanf("%d%d%d", &rec.time.hour, &rec.time.minute, &rec.time.second);
	getchar();

	printf("\n\t\t\t\t        ==========================================\n");

	rec.seat_count = Ticket_Srv_AddBatch(rec.id, rec.studio_id);
	if (Schedule_Srv_Modify(&rec)) {
		rtn = 1;
		printf(
			"\t\t\t\t\t演出计划修改成功!\t\t按 [Enter] 返回\n\t\t\t");
	}
	else
		printf("\t\t\t\t\t演出计划修改失败!\t\t\t按 [Enter] 返回\n\t\t\t");
	getchar();
	getchar();
	return rtn;
}


/*
* Function:    Schedule_UI_Delete
* Function ID:	TTMS_SCU_Schedule_UI_Del
* Description: 按照ID号删除演出计划信息
* Input:       待删除的剧目ID号
* Output:      提示删除是否成功
* Return:      0表示删除失败，1表示删除成功
*/
int Schedule_UI_Delete(int id) {
	int rtn = 0;
	schedule_t rec;

	if (!Schedule_Srv_FetchByID(id, &rec)) {
		printf("\t\t\t\t剧目ID不存在!\t\t\t按 [Enter] 返回\n\t\t\t");
		getchar();
		getchar();
		return 0;
	}

	goto_xy(0, 28);
	printf("\t\t\t                                                                                            \n");
	printf("\t\t\t                                                                                            \n");
	printf("\t\t\t                                                                                            \n");
	goto_xy(0, 28);
	printf("\t\t\t\t是否确认删除 ID ： %d 的计划( Y / N )", id);
	char ch = getche();
	if (ch != 'Y'&&ch != 'y')
		return 0;

	/*if ( Ticket_Srv_DeleteBatch(rec.studio_id) && Schedule_Srv_DeleteByID(id))*/ 
	if (Schedule_Srv_DeleteByID(id)) 
	{
		printf("\t\t\t演出计划删除成功!\n\t\t\t");
		rtn = 1;
	}
	else {
		printf("\t\t\t演出计划删除失败!\n\t\t\t按 [Enter] 返回\n\t\t\t");
	}
	getchar();
	getchar();
	return rtn;
}

/*
* Function:    Schedule_UI_Query
* Function ID:	TTMS_SCU_Schedule_UI_Qry
* Description: 按照ID号查询演出计划信息
* Input:       待查找的剧目ID号
* Output:      查找到的剧目信息
* Return:      0表示未找到，1表示找到了
*/
int Schedule_UI_Query(int id) {
	int rtn = 1;
	schedule_t  buf;
	schedule_t rec;

	if (!Schedule_Srv_FetchByID(id, &rec)) {
		printf("\t\t\t\t剧目ID不存在!\t\t\t按 [Enter] 返回\n\t\t\t");
		getchar();
		getchar();
		return 0;
	}


	if (Schedule_Srv_FetchByID(id, &buf)) {
		system("cls");
		kuangjia();
		goto_xy(30, 7);
		printf("              ---->>    ID为 %2d 的演出计划    <<----\n",buf.id);
		goto_xy(30, 8);
		printf("\t       ==============================================\n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n");
		printf("\t\t\t%8s %8s %10s %15s    %14s %12s\n", "计划ID号", "剧目ID号", "放映厅ID号", "演出日期", "演出时间", "座位数量");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n");
		//显示数据

		printf("\t\t\t%5d %8d %8d    %8d年%02d月%02d日   %8d时%02d分%02d秒  %3d\n\n", buf.id,
			buf.play_id, buf.studio_id, buf.date.year, buf.date.month, buf.date.day,
			buf.time.hour, buf.time.minute, buf.time.second, buf.seat_count);
				
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n");
		printf("\t\t\t\t\t\t输入 [Enter] 结束");
		while (getchar() != '\n');
	}
	else
	{
		printf("\t\t\t查找不到该演出计划！");
	}
	getchar();
	return rtn;
}

/*
* Function:    Schedule_UI_ListByPlay
* Function ID:	TTMS_SCU_Schedule_UI_ListByPlay
* Description: 以列表模式显示给定剧目的演出计划信息
* Input:       list为查找到的演出计划信息链表的头指针，play为剧目信息，paging为显示分页设置参数
* Output:      无
* Return:      返回查找到的记录数目
*/
void Schedule_UI_ListByPlay(const play_t *play, schedule_list_t list, Pagination_t paging) {


}

/*
* Function:    Schedule_UI_MgtEntry
* Function ID:	TTMS_SCU_Schedule_UI_MgtEnt
* Description: 演出计划管理界面，演出计划按照剧目进行管理，以剧目ID号为输入
* Input:       相关剧目ID号
* Output:      演出计划信息
* Return:      无
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
	//载入数据
	paging.totalRecords = Schedule_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);
	do {
		system("cls");
		kuangjia();
		goto_xy(30, 5);
		printf("              ---->>      上映剧目列表    <<----\n");

		printf("\t\t\t==============================================================================\n\n");
		Schedule_UI_ListAll();

		while (_kbhit()){getch();}
		choice = getche();
		while (_kbhit()){getch();}
		switch (choice)
		{
		case 'a':
		case 'A':
			//添加演出计划
			if (Schedule_UI_Add())     //新添加成功，跳到最后一页显示
			{
				paging.totalRecords = Schedule_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, schedule_node_t);
			}
			break;
		case 'u':
		case 'U':
			//修改演出计划
			printf("\t\t\t输入 ID:");
			while (scanf("%d", &id) != 1)
			{
				printf("\t\t\t您输入的不是数字\n");
				printf("\t\t\t请重新输入：");
				while ((ch = getchar()) != '\n')
					continue;
			}
			while (_kbhit()){getch();}
			if (Schedule_UI_Modify(id)) {	//从新载入数据
				paging.totalRecords = Schedule_Srv_FetchAll(head);
				List_Paging(head, paging, schedule_node_t);
			}
			break;
		case 'd':
		case 'D':
			//删除演出计划
			printf("\t\t\t输入 ID:");
			scanf("%d", &id);
			while (_kbhit()){getch();}
			if (Schedule_UI_Delete(id)) {	//从新载入数据
				paging.totalRecords = Schedule_Srv_FetchAll(head);
				List_Paging(head, paging, schedule_node_t);
			}
			break;
		case 'q':
		case 'Q':
			printf("\t\t\t输入要查找的ID:");
			while (scanf("%d", &id) != 1)
			{
				printf("\t\t\t您输入的不是数字\n");
				printf("\t\t\t请重新输入：");
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
	//释放链表空间
	List_Destroy(head, schedule_node_t);
}
