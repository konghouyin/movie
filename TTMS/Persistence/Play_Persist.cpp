#include "Play_Persist.h"
#include "../Service/Play.h"
#include "../Common/list.h"
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <process.h>
#include <assert.h>
#include <string.h>

static const char PLAY_DATA_FILE[] = "Play.dat";//�����Ŀ��Ϣ
static const char PLAY_DATA_TEMP_FILE[] = "PlayTmp.dat";//ɾ�������ʱ����ʱ�����Ŀ��Ϣ

														/*
														* Function:    Play_Perst_Insert
														* Function ID:	TTMS_SCU_Play_Perst_Insert
														* Description: �ھ�Ŀ��Ϣ�ļ�ĩβд��һ����Ŀ��Ϣ
														* Input:       �������ļ��ľ�Ŀ��Ϣ����
														* Output:      ���ļ�ʧ�ܵ���Ϣ
														* Return:      д���ļ��ļ�¼��
														*/
int Play_Perst_Insert(const play_t *data) {
	assert(NULL != data);
	FILE *fp = fopen(PLAY_DATA_FILE, "ab");
	int rtn = 0;
	if (NULL == fp) {
		printf("Cannot open file %s!\n", PLAY_DATA_FILE);
		return 0;
	}
	rtn = fwrite(data, sizeof(play_t), 1, fp);//���óɹ�������count��ֵ��������ɹ�������0��
	fclose(fp);
	return rtn;
}

/*
* Function:    Play_Perst_Update
* Function ID:	TTMS_SCU_Play_Perst_Mod
* Description: ���վ�ĿID�Ÿ����ļ��еľ�Ŀ��Ϣ
* Input:       �����ļ��и��µľ�Ŀ��Ϣ����
* Output:      ���ļ�ʧ�ܵ���Ϣ
* Return:      ���µľ�Ŀ��Ϣ����0��ʾδ�ҵ���1��ʾ�ҵ�������
*/
int Play_Perst_Update(const play_t *data) {
	assert(NULL != data);
	FILE *fp = fopen(PLAY_DATA_FILE, "rb+");
	if (NULL == fp) {
		printf("Cannot open file %s!\n", PLAY_DATA_FILE);
		return 0;
	}

	play_t buf;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&buf, sizeof(play_t), 1, fp)) {
			if (buf.id == data->id) {
				fseek(fp, -((int)sizeof(play_t)), SEEK_CUR);
				fwrite(data, sizeof(play_t), 1, fp);
				found = 1;
				break;
			}
		}
	}
	fclose(fp);
	return found;
}

/*
* Function:    Play_Perst_DeleteByID
* Function ID:	TTMS_SCU_Play_Perst_DelByID
* Description: ���վ�ĿID��ɾ����Ŀ����Ϣ
* Input:       ��ɾ���ľ�ĿID��
* Output:      ���ļ�ʧ�ܵ���Ϣ
* Return:      0��ʾɾ��ʧ�ܣ�1��ʾɾ���ɹ�
*/
int Play_Perst_DeleteByID(int ID) {
	//��ԭʼ�ļ���������Ȼ���ȡ��������д�뵽�����ļ��У�����Ҫɾ����ʵ����˵�����������һ���ļ���
	//��ԭʼ�����ļ�������
	if (rename(PLAY_DATA_FILE, PLAY_DATA_TEMP_FILE)<0) {
		printf("Cannot open file %s!\n", PLAY_DATA_FILE);
		return 0;
	}

	FILE *fpSour, *fpTarg;
	fpSour = fopen(PLAY_DATA_TEMP_FILE, "rb");
	if (NULL == fpSour) {
		printf("Cannot open file %s!\n", PLAY_DATA_FILE);
		return 0;
	}

	fpTarg = fopen(PLAY_DATA_FILE, "wb");
	if (NULL == fpTarg) {
		printf("Cannot open file %s!\n", PLAY_DATA_TEMP_FILE);
		return 0;
	}


	play_t buf;

	int found = 0;
	while (!feof(fpSour)) {
		if (fread(&buf, sizeof(play_t), 1, fpSour)) {
			if (ID == buf.id) {
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(play_t), 1, fpTarg);//һ������һ������д�룬������Ҫɾ�������ݾ�����
		}
	}
	fclose(fpTarg);
	fclose(fpSour);
	//ɾ����ʱ�ļ�
	remove(PLAY_DATA_TEMP_FILE);
	return found;
}

