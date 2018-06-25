#include "Account_UI.h"
#include "../Common/list.h"
#include "../Service/Account.h"
#include "../Service/EntityKey.h"
#include "Account_UI.h"
#include "../Common/window.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <io.h>
#include <process.h>
#include <time.h>  
#include <conio.h>
#include<Windows.h>

extern account_t gl_CurUser;

char *usr_type(int i)
{
	static char back[15];
	switch (i)
	{
	case 1:
		strcpy(back, "cherk");
		break;

	case 2:
		strcpy(back, "manager");
		break;

	case 9:
		strcpy(back,"administrator" );
		break;

	case 0:
		strcpy(back, "others");
		break;
	}
	return back;
}
//��������ļ���
//�÷�������Ҫ����ֵ���ַ�������Ϊ�������뺯��
//������δ���ַ����鳤��������
//����ֵ��������ַ�������������'\0'��
int GetPassword(char password[])
{
	char ch;
	int i = 0;
	while ((ch = getch()) != '\r')
	{
		if (ch < 0)
		{
			getch();
			continue;
		}
		if (ch == '\t' || ch == 32)
		{
			continue;
		}
		else if (ch == 8 && i > 0)
		{
			printf("\b \b");
			i--;
			continue;
		}
		else if (ch != 8 && i < 10)
		{
			printf("*");
			password[i] = ch;
			i++;
		}
	}
	password[i] = '\0';
	return i;
}


#define TRY_TIME 4
//��¼��������ʾ�û������û��������룬��¼�ɹ�return 1��������ʾ���µ�¼������3�Σ���¼ʧ��
int SysLogin() {


	Account_Srv_InitSys();
	char usrname[20];
	char passwd[20];
	int i = 0, j;
	system("cls");
	kuangjia();
	goto_xy(30, 6);
	printf("       ------->>            ���¼           <<------\n");
	goto_xy(30, 7);
	printf("==============================================================\n");
	for (i = 1; i <= TRY_TIME; i++) {
		printf("\t\t\t\t******** ����������û���: ");
		while (_kbhit())
		{
			getch();
		}
		fgets(usrname, 19, stdin);
		int l = strlen(usrname);
		usrname[l - 1] = '\0';
		printf("\t\t\t\t******** �������������: ");
		GetPassword(passwd);
		printf("\n\t\t\t\t==========================================================\n");

		//��֤��¼�˺��Ƿ��Ѵ��ڣ����ڣ������¼�û���Ϣ��ȫ�ֱ���gl_CurUser��return 1������return 0
		if (Account_Srv_Verify(usrname, passwd))
		{
			printf("\t\t\t\t\t    ");
			for (j = 0; j < 11; j++)
			{
				Sleep(100);
				printf("=> ");
			}
			printf("\n");
			return 1;
		}
		else if(i == TRY_TIME)
		{
			return 0;
		}
		else
		{
			printf("\t\t\t\t\t    ");
			for (j = 0; j < 11; j++)
			{
				Sleep(100);
				printf("=> ");
			}
			printf("\n");
			for (int o = i*10-5; o >=0; o--)
			{
				goto_xy(0, 13);
				printf("\t\t\t\t�����֤����!!!   ����%d�λ���   ��%d�������----��ʣ%d��\n", 4 - i, i * 10 - 5, o);
				Sleep(1000);
			}			
			goto_xy(0, 8);
			printf("\t\t\t                                                                                            \n");
			printf("\t\t\t                                                                                            \n");
			printf("\t\t\t                                                                                            \n");
			printf("\t\t\t                                                                                            \n");
			printf("\t\t\t                                                                                            \n");
			printf("\t\t\t                                                                                            \n");
			goto_xy(0, 8);
		}
	}
}
//����ϵͳ�û�������ں�������ʾ�û��˺Ź���˵�

