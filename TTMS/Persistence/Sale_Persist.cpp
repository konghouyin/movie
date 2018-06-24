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
	rtn = fwrite(data, sizeof(sale_t), 1, fp);//调用成功，返回count的值，如果不成功，返回0；
	fclose(fp);
	return rtn;
}

int Sale_Perst_DeleteByID(int saleID) {
	//将原始文件重命名，然后读取数据重新写入到数据文件中，并将要删除的实体过滤掉。（借用另一个文件）
	//对原始数据文件重命名
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
			fwrite(&buf, sizeof(sale_t), 1, fpTarg);//一个数据一个数据写入，当遇到要删除的数据就跳过
		}
	}
	fclose(fpTarg);
	fclose(fpSour);
	//删除临时文件
	remove(SALE_DATA_TEMP_FILE);
	return found;
}

//根据用户ID载入给定时间区间内的销售记录
int Sale_Perst_SelectByUsrID(sale_list_t list, int usrID, user_date_t stDate, user_date_t endDate)
{
	int recCount = 0, i, j;
	FILE *fp;
	sale_t saleRec;
	sale_list_t newNode;
	fp = fopen(SALE_DATA_FILE, "rb");
	if (fp == NULL)
	{
		printf("文件打开失败！\n");
		return 0;
	}
	else
	{
		while (fread(&saleRec, sizeof(sale_t), 1, fp) == 1)
		{
			i = DateCmp(saleRec.date, stDate);
			j = DateCmp(endDate, saleRec.date);
			if (saleRec.user_id == usrID && i != -1 && j != -1)//dt1<dt2 返回-1，=返回0，>返回1
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

//根据给定时间区间内的销售记录
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
		printf("文件打开失败！\n");
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

//根据票的id获得票售票的基本信息
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
if (NULL == fp) { //文件不存在
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
// 请补充完整
return 1;
}
int Sale_Infor_By_Time(char  queryTime[][30], Sale_list_t head)
{
// 请补充完整
return 1;
}*/

