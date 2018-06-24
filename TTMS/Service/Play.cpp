#include "Play.h"
#include "../Common/list.h"
#include "../Persistence/Play_Persist.h"
#include <string.h>

/*
* Function:    Play_Srv_Add
* Function ID:	TTMS_SCU_Play_Srv_Add
* Description: ���һ����Ŀ��Ϣ
* Input:       ����ӵľ�Ŀ��Ϣ����
* Output:      ��
* Return:      ��ӵļ�¼��
*/
int Play_Srv_Add(const play_t *data) {
	return Play_Perst_Insert(data);
}

/*
* Function:    Play_Srv_Modify
* Function ID:	TTMS_SCU_Play_ Srv _Mod
* Description: ����һ����Ŀ��Ϣ
* Input:       �����µľ�Ŀ��Ϣ����
* Output:      ��
* Return:      ���µľ�Ŀ��Ϣ����0��ʾδ�ҵ���1��ʾ�ҵ�������
*/
int Play_Srv_Modify(const play_t *data) {
	return Play_Perst_Update(data);
}

/*
* Function:    Play_Srv_DeleteByID
* Function ID:	TTMS_SCU_Play_Srv_DelByID
* Description: ����ID��ɾ����Ŀ��Ϣ
* Input:       ��ɾ���ľ�ĿID��
* Output:      ��
* Return:      0��ʾɾ��ʧ�ܣ�1��ʾɾ���ɹ�
*/
int Play_Srv_DeleteByID(int ID) {
	return Play_Perst_DeleteByID(ID);
}

/*
* Function:    Play_Srv_FetchByID
* Function ID:	TTMS_SCU_Play_Srv_FetchByID
* Description: ����ID�Ų���һ����Ŀ��Ϣ������buf��ָ��Ԫ
* Input:       �����ҵľ�ĿID�ţ������ҵ�����Ϣ���浽buf��
* Output:      ��
* Return:      0��ʾδ�ҵ���1��ʾ�ҵ���
*/
int Play_Srv_FetchByID(int ID, play_t *buf) {
	return  Play_Perst_SelectByID(ID, buf);
}

/*
* Function:    Play_Srv_FetchAll
* Function ID:	TTMS_SCU_Play_Srv_FetchAll
* Description: �����о�Ŀ��Ϣ������һ������
* Input:       list��Ŀ��Ϣ�����ͷָ��
* Output:      ��
* Return:      ���ز��ҵ��ļ�¼��Ŀ
*/
int Play_Srv_FetchAll(play_list_t list) {
	return Play_Perst_SelectAll(list);
}

/*
* Function:    Play_Srv_FetchByName
* Function ID:	TTMS_SCU_Play_Srv_FetchByName
* Description: ���ݾ�Ŀ���Ʋ��Ҿ�Ŀ����������ľ�Ŀ����
* Input:       listΪ���ҵ��ľ�Ŀ��Ϣ�����ͷָ�룬condtΪģ����ѯ�Ĺؼ���
* Output:      ��
* Return:      ���ز��ҵ��ļ�¼��Ŀ
*/
int Play_Srv_FetchByName(play_list_t list, char condt[]) {
	return  Play_Perst_SelectByName(list, condt);
}

play_t Play_Srv_FetchByName1(play_list_t list, char condt[])
{
	return  Play_Perst_SelectByName1(list, condt);
}


/*
* Function:    Play_Srv_FilterByName
* Function ID:	TTMS_SCU_Play_Srv_FilterByName
* Description: ���ݾ�Ŀ���Ʋ��Ҿ�Ŀ����������ľ�Ŀ����
* Input:       listΪ���ҵ��ľ�Ŀ��Ϣ�����ͷָ�룬filterΪ���˴�
* Output:      ��
* Return:      ���ز��ҵ��ļ�¼��Ŀ
*/
int Play_Srv_FilterByName(play_list_t list, char filter[]) {
	assert(NULL != list);
	play_node_t *ptr = list->next;
	while (ptr != list) {
		if (strcmp(ptr->data.name, filter) == 0)
			return 1;
		else
			ptr = ptr->next;
	}
	return 0;
}