void Account_UI_MgtEntry() {
	int i;
	char choice;
	account_t usr;

	account_list_t head;
	account_node_t *pos;
	Pagination_t paging;

	List_Init(head, account_node_t);
	paging.offset = 0;
	paging.pageSize = ACCOUNT_PAGE_SIZE;

	//��������
	paging.totalRecords = Account_Srv_FetchAll(head);//��ѯ�ļ��е�¼��Ϣ�ĸ���������������
	Paging_Locate_FirstPage(head, paging);//��ҳ����ʼ������һҳ
	if (gl_CurUser.type == 9)
	{
		do {
			system("cls");
			kuangjia();
			goto_xy(0, 5);
			printf("\n\t\t\t    ==================================================================\n");
			printf("\t\t\t        ********************* �û��������  *********************\n");
			printf("\t\t\t        %-9s  %-12s  %-12s  %-12s   \n", "ID", "�û�����", "�û���", "����");
			printf("\t\t\t    ------------------------------------------------------------------\n");
			//��ʾ����
			for (i = 0, pos = (account_node_t *)(paging.curPos);
				pos != head && i < paging.pageSize; i++) {
				printf("\t\t\t        %-5d  %-16s  %-12s  %-12s  \n\n", pos->data.id, usr_type(pos->data.type), pos->data.username, "********");
				pos = pos->next;
			}
			goto_xy(0, 21);
			printf("\t\t\t\t ----- �ܸ���:%2d ----------------------- ҳ�� %2d/%2d ----\n\n",
				paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));
			printf("\t\t\t    ******************************************************************\n");
			printf("\t\t\t       [P]��һҳ|[N]��һҳ|[A]���|[D]ɾ��|[M]�޸�|[Q]��ѯ|[R]����");
			printf("\n\t\t\t    ==================================================================\n");
			printf("\t\t\t\t    ���ѡ��:");
			while (_kbhit())
			{
				getch();
			}
			choice = getche();
			//getchar();
			while (_kbhit()){getch();}
			int l;
			switch (choice) {
			case 'a':
			case 'A':
				if (Account_UI_Add(head)) //����ӳɹ����������һҳ��ʾ
				{
					paging.totalRecords = Account_Srv_FetchAll(head);
					Paging_Locate_LastPage(head, paging, account_node_t);
				}
				break;
			case 'd':
			case 'D':
				//getchar();
				printf("\t\t\t�����û���:");
			
				fgets(usr.username, 29, stdin);
				l = strlen(usr.username);
				usr.username[l - 1] = '\0';

				if (Account_UI_Delete(head, usr.username)) {	//������������
					paging.totalRecords = Account_Srv_FetchAll(head);
					List_Paging(head, paging, account_node_t);
				}
				break;
			case 'm':
			case 'M':
				//getchar();
				printf("\t\t\t�����û���:");
				fgets(usr.username, 29, stdin);
				l = strlen(usr.username);
				usr.username[l - 1] = '\0';
				if (Account_UI_Modify(head, usr.username)) {	//������������
					paging.totalRecords = Account_Srv_FetchAll(head);
					List_Paging(head, paging, account_node_t);
				}
				break;
			case 'q':
			case 'Q':
				//getchar();
				printf("\t\t\t�����û���:");
				fgets(usr.username, 29, stdin);
				l = strlen(usr.username);
				usr.username[l - 1] = '\0';
				if (Account_UI_Query(head, usr.username)) {
					//������������
					paging.totalRecords = Account_Srv_FetchAll(head);
					List_Paging(head, paging, account_node_t);
				}
			case 'p':
			case 'P':
				if (1 < Pageing_CurPage(paging)) {
					Paging_Locate_OffsetPage(head, paging, -1, account_node_t);
				}
				break;
			case 'n':
			case 'N':
				if (Pageing_TotalPages(paging) > Pageing_CurPage(paging)) {
					Paging_Locate_OffsetPage(head, paging, 1, account_node_t);
				}
				break;
			}
		} while (choice != 'r' && choice != 'R');
	}
	else
	{
		do {
			system("cls");
			kuangjia();
			goto_xy(30, 6);
			printf("                 ---->>    �޸��Լ�����Ϣ    <<----\n");
			printf("\n\t\t\t\t==================================================================\n");
			printf("\t\t\t\t           %-9s  %-12s  %-12s  %-12s   \n", "ID", "����", "�û���", "����");
			printf("\t\t\t\t     --------------------------------------------------------     \n\n");
			printf("\t\t\t\t           %-5d  %-16s  %-12s  %-12s  \n\n", gl_CurUser.id, usr_type(gl_CurUser.type), gl_CurUser.username, gl_CurUser.password);
			printf("\t\t\t\t     --------------------------------------------------------\n");
			printf("\t\t\t\t                    [M]�޸�\t\t[R]����");
			printf("\n\t\t\t\t==================================================================\n");
			printf("\t\t\t\t    ��ѡ��:");
			while (_kbhit()){getch();}
			choice = getche();
			//getchar();
			while (_kbhit()){getch();}
			switch (choice)
			{
			case 'm':
			case 'M':
				//getchar();
				strcpy(usr.username, gl_CurUser.username);
				if (Account_UI_Modify_other(head, usr.username))//������������
				{	
					paging.totalRecords = Account_Srv_FetchAll(head);
					List_Paging(head, paging, account_node_t);
				}
				break;
			}
		} while (choice != 'r' && choice != 'R');

	}
	//getchar();
	//�ͷ�����ռ�
	List_Destroy(head, account_node_t);
}




