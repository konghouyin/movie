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
* Description: 以列表模式显示剧目信息
* Input:       list剧目信息链表的头指针，paging分页设置参数
* Output:      所有剧目的信息
* Return:      返回查找到的记录数目
*/
void Play_UI_ShowList(play_list_t list, Pagination_t paging) {
	int i;
	play_node_t *pos;

	system("cls");
	kuangjia();
	goto_xy(30, 8);
	printf("              ---->>      上映剧目列表    <<----\n");

	printf("\t\t\t==============================================================================\n");
	for (i = 0, pos = (play_node_t *)(paging.curPos); pos != list && i < paging.pageSize; i++)
	{
		goto_xy(38, 11);
		printf("片名：%s", pos->data.name);
		goto_xy(38, 13);
		printf("种类：%s", type(pos->data.type));
		goto_xy(38, 15);
		printf("等级：%s", rating(pos->data.rating));
		goto_xy(38, 17);
		printf("时长：%d分钟", pos->data.duration);
		goto_xy(38, 19);
		printf("价格：%d元", pos->data.price);


		goto_xy(68, 11);
		printf("ID：%d", pos->data.id);
		goto_xy(68, 13);
		printf("地区：%s", pos->data.area);
		goto_xy(68, 15);
		printf("上映日期：%4d-%02d-%02d", pos->data.start_date.year, pos->data.start_date.month, pos->data.start_date.day);
		goto_xy(68, 17);
		printf("下架日期：%4d-%02d-%02d\n\n\n\n", pos->data.end_date.year, pos->data.end_date.month, pos->data.end_date.day);

		pos = pos->next;
	}
	//剧目类型定义，1表示电影，2表示歌剧，3表示音乐会
	//演出级别类型定义，1表示儿童可观看，2表示青少年可观看，3表示成人可观看

}

