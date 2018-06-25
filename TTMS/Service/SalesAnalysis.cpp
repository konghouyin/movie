/*
* salesanalysis.c
*
*  Created on: 2015��6��12��
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

//����Ա��usrID�ڸ���ʱ����������۶�������۶�
int Salesanalysis_Srv_CompSaleVal(int usrID, user_date_t stDate, user_date_t endDate) {
	int amount = 0;
	int i, j;
	sale_list_t saleList;
	sale_node_t *pos;

	List_Init(saleList, sale_node_t);
	/*����id����ƥ���������Ϣ������saleList����*/
	Sale_Perst_SelectAll(saleList);
	List_ForEach(saleList, pos)
	{
		i = DateCmp(pos->data.date, stDate);
		j = DateCmp(endDate, pos->data.date);
		if (pos->data.user_id == usrID && i != -1 && j != -1) {
			amount = amount + pos->data.value;
		}
	}//�޸����
	List_Destroy(saleList, sale_node_t);
	return amount;
}

//����������Ա�ڸ���ʱ����������۶�������۶�
int Salesanalysis_Srv_CompSaleVal_all(user_date_t stDate, user_date_t endDate) {
	int amount = 0;
	int i, j;
	sale_list_t saleList;
	sale_node_t *pos;

	List_Init(saleList, sale_node_t);
	/*����id����ƥ���������Ϣ������saleList����*/
	Sale_Perst_SelectAll(saleList);
	List_ForEach(saleList, pos)
	{
		i = DateCmp(pos->data.date, stDate);
		j = DateCmp(endDate, pos->data.date);
		if ( i != -1 && j != -1) {
			amount = amount + pos->data.value;
		}
	}//�޸����
	List_Destroy(saleList, sale_node_t);
	return amount;
}

//��Ͼ�ĿPlay.dat,ͳ���������ݣ��������۷���salesanalysis_list_t list��������list������
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
		//printf("��Ŀ ID:%s\n", pos->data.name);
		newNode = (salesanalysis_node_t*)malloc(sizeof(salesanalysis_node_t));
		if (!newNode)
		{
			printf("�ڴ����ʧ��!!\n");
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
	//printf("��������ɣ�\n");
	return count;
}

//�Ծ�Ժ��ӰƱ������
void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list) {
	salesanalysis_node_t *p, *listLeft;
	assert(list != NULL);

	if (List_IsEmpty(list))
		return;

	//��nextָ�빹�ɵ�ѭ����������һ�����Ͽ�
	list->prev->next = NULL;

	//listLeftָ���һ�����ݽڵ�
	listLeft = list->next;

	//��list������Ϊ��
	list->next = list->prev = list;

	while (listLeft != NULL) {
		//ȡ����һ�����
		p = listLeft;
		listLeft = listLeft->next;

		//�����p���뵽����������list��
		SalesAnalysis_Srv_AddToSoftedList(list, p);
	}
}


//�����node���뵽����������list��
void SalesAnalysis_Srv_AddToSoftedList(salesanalysis_list_t list, salesanalysis_node_t *node) {

	salesanalysis_node_t *p;

	assert(list != NULL && node != NULL);

	if (List_IsEmpty(list)) {
		List_AddTail(list, node);
	}
	else {
		//Ѱ�Ҳ���λ��
		p = list->next;

		while (p != list && (p->data.sales>node->data.sales)) {
			p = p->next;
		}
		//�����node���뵽p֮ǰ
		List_InsertBefore(p, node);
	}
}