//���һ���û��˺���Ϣ������˺������ڣ���ʾ������Ϣ
int Account_UI_Add(account_list_t list) {
	account_t usr;
	int newUsrCount = 0;
	char choice;
	char passwd[20];
	int l;
	List_Init(list, account_node_t);
	Account_Srv_FetchAll(list);
	do
	{
		system("cls");
		kuangjia();
		goto_xy(0, 5);
		printf("\n\t\t\t\t    =======================================================\n");
		printf("\t\t\t\t       ****************  ���һ�����û�  ****************\n");
		printf("\t\t\t\t    -------------------------------------------------------\n");
		printf("\n\t\t\t\t\t�������µ��û���:");
		fgets(usr.username, 29, stdin);
		int l = strlen(usr.username);
		usr.username[l - 1] = '\0';
		printf("\n\t\t\t\t\t�������µ�����:");
		GetPassword(usr.password);
		l = strlen(usr.password);
		while (l < 6)
		{
			printf("\n\t\t\t\t\t���벻��6λ,����������!\n");
			printf("\n\t\t\t\t\t�������µ�����:");
			GetPassword(usr.password);
			l = strlen(usr.password);
		}
		printf("\n\t\t\t\t\t���ٴ��������������:");
		GetPassword(passwd);
		while (strcmp(usr.password, passwd) != 0)
		{
			printf("\n\t\t\t\t\t�������벻һ�£����������룡\n");
			printf("\n\t\t\t\t\t�������µ�����:");
			GetPassword(usr.password);
			l = strlen(usr.password);
			while (l < 6)
			{
				printf("\n\t\t\t\t\t���벻��6λ,����������!\n");
				printf("\n\t\t\t\t\t�������µ�����:");
				GetPassword(usr.password);
				l = strlen(usr.password);
			}
			printf("\n\t\t\t\t\t���ٴ��������������:");
			GetPassword(passwd);
		}
		printf("\n\n\t\t\t\t\t�������û�����:��0������1��ƱԱ��2����9����Ա��");
		scanf("%d", &usr.type);
		getchar();
		printf("\n\t\t\t\t    -------------------------------------------------------\n");
		if (NULL != Account_Srv_FindByUsrName(list, usr.username))
		{
			printf("\n\t\t\t\t\t���û��Ѿ�����!!!");
			printf("\t\t�� [Enter] ���˳�!!!");
			getchar();
			return 0;
		}
		else {
			//��ȡ����
			char type[] = "Account";
			usr.id = EntKey_Srv_CompNewKey(type);

			if (Account_Srv_Add(&usr))
			{
				newUsrCount += 1;
				printf("\t\t\t\t\t    ���û���ӳɹ�!");
			}
			else
				printf("\t\t\t\t\t    ���û����ʧ��!");
		}
		printf("\t    [A]�������   [R]����");
		choice = getche();
		//getchar();
	} while ('a' == choice || 'A' == choice);
	return newUsrCount;
}