/*
* Function:    Play_UI_MgtEntry
* Function ID:	TTMS_SCU_Play_UI_MgtEnt
* Description: 剧目信息管理界面
* Input:       flag为0，进入管理页面，flag为1进入查询界面
* Output:      剧目管理界面
* Return:      无
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
	//载入数据
	paging.totalRecords = Play_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);

	if (flag)
	{
		do {
			system("cls");
			Play_UI_ShowList(head, paging); 
			printf("\t\t\t\t------- 剧目总数:%2d ---------------------------- 位置 %2d/%2d ------\n",
				paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));
			printf("\t\t\t    ************************************************************************  \n");
			printf("\t\t\t          [P]上一个  [N]下一个                        [Q]查询   [R]返回");
			printf("\n\t\t\t================================================================================\n");
			printf("\t\t\t\t请选择:");
			choice = getche();
			char name[30];
			switch (choice)
			{
			case 'q':
			case 'Q':
				printf("\t\t\t\t请输入查询片名: ");
				scanf("%s", name);


				getchar();
				if (Play_UI_Query_Name(name)) {	//从新载入数据
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
			printf("\t\t\t\t--------- 剧目总数:%2d ---------------------------- 位置 %2d/%2d ------\n\n",
				paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));
			printf("\t\t\t*******************************************************************************\n");
			printf("\t\t\t[P]上一个  [N]下一个   |   [A]增加  [D]删除  [U]修改  [Q]查询  [S]计划  [R]返回");
			printf("\n\t\t\t================================================================================\n");
			printf("\t\t\t\t请选择: ");
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
				if (Play_UI_Add()) //新添加成功，跳到最后一页显示
				{
					paging.totalRecords = Play_Srv_FetchAll(head);
					Paging_Locate_LastPage(head, paging, play_node_t);
				}
				break;
			case 'd':
			case 'D':
				printf("\t\t\t请输入删除ID: ");
				scanf("%d", &id);
				getchar();
				if (Play_UI_Delete(id)) {	
					//从新载入数据
					paging.totalRecords = Play_Srv_FetchAll(head);
					List_Paging(head, paging, play_node_t);
				}
				break;
			case 'u':
			case 'U':
				printf("\t\t\t输入需要修改的ID号: ");
				scanf("%d", &id);
				getchar();
				if (Play_UI_Modify(id)) {	//从新载入数据
					paging.totalRecords = Play_Srv_FetchAll(head);
					List_Paging(head, paging, play_node_t);
				}
				break;
			case 'q':
			case 'Q':
				printf("\t\t\t输入需要查询的片名: ");
				scanf("%s", name);
				getchar();
				if (Play_UI_Query_Name(name)) {	//从新载入数据
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
	printf("    ---->>     备选列表    <<----\n");


	for (i = 0, pos = (play_node_t *)(paging.curPos); pos != list && i < paging.pageSize; i++)
	{
		goto_xy(35, 13);
		printf("片名：%s         ", pos->data.name);
		goto_xy(35, 15);
		printf("种类：%s         ", type(pos->data.type));
		goto_xy(35, 17);
		printf("等级：%s         ", rating(pos->data.rating));
		goto_xy(35, 19);
		printf("时长：%d分钟      ", pos->data.duration);
		goto_xy(35, 21);
		printf("价格：%d元        ", pos->data.price);
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
	//载入数据
	paging.totalRecords = Play_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);

		do {

			id=Play_UI_ShowList_schedule(head, paging);
			printf("\n\n\t\t         --- 剧目总数:%2d ------ 位置 %2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));
			printf("\t\t      ********************************************** \n");
			printf("\t\t        [P]上一个 [N]下一个 | [Y]确认 [W]手动输入");
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
//为演出计划添加提供数据


/*
* Function:    Play_UI_Add
* Function ID:	TTMS_SCU_Play_UI_Add
* Description: 添加一条剧目信息
* Input:       无
* Output:      输入信息时的各种提示
* Return:      添加的记录数
*/
int Play_UI_Add(void) {

	play_t rec;
	char choice;
	int newRecCount = 0;

	do {
		system("cls");
		kuangjia();
		goto_xy(30, 6);
		printf("              ---->>    添加新的剧目信息    <<----\n");
		goto_xy(30, 7);
		printf("\t       ==============================================\n");

		printf("\n\t\t\t\t\t剧目名称: ");
		fflush(stdin);
		fgets(rec.name, 30, stdin);
		int l = strlen(rec.name);
		rec.name[l - 1] = '\0';

		printf("\n\t\t\t\t\t剧目类型（1--电影，2--歌剧，3--音乐会）: ");
		scanf("%d", &rec.type);//剧目类型定义，1--电影，2--歌剧，3--音乐会

		printf("\n\t\t\t\t\t剧目地区: ");
		getchar();
		fgets(rec.area, 8, stdin);
		l = strlen(rec.area);
		rec.area[l - 1] = '\0';

		printf("\n\t\t\t\t\t剧目分级（1--儿童，2--青少年，3--成人）: ");
		scanf("%d", &rec.rating);//演出级别类型定义，1表示儿童可观看，2表示青少年可观看，3表示成人可观看

		printf("\n\t\t\t\t\t播放时间（单位-分钟）: ");
		scanf("%d", &rec.duration);

		printf("\n\t\t\t\t\t上架日期 (年 月 日): ");
		scanf("%d%d%d", &rec.start_date.year, &rec.start_date.month, &rec.start_date.day);

		printf("\n\t\t\t\t\t下架日期 (年 月 日): ");
		scanf("%d%d%d", &rec.end_date.year, &rec.end_date.month, &rec.end_date.day);

		printf("\n\t\t\t\t\t剧目票价（元）: ");
		scanf("%d", &rec.price);

		getchar();
		printf("\n\t\t\t\t  =======================================================\n");

		//获取主键
		char type[] = "Play";
		rec.id = EntKey_Srv_CompNewKey(type);

		if (Play_Srv_Add(&rec)) {
			newRecCount += 1;
			printf("\n\t\t\t\t\t剧目添加成功!");
		}
		else
			printf("\t\t\t\t\t剧目添加失败!");
		printf("\t\t[A]添加     [R]返回");

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
* Description: 更新剧目信息
* Input:       待更新的剧目ID号
* Output:      输入信息时的各种提示
* Return:      更新的剧目信息数，0表示未找到，1表示找到并更新
*/
int Play_UI_Modify(int id) {
	play_t rec;
	int rtn = 0;

	/*Load record*/
	if (!Play_Srv_FetchByID(id, &rec)) {
		printf("\t\t\t\t剧目不存在!\t\t\t按 [Enter] 返回\n");
		getchar();
		return 0;
	}
	//界面	
	system("cls");
	kuangjia();
	goto_xy(30, 6);
	printf("              ---->>    修改剧目信息    <<----\n");
	goto_xy(30, 7);
	printf("\t       ==============================================\n");
	printf("\n\t\t\t\t\t剧目名称: ");
	fflush(stdin);
	fgets(rec.name, 30, stdin);
	int l = strlen(rec.name);
	rec.name[l - 1] = '\0';

	printf("\n\t\t\t\t\t剧目类型:（1--电影，2--歌剧，3--音乐会） ");
	scanf("%d", &rec.type);//剧目类型定义，1--电影，2--歌剧，3--音乐会

	printf("\n\t\t\t\t\t剧目地区: ");
	getchar();
	fgets(rec.area, 8, stdin);
	l = strlen(rec.area);
	rec.area[l - 1] = '\0';

	printf("\n\t\t\t\t\t剧目分级:（1--儿童，2--青少年，3--成人）");
	scanf("%d", &rec.rating);//演出级别类型定义，1表示儿童可观看，2表示青少年可观看，3表示成人可观看

	printf("\n\t\t\t\t\t播放时间（单位-分钟）: ");
	scanf("%d", &rec.duration);

	printf("\n\t\t\t\t\t上架日期 (年 月 日): ");
	scanf("%d%d%d", &rec.start_date.year, &rec.start_date.month, &rec.start_date.day);

	printf("\n\t\t\t\t\t下架日期 (年 月 日): ");
	scanf("%d%d%d", &rec.end_date.year, &rec.end_date.month, &rec.end_date.day);

	printf("\n\t\t\t\t\t剧目票价（元）: ");
	scanf("%d", &rec.price);

	getchar();
	printf("\n\t\t\t\t  =======================================================\n");

	

	if (Play_Srv_Modify(&rec)) {
		rtn = 1;
		printf(
			"\t\t\t\t\t剧目信息修改成功!\t\t按 [Enter] 返回\n\t\t\t");
	}
	else
		printf("\t\t\t\t\t剧目信息修改失败!t\t按 [Enter] 返回\n\t\t\t");
	getchar();
	return rtn;
}

/*
* Function:    Play_UI_Delete
* Function ID:	TTMS_SCU_Play_UI_Del
* Description: 按照ID号删除剧目信息
* Input:       待删除的剧目ID号
* Output:      提示删除是否成功
* Return:      0表示删除失败，1表示删除成功
*/
int Play_UI_Delete(int id) {

	int rtn = 0;
	play_t rec;
	schedule_list_t head;
	List_Init(head, schedule_node_t);
	Schedule_Srv_FetchAll(head);

	if (!Play_Srv_FetchByID(id, &rec))
	{
		printf("\t\t\t\t剧目ID不存在!\t\t\t按 [Enter] 返回\n\t\t\t");
		getchar();
		return 0;
	}
	goto_xy(0, 27);
	printf("\t\t\t                                                                                            \n");
	printf("\t\t\t                                                                                            \n");
	printf("\t\t\t                                                                                            \n");
	goto_xy(0, 27);
	printf("\t\t\t\t是否确认删除 ID ： %d 的剧目( Y / N )", id);
	char ch = getche();
	if (ch != 'Y'&&ch != 'y')
		return 0;

	if (Schedule_Srv_DeleteByPlay(head, id))
	{
		goto_xy(35, 29);
		printf("相关的演出计划删除成功!");
		rtn = 1;
	}
	if (Play_Srv_DeleteByID(id)) {
		goto_xy(50, 29);
		printf("剧目删除成功!\t\t按 [Enter] 返回\n\t\t\t");
		rtn = 1;
	}

	getchar();

	return rtn;
}

/*
* Function:    Play_UI_Query
* Function ID:	TTMS_SCU_Play_UI_Qry
* Description: 按照ID号查询剧目信息
* Input:       待查找的剧目ID号
* Output:      查找到的剧目信息
* Return:      0表示未找到，1表示找到了
*/
int Play_UI_Query(int id) {
	int rtn = 0;
	play_t rec;
	if (!Play_Srv_FetchByID(id, &rec)) {
		printf("\t\t\t\t剧目ID输入错误!\t\t\t按 [Enter] 返回\n\t\t\t");
		getchar();
		return 0;
	}
	//界面	
	system("cls");
	kuangjia();
	goto_xy(30, 10);
	printf("              ---->>      查询的剧目信息    <<----\n");

	printf("\t\t\t==============================================================================\n");
	goto_xy(38, 13);
	printf("片名：%s", rec.name);
	goto_xy(38, 15);
	printf("种类：%s", type(rec.type));
	goto_xy(38, 17);
	printf("等级：%s", rating(rec.rating));
	goto_xy(38, 19);
	printf("时长：%d", rec.duration);
	goto_xy(38, 21);
	printf("价格：%d", rec.price);


	goto_xy(68, 13);
	printf("ID：%d", rec.id);
	goto_xy(68, 15);
	printf("地区：%s", rec.area);
	goto_xy(68, 17);
	printf("上映日期：%4d-%02d-%02d", rec.start_date.year, rec.start_date.month, rec.start_date.day);
	goto_xy(68, 19);
	printf("下架日期：%4d-%02d-%02d\n\n\n\n", rec.end_date.year, rec.end_date.month, rec.end_date.day);

	printf("\n\t\t\t================================================================================\n");

	printf("\t\t\t\t\t按 [Enter] 返回\n\t\t\t");
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
		printf("\t\t\t\t查询无果!\t\t\t\t按 [Enter] 返回\n\t\t\t");
		getchar();
		return 0;
	}

	//界面	
	system("cls");
	kuangjia();
	goto_xy(30, 9);
	printf("              ---->>      查询的剧目信息    <<----\n");

	printf("\t\t\t==============================================================================\n");
	goto_xy(38, 12);
	printf("片名：%s", rec.name);
	goto_xy(38, 14);
	printf("种类：%s", type(rec.type));
	goto_xy(38, 16);
	printf("等级：%s", rating(rec.rating));
	goto_xy(38, 18);
	printf("时长：%d 分钟", rec.duration);
	goto_xy(38, 20);
	printf("价格：%d 元", rec.price);


	goto_xy(68, 12);
	printf("ID：%d", rec.id);
	goto_xy(68, 14);
	printf("地区：%s", rec.area);
	goto_xy(68, 16);
	printf("上映日期：%4d-%02d-%02d", rec.start_date.year, rec.start_date.month, rec.start_date.day);
	goto_xy(68, 18);
	printf("下架日期：%4d-%02d-%02d\n\n\n\n", rec.end_date.year, rec.end_date.month, rec.end_date.day);

	printf("\n\t\t\t================================================================================\n");

	printf("\t\t\t\t\t\t\t按 [Enter] 返回\n\t\t\t");
	getchar();
	return 1;
}




char *type(int type)
{
	static char back[5];
	if (type == 1)
	{
		strcpy(back, "电影");
	}
	else if (type == 2)
	{
		strcpy(back,"歌剧" );
	}
	else if (type == 3)
	{
		strcpy(back,"音乐" );
	}
	else
		strcpy(back,"其他" );
	return back;
}
char *rating(int rating)
{
	static char back[8];
	if (rating == 1)
	{
		strcpy(back, "儿童剧");
	}
	else if (rating == 2)
	{
		strcpy(back, "青年剧");
	}
	else if (rating == 3)
	{
		strcpy(back,"成人剧" );
	}
	else
		strcpy(back, "其它");
	return back;
}
