#include "../Persistence/Sale_Persist.h"
#include "../Persistence/Query_Persist.h"


//����Ʊ����Ϣ���뵽��������Ϣ
int Sale_Srv_Add(const sale_t *data) {
	return Sale_Perst_Insert(data);
}

//ɾ����������Ϣ
int Sale_Srv_DeleteByID(int saleID) {
	return Sale_Perst_DeleteByID(saleID);
}


//ͨ��uid��ѯ����
//int Sale_Srv_SelectByUid(char *queryuid, sale_list_t head) {
//return Sale_Infor_By_Uid(queryuid, head);
//}
//����ʱ���ѯ����
//int Sale_Srv_selectByTime(char querytime[][30], sale_list_t head) {
//return Sale_Infor_By_Time(querytime, head);
//}