/*
* Function:    Play_Perst_SelectByID
* Function ID:	TTMS_SCU_Play_Perst_SelByID
* Description: ���վ�ĿID�Ų��Ҿ�Ŀ����Ϣ
* Input:       �����ҵľ�ĿID�ţ�������ҽ�����ڴ�ĵ�ַ
* Output:      ��
* Return:      0��ʾδ�ҵ���1��ʾ�ҵ���
*/
int Play_Perst_SelectByID(int ID, play_t *buf) {
	assert(NULL != buf);

	FILE *fp = fopen(PLAY_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}
	play_t data;
	int found = 0;
	while (!feof(fp)) {
		if (fread(&data, sizeof(play_t), 1, fp)) {
			if (ID == data.id) {
				*buf = data;
				found = 1;
				break;
			};
		}
	}
	fclose(fp);
	return found;
}



/*
* Function:    Play_Perst_SelectAll
* Function ID:	TTMS_SCU_Play_Perst_SelAll
* Description: �����о�Ŀ��Ϣ������һ������
* Input:       list��Ŀ��Ϣ�����ͷָ��
* Output:      ��ʾ��������ʱ������ռ�ʧ��
* Return:      ���ز��ҵ��ļ�¼��Ŀ
*/
int Play_Perst_SelectAll(play_list_t list) {
	play_node_t *newNode;
	play_t data;
	int recCount = 0;

	assert(NULL != list);

	List_Free(list, play_node_t);

	FILE *fp = fopen(PLAY_DATA_FILE, "rb");
	if (NULL == fp) {                 //�ļ��򲻿�
		return 0;
	}

	while (!feof(fp)) {
		if (fread(&data, sizeof(play_t), 1, fp)) {
			newNode = (play_node_t*)malloc(sizeof(play_node_t));
			if (!newNode) {
				printf("Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
				break;
			}
			newNode->data = data;
			List_AddTail(list, newNode);
			recCount++;
		}
	}
	fclose(fp);
	return recCount;
}



/*
* Function:    Play_Perst_SelectByName
* Function ID:	TTMS_SCU_Play_Perst_SelByName
* Description: ���վ�Ŀ���Ʋ��Ҿ�Ŀ����Ϣ
* Input:       listΪ���ҵ��ľ�Ŀ��Ϣ����condtΪģ����ѯ�Ĺؼ���
* Output:      ��ʾ��������ʱ������ռ�ʧ��
* Return:      ���ز��ҵ��ļ�¼��Ŀ
*/
int Play_Perst_SelectByName(play_list_t list, char condt[]) {
	assert(NULL != condt);

	FILE *fp = fopen(PLAY_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	List_Free(list, play_node_t);
	play_t data;
	int recCount = 0;
	play_node_t *newNode;

	while (!feof(fp)) {
		if (fread(&data, sizeof(play_t), 1, fp)) {
			newNode = (play_node_t*)malloc(sizeof(play_node_t));
			if (!newNode) {
				printf("Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
				break;
			}
			if (strstr(data.name, condt))
			{
				newNode->data = data;
				List_AddTail(list, newNode);
				recCount++;
			}
		}
	}
	fclose(fp);
	return recCount;
}


play_t Play_Perst_SelectByName1(play_list_t list, char condt[])
{
	assert(NULL != condt);
	play_t data;
	data.id = 0;
	FILE *fp = fopen(PLAY_DATA_FILE, "rb");
	if (NULL == fp) {
		return data;
	}

	List_Free(list, play_node_t);
	int recCount = 0;
	play_node_t *newNode;

	while (!feof(fp)) {
		if (fread(&data, sizeof(play_t), 1, fp)) {
			if (strcmp(data.name, condt)==0)
			{
				fclose(fp);
				return data;
			}
		}
	}
	fclose(fp);
	return data;
}