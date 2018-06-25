/*
* salesanalysis.c
*
*  Created on: 2015年6月12日
*      Author: Administrator
*/
#include <string.h>
#include <stdio.h>
#include "SalesAnalysis.h"
#include "../Persistence/Sale_Persist.h"
#include "../Persistence/SalesAnalysis_Persist.h"
#include "Sale.h"
#include "Ticket.h"
#include "Play.h"
#include "Schedule.h"
#include "../Common/list.h"

//计算员工usrID在给定时间区间的销售额，返回销售额
int Salesanalysis_Srv_CompSaleVal(int usrID, user_date_t stDate, user_date_t endDate) {
	int amount = 0;
	int i, j;
	sale_list_t saleList;
	sale_node_t *pos;

	List_Init(saleList, sale_node_t);
	/*根据id载入匹配的销售信息，构建saleList链表*/
	Sale_Perst_SelectAll(saleList);
	List_ForEach(saleList, pos)
	{
		i = DateCmp(pos->data.date, stDate);
		j = DateCmp(endDate, pos->data.date);
		if (pos->data.user_id == usrID && i != -1 && j != -1) {
			amount = amount + pos->data.value;
		}
	}//修改完成
	List_Destroy(saleList, sale_node_t);
	return amount;
}

//计算所有人员在给定时间区间的销售额，返回销售额
int Salesanalysis_Srv_CompSaleVal_all(user_date_t stDate, user_date_t endDate) {
	int amount = 0;
	int i, j;
	sale_list_t saleList;
	sale_node_t *pos;

	List_Init(saleList, sale_node_t);
	/*根据id载入匹配的销售信息，构建saleList链表*/
	Sale_Perst_SelectAll(saleList);
	List_ForEach(saleList, pos)
	{
		i = DateCmp(pos->data.date, stDate);
		j = DateCmp(endDate, pos->data.date);
		if ( i != -1 && j != -1) {
			amount = amount + pos->data.value;
		}
	}//修改完成
	List_Destroy(saleList, sale_node_t);
	return amount;
}

//结合剧目Play.dat,统计销售数据，构建销售分析salesanalysis_list_t list链表，返回list链表长度
int Salesanalysis_Srv_StaticSale(salesanalysis_list_t list) {
	int count = 0;
	assert(NULL != list);
	play_list_t playList;
	play_node_t *pos;
	salesanalysis_node_t *newNode;
	int sold, total;

	List_Free(list, salesanalysis_node_t);

	List_Init(playList, play_node_t);
	Play_Srv_FetchAll(playList);

	List_ForEach(playList, pos)
	{
		//printf("剧目 ID:%s\n", pos->data.name);
		newNode = (salesanalysis_node_t*)malloc(sizeof(salesanalysis_node_t));
		if (!newNode)
		{
			printf("内存分配失败!!\n");
			break;
		}
		newNode->data.play_id = pos->data.id;
		strcpy(newNode->data.name, pos->data.name);
		strcpy(newNode->data.area, pos->data.area);
		newNode->data.duration = pos->data.duration;
		newNode->data.start_date = pos->data.start_date;
		newNode->data.end_date = pos->data.end_date;
		newNode->data.price = pos->data.price;
		newNode->data.sales = Schedule_Srv_StatRevByPlay(pos->data.id, &sold, &total);
		newNode->data.totaltickets = sold;
		//printf("\n%s    %d\n",newNode->data.name,newNode->data.sales);
		List_AddTail(list, newNode);
		count++;
	}
	List_Destroy(playList, play_node_t);
	//printf("操作已完成！\n");
	return count;
}

//对剧院电影票房排序
void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list) {
	salesanalysis_node_t *p, *listLeft;
	assert(list != NULL);

	if (List_IsEmpty(list))
		return;

	//将next指针构成的循环链表从最后一个结点断开
	list->prev->next = NULL;

	//listLeft指向第一个数据节点
	listLeft = list->next;

	//将list链表置为空
	list->next = list->prev = list;

	while (listLeft != NULL) {
		//取出第一个结点
		p = listLeft;
		listLeft = listLeft->next;

		//将结点p加入到已排序链表list中
		SalesAnalysis_Srv_AddToSoftedList(list, p);
	}
}


//将结点node加入到已排序链表list中
void SalesAnalysis_Srv_AddToSoftedList(salesanalysis_list_t list, salesanalysis_node_t *node) {

	salesanalysis_node_t *p;

	assert(list != NULL && node != NULL);

	if (List_IsEmpty(list)) {
		List_AddTail(list, node);
	}
	else {
		//寻找插入位置
		p = list->next;

		while (p != list && (p->data.sales>node->data.sales)) {
			p = p->next;
		}
		//将结点node加入到p之前
		List_InsertBefore(p, node);
	}
}