//�����û��˺����޸��û��˺����룬����������û��˺�������ʾ������Ϣ
int Account_UI_Modify(account_list_t list, char usrName[])
{
	account_t usr;
	int rtn = 0;
	int l;
	char passwd[20];
	if (!Account_Srv_FindByUsrName(list, usrName))
	{
		for (int i = 3; i >= 0; i--)
		{
			goto_xy(0, 28);
			printf("\n\t\t\t\t    ����û�������!             %d��󷵻�", i);
			Sleep(1000);
		}
		return 0;
	}
	Account_Srv_FetchByName(usrName, &usr);
	system("cls");
	kuangjia();
	goto_xy(0, 5);
	printf("\n\t\t\t\t    =======================================================\n");
	printf("\t\t\t\t         ****************  �޸���Ϣ  ****************\n");
	printf("\t\t\t\t    -------------------------------------------------------\n");
	printf("\n\t\t\t\t\t�������µ��û���:");
	fgets(usr.username, 29, stdin);
	l = strlen(usr.username);
	usr.username[l - 1] = '\0';

	printf("\n\t\t\t\t\t�������µ�����:");
	GetPassword(usr.password);
	l = strlen(usr.password);
	while (l < 6)
	{
		printf("\n\t\t\t\t\t���벻��6λ,����������!\n");
		printf("\n\t\t\t\t\t�������µ�����:");
		GetPassword(usr.password);
		l = strlen(usr.password);
	}
	printf("\n\t\t\t\t\t���ٴ��������������:");
	GetPassword(passwd);
	while (strcmp(usr.password, passwd) != 0)
	{
		printf("\n\t\t\t\t\t�������벻һ�£����������룡\n");
		printf("\n\t\t\t\t\t�������µ�����:");
		GetPassword(usr.password);
		l = strlen(usr.password);
		while (l < 6)
		{
			printf("\n\t\t\t\t\t���벻��6λ,����������!\n");
			printf("\n\t\t\t\t\t�������µ�����:");
			GetPassword(usr.password);
			l = strlen(usr.password);
		}
		printf("\n\t\t\t\t\t���ٴ��������������:");
		GetPassword(passwd);
	}
	printf("\n\n\t\t\t\t\t�������û�����:��0������1��ƱԱ��2����9����Ա��");
	scanf("%d", &usr.type);
	getchar();
	printf("\n\t\t\t\t    =======================================================\n");
	if (Account_Srv_Modify(&usr)) {
		rtn = 1;
		printf("\n\t\t\t\t\t����û���Ϣ���³ɹ�!\t\t�� [Enter] ������\n\t\t\t");
	}
	else
		printf("\n\t\t\t\t\t����û���Ϣ����ʧ��!\t\t�� [Enter] ������\n\t\t\t");
	getchar();
	return rtn;
}


