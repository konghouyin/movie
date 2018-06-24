#include "Sale_Persist.h"
#include "../Common/list.h"
#include "../Service/Sale.h"
#include <stdio.h>
#include "../Common/common.h"
#include <io.h>
#include <process.h>
#include <stdlib.h>
#include <string.h>


static const char SALE_DATA_FILE[] = "Sale.dat";
static const char SALE_DATA_TEMP_FILE[] = "SaleTmp.dat";

int Sale_Perst_Insert(const sale_t *data) {
	assert(NULL != data);
	FILE *fp = fopen(SALE_DATA_FILE, "ab");
	int rtn = 0;
	if (NULL == fp) {
		printf("Cannot open file %s!\n", SALE_DATA_FILE);
		return 0;
	}
	rtn = fwrite(data, sizeof(sale_t), 1, fp);//���óɹ�������count��ֵ��������ɹ�������0��
	fclose(fp);
	return rtn;
}

int Sale_Perst_DeleteByID(int saleID) {
	//��ԭʼ�ļ���������Ȼ���ȡ��������д�뵽�����ļ��У�����Ҫɾ����ʵ����˵�����������һ���ļ���
	//��ԭʼ�����ļ�������
	if (rename(SALE_DATA_FILE, SALE_DATA_TEMP_FILE)<0) {
		printf("Cannot open file %s!\n", SALE_DATA_FILE);
		return 0;
	}

	FILE *fpSour, *fpTarg;
	fpSour = fopen(SALE_DATA_TEMP_FILE, "rb");
	if (NULL == fpSour) {
		printf("Cannot open file %s!\n", SALE_DATA_FILE);
		return 0;
	}

	fpTarg = fopen(SALE_DATA_FILE, "wb");
	if (NULL == fpTarg) {
		printf("Cannot open file %s!\n", SALE_DATA_TEMP_FILE);
		return 0;
	}


	sale_t buf;

	int found = 0;
	while (!feof(fpSour)) {
		if (fread(&buf, sizeof(sale_t), 1, fpSour)) {
			if (saleID == buf.id) {
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(sale_t), 1, fpTarg);//һ������һ������д�룬������Ҫɾ�������ݾ�����
		}
	}
	fclose(fpTarg);
	fclose(fpSour);
	//ɾ����ʱ�ļ�
	remove(SALE_DATA_TEMP_FILE);
	return found;
}

//�����û�ID�������ʱ�������ڵ����ۼ�¼
int Sale_Perst_SelectByUsrID(sale_list_t list, int usrID, user_date_t stDate, user_date_t endDate)
{
	int recCount = 0, i, j;
	FILE *fp;
	sale_t saleRec;
	sale_list_t newNode;
	fp = fopen(SALE_DATA_FILE, "rb");
	if (fp == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		return 0;
	}
	else
	{
		while (fread(&saleRec, sizeof(sale_t), 1, fp) == 1)
		{
			i = DateCmp(saleRec.date, stDate);
			j = DateCmp(endDate, saleRec.date);
			if (saleRec.user_id == usrID && i != -1 && j != -1)//dt1<dt2 ����-1��=����0��>����1
			{
				newNode = (sale_node_t *)malloc(sizeof(sale_node_t));
				newNode->data.id = saleRec.id;
				newNode->data.user_id = saleRec.user_id;
				newNode->data.ticket_id = saleRec.ticket_id;
				newNode->data.date = saleRec.date;
				newNode->data.time = saleRec.time;
				newNode->data.value = saleRec.value;
				newNode->data.type = saleRec.type;
				List_AddTail(list, newNode);
				recCount++;
				break;
			}
		}
	}
	return recCount;
}

//���ݸ���ʱ�������ڵ����ۼ�¼
int Sale_Perst_SelectByDate(sale_list_t list, user_date_t stDate, user_date_t endDate)
{
	FILE *fp;
	int i, j;
	int recCount = 0;
	fp = fopen(SALE_DATA_FILE, "rb");
	sale_t saleRec;
	sale_list_t newNode;
	if (fp == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
	}
	else
	{
		while (fread(&saleRec, sizeof(sale_t), 1, fp) == 1)
		{
			i = DateCmp(saleRec.date, stDate);    //          1
			j = DateCmp(endDate, saleRec.date);     //   1 
			if (i != -1 && j != -1)
			{
				newNode = (sale_node_t *)malloc(sizeof(sale_node_t));
				newNode->data.id = saleRec.id;
				newNode->data.user_id = saleRec.user_id;
				newNode->data.ticket_id = saleRec.ticket_id;
				newNode->data.date = saleRec.date;
				newNode->data.time = saleRec.time;
				newNode->data.value = saleRec.value;
				newNode->data.type = saleRec.type;
				List_AddTail(list, newNode);
				recCount++;
				break;
			}
		}
	}
	return recCount;
}

//����Ʊ��id���Ʊ��Ʊ�Ļ�����Ϣ
int Select_Price_By_Playid(int id, sale_t *buf)
{

	assert(NULL != buf);

	FILE *fp = fopen(SALE_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}
	sale_t data;
	int found = 0;
	while (!feof(fp)) {
		if (fread(&data, sizeof(sale_t), 1, fp)) {
			if (id == data.ticket_id) {
				*buf = data;
				found = 1;
				break;
			}
		}
	}
	fclose(fp);
	return found;
}
/*
int Sale_Perst_SelectAll(sale_list_t list) {
sale_node_t *newNode;
sale_t data;
int recCount = 0;

assert(NULL != list);

List_Free(list, sale_node_t);

FILE *fp = fopen(SALE_DATA_FILE, "rb");
if (NULL == fp) { //�ļ�������
return 0;
}

while (!feof(fp)) {
if (fread(&data, sizeof(sale_t), 1, fp)) {
newNode = (sale_node_t*)malloc(sizeof(sale_node_t));
if (!newNode) {
printf(
"Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
break;
}
newNode->data = data;
List_AddTail(list, newNode);
recCount++;
}
}
fclose(fp);
return recCount;
}*/
/*
//queryUid = null,query all the uid Sale information return the all uid Sale information number
//queryUid =  uid, query the uid Sale information return the uid Sale  number
*
int  Sale_Infor_By_Uid(char * queryUid, Sale_list_t head)
{
// �벹������
return 1;
}
int Sale_Infor_By_Time(char  queryTime[][30], Sale_list_t head)
{
// �벹������
return 1;
}*/

