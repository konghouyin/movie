#include "Account.h"
#include "EntityKey.h"
#include "../Common/list.h"
#include "../Persistence/Account_Persist.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern account_t gl_CurUser;//����һ��ȫ�ֱ������洢��ǰ��¼���û���Ϣ

//����ϵͳ��ʼ���˺�admin
//��ѯ����Ա�ļ��Ƿ���ڣ���������ھ��½�һ��
void Account_Srv_InitSys() {
	if (Account_Perst_CheckAccFile())
		return;
	printf("ϵͳ��⵽����ʹ��,���ʼ��ϵͳ����Ա����Ϣ��\n");
	account_t data_admin;//����һ����Ա������
	char type[] = "account";
	data_admin.id = EntKey_Srv_CompNewKey(type);//�������Ψһ��Ӧ����
	printf("\t\t\t���������Ա���ƣ�");
	fgets(data_admin.username,29,stdin);//vs 2017��֧��gets(),ʹ��fgets()����
	int l = strlen(data_admin.username);
	data_admin.username[l - 1] = '\0';
	printf("\t\t\t���������Ա���룺");	
	fgets(data_admin.password, 29, stdin);
	l = strlen(data_admin.password);
	data_admin.password[l - 1] = '\0';
	data_admin.type = (account_type_t)9; //ע��Ϊ����Ա�˺ţ���Ϊ�����ʼ�������ʼ��
	if (Account_Srv_Add(&data_admin))//�ļ���ֱ�Ӵ������������Բ���Ҫ��������
	{
		printf("�ɹ���ʼ������Ա!");
	}
	else
	{
		printf("��ʼ��ʧ�ܣ�����ϵ��������̣��Ի�ȡ����֧�֣�");
		exit(EXIT_FAILURE);
	}
}

//��֤��¼�˺��Ƿ��Ѵ��ڣ����ڣ������¼�û���Ϣ��ȫ�ֱ���gl_CurUser��return 1������return 0
int Account_Srv_Verify(char usrName[], char pwd[]) {
	account_t usr;
	account_list_t head;
	List_Init(head, account_node_t);//��������

	Account_Srv_FetchAll(head);
	//��ȡ�����û��˺���Ϣ�����浽list�����У�ͨ������Account_Perst_SelectAll(list)����ʵ��
	/*��Ҫ��ͷָ����Ϊ��������־û��������Ϣ��ȡ*/
	
	Account_Perst_SelByName(usrName, &usr);
	//�����û��������˺�,����ɹ� return 1������ return 0
	//usr��Ϊָ��������룬���Ը���usrΪ���µ�������
	//�ú�������ҪĿ���ǣ�����usr���Ա�������������ѯ
	//���⣺�ļ��Ѿ��������������������н��в�ѯ�������ٴζ�ȡ�ļ��������ļ�Ч��


	if (!Account_Srv_FindByUsrName(head, usrName))
	//��֤�û����Ƿ���ڣ�����list�������ڣ����ض�Ӧ���ָ�룻���򣬷���null
		return 0;
	if (strcmp(usr.password, pwd) == 0) {
		gl_CurUser = usr;
		return 1;
	}
	return 0;
}


//��֤�û����Ƿ���ڣ�����list�������ڣ����ض�Ӧ���ָ�룻���򣬷���null
account_node_t * Account_Srv_FindByUsrName(account_list_t list, char usrName[]) {
	account_node_t  *pos;
	List_ForEach(list, pos)//�������麯��
		if (strcmp(pos->data.username, usrName) == 0)
			return pos;
	return NULL;
}

//���һ���û��˺ţ�ͨ������Account_Perst_Insert(data)����ʵ��
int Account_Srv_Add(const account_t *data) {
	return Account_Perst_Insert(data);
}

//�޸�һ���û��˺ţ�ͨ������Account_Perst_Update(data)����ʵ��
int Account_Srv_Modify(const account_t *data) {
	return Account_Perst_Update(data);
}

//ɾ��һ���û��˺ţ�ͨ������Account_Perst_DeleteByID(usrID)����ʵ��
int Account_Srv_DeleteByID(int usrID) {
	return Account_Perst_DeleteByID(usrID);
}

//��ȡusrID��Ӧ���û��˺���Ϣ��ͨ������Account_Perst_SelectByID(usrID, buf)����ʵ��
int Account_Srv_FetchByID(int usrID, account_t *buf) {
	return Account_Perst_SelectByID(usrID, buf);
}

//��ȡusrName��Ӧ���û��˺���Ϣ��ͨ������Account_Perst_SelByName(usrName, buf)����ʵ��
int Account_Srv_FetchByName(char usrName[], account_t *buf) {
	return Account_Perst_SelByName(usrName, buf);
}

//��ȡ�����û��˺���Ϣ�����浽list�����У�ͨ������Account_Perst_SelectAll(list)����ʵ��
int Account_Srv_FetchAll(account_list_t list) {
	return Account_Perst_SelectAll(list);
}