//�����û��˺����޸��û��˺����룬����������û��˺�������ʾ������Ϣ
int Account_UI_Modify_other(account_list_t list, char usrName[])
{
	account_t usr;
	int rtn = 0;
	int l;
	char passwd[20];
	system("cls");
	kuangjia();
	if (!Account_Srv_FindByUsrName(list, usrName))
	{
		printf("������������û��������������룡");
		Sleep(2000);
		return 0;
	}
	Account_Srv_FetchByName(usrName, &usr);
	goto_xy(30, 6);
	printf("                   ---->>    �޸��û���Ϣ    <<----\n");
	printf("\n\t\t\t\t==================================================================\n");
	printf("\n\t\t\t\t\t\t�������µ��û���:");
	fgets(usr.username, 29, stdin);
	l = strlen(usr.username);
	usr.username[l - 1] = '\0';

	printf("\n\t\t\t\t\t\t�������µ�����:");
	GetPassword(usr.password);
	l = strlen(usr.password);
	while (l < 6)
	{
		printf("\n\t\t\t\t\t\t���벻��6λ,����������!\n");
		printf("\n\t\t\t\t\t\t�������µ�����:");
		GetPassword(usr.password);
		l = strlen(usr.password);
	}
	printf("\n\t\t\t\t\t\t���ٴ��������������:");
	GetPassword(passwd);
	while (strcmp(usr.password, passwd) != 0)
	{
		printf("\n\t\t\t\t\t\t�������벻һ�£����������룡\n");
		printf("\n\t\t\t\t\t\t�������µ�����:");
		GetPassword(usr.password);
		l = strlen(usr.password);
		while (l < 6)
		{
			printf("\n\t\t\t\t\t\t���벻��6λ,����������!\n");
			printf("\n\t\t\t\t\t\t�������µ�����:");
			GetPassword(usr.password);
			l = strlen(usr.password);
		}
		printf("\n\t\t\t\t\t\t���ٴ��������������:");
		GetPassword(passwd);
	}
	printf("\n\t\t\t\t==================================================================\n");
	if (Account_Srv_Modify(&usr)) {
		rtn = 1;
		printf("\n\t\t\t\t   �û���Ϣ���³ɹ�!\t\t\t�� [Enter] ������\n\t\t\t");
		gl_CurUser = usr;
	}
	else
		printf("\t\t\t\t    �û���Ϣ����ʧ��!\n\t\t\t�� [Enter] ������\n\t\t\t");
	getchar();
	return rtn;
}


//�����û��˺���ɾ��һ���Ѿ����ڵ��û��˺���Ϣ���������������û��˺�������ʾ������Ϣ
int Account_UI_Delete(account_list_t list, char usrName[]) {
	account_t usr;
	int rtn = 0;

	if (!Account_Srv_FindByUsrName(list, usrName))
	{
		for (int i = 3; i >= 0; i--)
		{
			goto_xy(0, 28);
			printf("\n\t\t\t\t    ����û�������!               %d��󷵻�",i);
			Sleep(1000);
		}
		return 0;
	}
	Account_Srv_FetchByName(usrName, &usr);
	if (Account_Srv_DeleteByID(usr.id))
	{
		rtn = 1;
		printf("\t\t\t\t    �û���Ϣɾ���ɹ�!\t\t�� [Enter] ������\n\t\t\t");
	}
	else
		printf("\t\t\t\t    �û���Ϣɾ��ʧ��!\t\t�� [Enter] ������\n\t\t\t");
	getchar();
	return rtn;

}



//�����û��˺������Ҹ��û��˺��Ƿ���ڣ����ڷ���1�����򷵻�0������ʾ������Ϣ
int Account_UI_Query(account_list_t  list, char usrName[]) {
	account_t usr;

	if (!Account_Srv_FindByUsrName(list, usrName))
	{
		for (int i = 3; i >= 0; i--)
		{
			goto_xy(0, 28);
			printf("\n\t\t\t\t    ����û�������!             %d��󷵻�", i);
			Sleep(1000);
		}
		return 0;
	}
	Account_Srv_FetchByName(usrName, &usr);
	system("cls");
	kuangjia();
	goto_xy(0, 5);
	printf("\n\t\t\t\t    =======================================================\n");
	printf("\t\t\t\t         ****************  �û���Ϣ  ****************\n");
	printf("\t\t\t\t    -------------------------------------------------------\n");
	printf("\n\t\t\t\t\t�û�ID: %d\n", usr.id);
	printf("\n\t\t\t\t\t�û�����:  %s\n", usr_type(usr.type));
	printf("\n\t\t\t\t\t�û�����: ");
	puts(usr.username);
	printf("\n\t\t\t\t\t�û�����: ");
	puts(usr.password);
	printf("\n\t\t\t\t    =======================================================\n");
	printf("\t\t\t\t\t\t    �� [Enter] ������\n\t\t\t");
	getchar();
	return 1;
}






