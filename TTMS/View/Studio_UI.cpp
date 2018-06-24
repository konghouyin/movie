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
//管理演出厅界面
void Studio_UI_MgtEntry(account_type_t type) {
	int i, id;
	char choice;

	studio_list_t head;
	studio_node_t *pos;
	Pagination_t paging;
	List_Init(head, studio_node_t);
	paging.offset = 0;
	paging.pageSize = STUDIO_PAGE_SIZE;
	//载入数据
	paging.totalRecords = Studio_Srv_FetchAll(head);//统计一共有多少演出厅，并创建链表
	Paging_Locate_FirstPage(head, paging);//定位到翻页器的第一页
	//翻页器没有再新建列表，只是通过相关操作，定位到需要打印信息的地址
	if (type == 9) {
		do {
			system("cls");
			kuangjia();
			goto_xy(30, 6);
			printf("                  ---->>    演出厅列表    <<----\n");
			printf("\t\t\t------------------------------------------------------------------------------\n");
			printf("\t\t\t    %-5s     %-18s    %-12s    %-12s   %-12s\n", "ID", "房间名称", "行数",
				"列数", "座位数");
			printf("\t\t\t------------------------------------------------------------------------------\n");
			//显示数据
			for (i = 0, pos = (studio_node_t *)(paging.curPos);
				pos != head && i < paging.pageSize; i++)//for循环打印当前页（初始化计数器，先获取需要打印第一个信息的地址；终止条件：循环链表碰到开头，或打印个数与最大值相等；递增i）
			{
				printf("\t\t\t    %-5d     %-18s    %-12d    %-12d   %-12d\n\n", pos->data.id,
					pos->data.name, pos->data.rowsCount, pos->data.colsCount,
					pos->data.seatsCount);
				pos = pos->next;//指向下一个节点
			}
			//打印翻页信息
			goto_xy(0, 21);
			printf("\t\t\t   --------- 总个数:%2d -------------------------------- 页数 %2d/%2d --------\n\n",
				paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));//总个数；计算当前页；计算总个数
			printf("\t\t\t******************************************************************************\n");
			printf("\t\t\t[P]上一页|[N]下一页             [A]增加 |[D]删除 |[U]修改 | [S]座位 | [R]返回");
			printf("\n\t\t\t==============================================================================\n");
			printf("\t\t\t\t请选择功能:");
			while (_kbhit())
			{
				getch();
			}
			choice = getche();
			switch (choice)
			{
			case 'a':
			case 'A':
				if (Studio_UI_Add()) //新添加成功，跳到最后一页显示
				{
					paging.totalRecords = Studio_Srv_FetchAll(head);//统计演出厅个数，并创建链表
					Paging_Locate_LastPage(head, paging, studio_node_t);//翻页器最后一页准备
				}
				break;
			case 'd':
			case 'D':
				printf("\t\t\t输入想要删除的演出厅ID:");
				scanf("%d", &id);
				getchar();
				if (Studio_UI_Delete(id)) {	//从新载入数据
					paging.totalRecords = Studio_Srv_FetchAll(head);
					List_Paging(head, paging, studio_node_t);//设置偏移量，使界面呈现到刚刚删除的位置
				}
				break;
			case 'u':
			case 'U':
				printf("\t\t\t输入想要修改的演出厅ID:");
				scanf("%d", &id);
				if (Studio_UI_Modify(id)) {	//从新载入数据
					paging.totalRecords = Studio_Srv_FetchAll(head);
					List_Paging(head, paging, studio_node_t);
				}
				break;
			case 's':
			case 'S':
				printf("\t\t\t输入进行座位管理的演出厅ID:");
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
	else//管理员有修改权限，一般用户只能查找，不能修改
	{
		do {
			system("cls");
			kuangjia();
			goto_xy(30, 6);
			printf("                  ---->>    演出厅列表    <<----\n");
			printf("\t\t\t------------------------------------------------------------------------------\n");
			printf("\t\t\t    %-5s     %-18s    %-12s    %-12s   %-12s\n", "ID", "房间名称", "行数",
				"列数", "座位数");
			printf("\t\t\t------------------------------------------------------------------------------\n");
			//显示数据
			for (i = 0, pos = (studio_node_t *)(paging.curPos);
				pos != head && i < paging.pageSize; i++)//for循环打印当前页（初始化计数器，先获取需要打印第一个信息的地址；终止条件：循环链表碰到开头，或打印个数与最大值相等；递增i）
			{
				printf("\t\t\t    %-5d     %-18s    %-12d    %-12d   %-12d\n\n", pos->data.id,
					pos->data.name, pos->data.rowsCount, pos->data.colsCount,
					pos->data.seatsCount);
				pos = pos->next;//指向下一个节点
			}
			//打印翻页信息
			goto_xy(0, 21);
			printf("\t\t\t   --------- 总个数:%2d -------------------------------- 页数 %2d/%2d --------\n\n",
				paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));//总个数；计算当前页；计算总个数
			printf("\t\t\t******************************************************************************\n");
			printf("\t\t\t             [P]上一页 | [N]下一页                       [R]返回");
			printf("\n\t\t\t==============================================================================\n");
			printf("\t\t\t\t请选择功能:");
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
	//释放链表空间
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
		printf("              ---->>    增加新的演出厅    <<----\n");
		printf("\t\t\t\t    -------------------------------------------------------\n");
		printf("\n\t\t\t\t\t\t    房间名称: ");
		fgets(rec.name, 30, stdin);
		int l = strlen(rec.name);
		rec.name[l - 1] = '\0';
		printf("\n\t\t\t\t\t\t    行数: ");
		scanf("\n\t\t\t%d", &rec.rowsCount);
		printf("\n\t\t\t\t\t\t    列数: ");
		scanf("%d", &rec.colsCount);
		getchar();
		rec.seatsCount = 0;
		printf("\t\t\t\t\t=============================================\n");

		//获取主键
		char type[] = "Studio";
		rec.id = EntKey_Srv_CompNewKey(type);  //为数据分配主键

		if (Studio_Srv_Add(&rec)) {
			newRecCount += 1;
			printf("\t\t\t\t\t\t     添加成功!\n");
		}
		else
			printf("\t\t\t\t\t添加失败\n");
		printf("\t\t\t\t    -------------------------------------------------------\n");
		printf("\t\t\t\t\t    [A]再次添加               [R]返回:");
		choice = getche();
	} while ('a' == choice || 'A' == choice);
	return newRecCount;//返回值来确认是否添加成功
}

int Studio_UI_Modify(int id) {
	studio_t rec;
	int rtn = 0;
	int newrow, newcolumn;
	seat_list_t list;
	int seatcount;

	//查找文件中是否具有相关ID
	if (!Studio_Srv_FetchByID(id, &rec)) {
		printf("\t\t\t输入的演出厅不存在!\n\t\t\t按 [Enter] 返回\n");
		getchar();
		return 0;
	}

	system("cls");
	kuangjia();
	goto_xy(30, 6);
	printf("              ---->>    修改%d号演出厅信息    <<----\n", id);
	printf("\t\t\t\t----------------------------------------------------------\n");
	printf("\n\t\t\t\t\t\t演出厅 ID:%d\n", rec.id);
	printf("\n\t\t\t\t\t\t演出厅名称 [%s]:", rec.name);
	getchar();
	fgets(rec.name, 30, stdin);
	int l = strlen(rec.name);
	rec.name[l - 1] = '\0';

	List_Init(list, seat_node_t);
	seatcount = Seat_Srv_FetchByRoomID(list, rec.id);
	if (seatcount) {
		do {			//如果座位文件中已有座位信息，则更新的行列必须比以前大，否则不允许更改
			printf("\n\t\t\t\t\t\t输入行数应 >= [%d]:", rec.rowsCount);
			scanf("\t\t\t%d", &(newrow));
			printf("\n\t\t\t\t\t\t输入的列数应 >= [%d]:", rec.colsCount);
			scanf("%d", &(newcolumn));
		} while (newrow<rec.rowsCount || newcolumn<rec.colsCount);
		getchar();
		rec.rowsCount = newrow;
		rec.colsCount = newcolumn;
		rec.seatsCount = seatcount;
	}
	else {
		printf("\n\t\t\t\t\t\t输入行数:");
		scanf("%d", &rec.rowsCount);
		printf("\n\t\t\t\t\t\t输入列数:");
		scanf("%d", &rec.colsCount);
		rec.seatsCount = 0;
	}

	printf("\n\t\t\t\t---------------------------------------------------------\n");

	if (Studio_Srv_Modify(&rec)) {
		rtn = 1;
		printf("\t\t\t\t\t演出厅信息更新完成!\t\t按 [Enter] 返回\n\t\t\t");
	}
	else
		printf("\t\t\t\t\t演出厅信息更新失败!\t\t请稍后重试!\n\t\t\t");
	getchar();
	getchar();
	return rtn;
}

int Studio_UI_Delete(int id) {

	int rtn = 0;

	if (Studio_Srv_DeleteByID(id)) {
		//在删除放映厅时，同时根据放映厅id删除座位文件中的座位

		if (Seat_Srv_DeleteAllByRoomID(id))//删除演出厅id的所有座位
			printf("\t\t\t\t\t\t演出厅对应的座位信息删除成功!\n");
		printf(
			"\t\t\t\t演出厅信息删除成功!!\t\t按 [Enter] 返回\n");
		rtn = 1;
	}
	else {
		printf("\t\t\t\t输入的演出厅不存在!\t\t按 [Enter] 返回\n");
	}
	printf("\t\t\t");
	getchar();
	return rtn;//返回值表示是否返回成功
}
