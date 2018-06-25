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
#include "../Common/window.h"
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
		system("cls");
		kuangjia();
		goto_xy(0, 5);
		printf("\t\t                                                                                                ");
		printf("\n\t\t\t    ==================================================================\n");
		printf("\t\t\t    ***************************  总票房排名  *************************\n");
		printf("\t\t\t    %10s  %12s  %10s    %s     %s\n", "排名", "剧目名称", "售价","数量","票房");
		printf("\t\t\t    ------------------------------------------------------------------\n");
		//显示数据
		int icount = 1;
		for (i = 0, pos = head->next;
			pos != head && i < paging.pageSize; i++)
		{
			printf("\t\t\t    %8d  %12s          %3d     %2d  %8ld\n", icount, pos->data.name,pos->data.price,pos->data.totaltickets, pos->data.sales);
			pos = pos->next;
			icount++;
		}
		goto_xy(0, 21);
		printf("\t\t             ----- 剧目总数 :%2d ---------------- 页码： %2d/%2d -----    \n", paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));
		printf("\t\t\t    = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
		printf("\t\t\t              [P] 上一页      [N] 下一页      [R] 返回 \n");
		printf("\n\t\t\t    ==================================================================\n");
		printf("\t\t\t    请输入您的选择：");
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
	printf("\n\n\t\t\t\t    ========================================================\n");
	printf("\t\t\t\t       ***************  售票员销售情况  *****************\n");
	printf("\t\t\t\t    ========================================================\n");
	printf("\t\t\t\t    %10s %20s %15s\n", "人员ID", "用户名", "销售额");
	printf("\t\t\t\t    %10d %20s %15d\n", buf.id, buf.username, rtn);
	printf("\t\t\t\t    --------------------------------------------------------\n");
	printf("\t\t\t\t\t按[Enter]键返回");
	getchar();

	return;
}


void SalesAnalysis_UI_StatSale_all(user_date_t stDate, user_date_t endDate) {
	int rtn;
	rtn = Salesanalysis_Srv_CompSaleVal_all(stDate, endDate);
	printf("\n\n\t\t\t\t    ========================================================\n");
	printf("\t\t\t\t       ***************  日期销售情况  *****************\n");
	printf("\t\t\t\t    ========================================================\n");
	printf("\t\t\t\t             查询时间                            销售额\n\n");
	printf("\t\t\t\t    %d年%d月%d日--%d年%d月%d日                %d\n", stDate.year,stDate.month,stDate.day,endDate.year,endDate.month,endDate.day,rtn);
	printf("\t\t\t\t    --------------------------------------------------------\n");
	printf("\t\t\t\t\t按[Enter]键返回");
	getchar();
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
			printf("\t\t\t                -------->       销售数据管理        <-------\n");
			printf("\t\t\t--------------------------------------------------------------------------\n");
			printf("\t\t\t      [T]票房排名  |  [U]日期销售统计  |  [O]人员销售统计  | [R]返回");
			printf("\n\t\t\t==========================================================================\n");
			printf("\t\t\t    请选择: ");
			choice = getche();
			char name[30];
			account_t buf;
			switch (choice)
			{
			case 't':
			case 'T':
				printf("\n");
				SalesAnalysis_UI_BoxOffice();
				break;
			case 'u':
			case 'U':
				printf("\n\t\t\t    请输入开始查询日期(年 月 日): ");
				scanf("%d%d%d", &stDate.year, &stDate.month, &stDate.day);
				printf("\t\t\t    请输入结束查询日期(年 月 日): ");
				scanf("%d%d%d", &endDate.year, &endDate.month, &endDate.day);
				getchar();
				SalesAnalysis_UI_StatSale_all(stDate, endDate);
				break;
			case 'o':
			case 'O':
				printf("\n\t\t\t    请输入查询售票员的用户名:");
				scanf("%s", name);
				//name->id
				if (!Account_Srv_FetchByName(name, &buf))
				{
					goto_xy(50, 10);
					printf("\t\t\t查无此人！  按[Enter]键返回");
					getchar();
					getchar();
					break;
				}
				getchar();
				printf("\n\t\t\t    请输入开始查询日期(年 月 日): ");
				scanf("%d%d%d", &stDate.year, &stDate.month, &stDate.day);
				printf("\t\t\t    请输入结束查询日期(年 月 日): ");
				scanf("%d%d%d", &endDate.year, &endDate.month, &endDate.day);
				getchar();
				SalesAnalysis_UI_StatSale(buf.id, stDate, endDate);
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
			printf("\t\t\t                -------->       销售数据管理        <-------\n");
			printf("\t\t\t--------------------------------------------------------------------------\n");
			printf("\t\t\t   [T]票房排名  |  [U]个人当日销售统计  |  [O]个人区间销售统计  | [R]返回");
			printf("\n\t\t\t==========================================================================\n");
			printf("\t\t\t    请选择: ");
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
			case 'u':
			case 'U':
				id = gl_CurUser.id;
				stDate = DateNow();
				endDate = DateNow();
				SalesAnalysis_UI_StatSale(id, stDate, endDate);
				break;
			case 'o':
			case 'O':
				id = gl_CurUser.id;
				printf("\n\t\t\t    请输入开始查询日期(年 月 日): ");
				scanf("%d%d%d", &stDate.year, &stDate.month, &stDate.day);
				printf("\t\t\t    请输入结束查询日期(年 月 日): ");
				scanf("%d%d%d", &endDate.year, &endDate.month, &endDate.day);
				getchar();
				SalesAnalysis_UI_StatSale(id, stDate, endDate);
			}
		} while (choice != 'r' && choice != 'R');
	}
}



