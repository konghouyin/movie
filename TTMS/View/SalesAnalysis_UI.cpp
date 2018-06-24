/*
* SalesAnalysis_UI.c
*
*  Created on: 2015年5月8日
*      Author: Administrator
*/
#include "SalesAnalysis_UI.h"
#include "../Common/list.h"
#include "../Common/common.h"
#include "../Common/window.h"
#include "../Service/SalesAnalysis.h"
#include "conio.h"
#include <stdio.h>
#include <io.h>
#include <process.h>
#include <assert.h>
#include <string.h>

//外部变量gl_CurUser 用于存储登录用户信息
extern account_t gl_CurUser;

//定义分页机制中页面大小为5
static const int SALESANALYSIS_PAGE_SIZE = 5;

//剧院销售排行榜函数,降序显示截止目前剧院电影票房排行榜
void SalesAnalysis_UI_BoxOffice() {
	salesanalysis_list_t  head;
	salesanalysis_node_t  *pos;
	int i;
	char choice;
	//载入数据
	//paging.totalRecords = Studio_Srv_FetchAll(head);

	Pagination_t paging;
	paging.offset = 0;

	List_Init(head, salesanalysis_node_t);

	Paging_Locate_FirstPage(head, paging);
	//设置分页大小
	paging.totalRecords = Salesanalysis_Srv_StaticSale(head);
	//printf("%d\n",paging.totalRecords);
	SalesAnalysis_Srv_SortBySale(head);
	/*设置分页显示页面大小*/
	paging.pageSize = SALESANALYSIS_PAGE_SIZE;
	do {
		goto_xy(0, 10);
		printf("\t\t                                                                                                \n\n");
		printf("\n\t\t\t==================================================================\n");
		printf("\t\t\t***************************  总票房排名  *************************\n");
		printf("\t\t\t%10s  %12s  %10s   %s %s\n", "排名", "剧目名称", "售价","数量","票房");
		printf("\t\t\t------------------------------------------------------------------\n");
		//显示数据
		int icount = 1;
		for (i = 0, pos = head->next;
			pos != head && i < paging.pageSize; i++)
		{
			printf("\t\t\t%8d  %12s          %d     %d  %8ld\n", icount, pos->data.name,pos->data.price,pos->data.totaltickets, pos->data.sales);
			pos = pos->next;
			icount++;
		}
		printf("\t\t    --------- 剧目总数 :%2d ---------------------------------------- 页码： %2d/%2d -------    \n", paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t[P] 上一页      [N] 下一页      [R] 返回 \n");
		printf("\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t请输入您的选择：");
		while (_kbhit()){getch();}
		choice = getche();
		switch (choice)
		{
		case 'p':
		case 'P':
			if (1 < Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, salesanalysis_node_t);
			}
			break;
		case 'n':
		case 'N':
			if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, salesanalysis_node_t);
			}
			break;
		}
	} while (choice != 'r' && choice != 'R');
}

//显示售票员在给定日期区间的售票情况
void SalesAnalysis_UI_StatSale(int usrID, user_date_t stDate, user_date_t endDate) {
	int rtn;
	account_t buf;
	Account_Srv_FetchByID(usrID, &buf);
	rtn = Salesanalysis_Srv_CompSaleVal(usrID, stDate, endDate);
	printf("\n\t\t\t===========================================================\n");
	printf("\t\t\t******************  cherk information  ********************\n");
	printf("\t\t\t===========================================================\n");
	printf("\t\t\t%-10s %-20s %-15s\n", "usr id", "usr name", "sale count");
	printf("\t\t\t%-10d %-20s %-15d\n", buf.id, buf.username, rtn);
	return;
}

//销售分析入口函数，显示菜单，菜单包含"降序显示截止目前剧院电影票房排行榜"，“显示或查询当日售票员售票情况”，
//“查询给定日期区间某售票员售票情况”
void SalesAanalysis_UI_MgtEntry() {
	char choice;
	int id;
	user_date_t stDate;
	user_date_t endDate;
	if (gl_CurUser.type == 2) {
		do
		{
			system("cls");
			kuangjia();
			goto_xy(0, 5);
			printf("\t\t\t            -------->       销售数据管理        <-------\n");
			printf("\t\t\t------------------------------------------------------------------\n");
			printf("\t\t\t            [T]票房排名 | [U]售票员销售统计 | [R]返回");
			printf("\n\t\t\t==================================================================\n");
			printf("\t\t\t请选择: ");
			choice = getche();
			switch (choice)
			{
			case 't':
			case 'T':
				printf("\n");
				SalesAnalysis_UI_BoxOffice();
				break;
			case 'u':
			case 'U':
				printf("\n\t\t\t请输入cherk的id:");
				scanf("%d", &id);
				printf("\t\t\t请输入开始查询日期:");
				scanf("%d%d%d", &stDate.year, &stDate.month, &stDate.day);
				printf("\t\t\t请输入结束查询日期:");
				scanf("%d%d%d", &endDate.year, &endDate.month, &endDate.day);
				getchar();
				SalesAnalysis_UI_StatSale(id, stDate, endDate);
				break;
			case 's':
			case 'S':
				printf("\n\t\t\t请输入cherk的id:");
				scanf("%d", &id);
				getchar();
				stDate = DateNow();
				endDate = DateNow();
				SalesAnalysis_UI_StatSale(id, stDate, endDate);
				break;
			}
		} while (choice != 'r' && choice != 'R');
	}
	else {
		do
		{
			system("cls");
			kuangjia();
			goto_xy(0, 5);
			printf("\t\t\t            -------->       销售数据管理        <-------\n");
			printf("\t\t\t------------------------------------------------------------------\n");
			printf("\t\t\t     [T]票房排名    |    [U]个人销售统计    |    [R]返回");
			printf("\n\t\t\t==================================================================\n");
			printf("\t\t\t请选择: ");
			while (_kbhit())
			{
				getch();
			}
			choice = getche();
			switch (choice)
			{
			case 't':
			case 'T':
				printf("\n");
				SalesAnalysis_UI_BoxOffice();
				break;
			case 'o':
			case 'O':
				id = gl_CurUser.id;
				stDate = DateNow();
				endDate = DateNow();
				//printf("%d-%d-%d\n",stDate.year,stDate.month,stDate.day);
				SalesAnalysis_UI_StatSale(id, stDate, endDate);
				break;
			}
		} while (choice != 'r' && choice != 'R');

	}
}



