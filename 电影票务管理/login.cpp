#include"include.h"




char* u_encryption(char* p);//���ܺ���

void list_log_in(void);//��¼�������
void goto_xy(int x, int y);//�����ת
Node* out_n(void);//����Ա��Ϣ
int chongfu(char *name);//�û�������
char* input_add_back(void);//�û��������¼
char* input_pass_back(void);//���������ȡ

void gly_(void);//����Ա����



int pass_true(char *name,char *pass)
{
	FILE *midn;
	midn = fopen("midn.txt", "r");
	if (midn == NULL)
	{
		goto_xy(10, 28);
		fprintf(stdout, "ϵͳ�ļ����𻵣�����ϵ����Ա��");
		Sleep(5000);
		exit(EXIT_FAILURE);
	}
	else
	{
		Node_p *mid;
		mid = (Node_p*)malloc(sizeof(Node_p));
		while (fread(mid, sizeof(Node_p), 1, midn) != 0)
		{
			if ((strcmp(mid->name, name)) == 0)
			{
				if (strcmp((u_encryption(mid->password)), pass) == 0)
				{
					fclose(midn);
					free(mid);
					return 1;
				}
			}
		}
		fclose(midn);
		return 0;
	}
}
//ȷ��������ȷ��

static int i = 0;

void log(void)
{
	
	list_log_in();
	char name[12];
	char pass[18];

lkj:if (i > 4)
	{

		goto_xy(47, 17);
		printf("        Wrong!    ");
		goto_xy(43, 21);
		printf("����������࣬������5����Զ��˳���");
		printf("\n\n\t\t\t\t�����������룬����ϵ����Ա����������̣��Ի�ȡ����֧�֣�");
		goto_xy(10, 28);
		printf("���棺�������������                                          \a");
		Sleep(5000);
		exit(EXIT_FAILURE);
	}

	goto_xy(47, 13);
	strcpy(name, input_add_back());
	if (strcmp(name, "!#%&(") == 0)
		return ;
	/////////////////////////////////////////////////////��ȡ�ַ�

	Node *gly = out_n();//��ȡ����Ա��Ϣ

	if (strcmp(name,gly->name)==0)
	{
		goto_xy(47, 17);
		strcpy(pass, input_pass_back());
		i++;
		if (strcmp(pass, "!#%&(") == 0)
			return;
///////////////////////////////////////////////////////////��ȡ����
		if (strcmp(pass, gly->password) == 0)
		{
			i = 0;
			gly_();
		}
		else
		{
			goto_xy(47, 17);
			printf("\a�������      ");
			goto_xy(10, 28);
			printf("���棺���������3����������룡                               ");
			if (i == 5)
			{
				goto lkj;
			}
			Sleep(3000);
			goto_xy(10, 28);
			printf("���棺����������������룡      �㻹��%d�λ���                ", 5 - i);
			goto_xy(47, 17);
			printf("                  ");
			goto_xy(47, 13);
			printf("                  ");
			goto lkj;
		}
	}
	else
	{
		int flag_name;
		flag_name = chongfu(name);
		while (flag_name == 1)
		{
			goto_xy(47, 13);
			printf("\aû�и��û���    ");
			goto_xy(10, 28);
			printf("���棺û�и��û������������룡                       ");
			Sleep(2000);
			goto_xy(47, 13);
			printf("                  ");
			goto lkj;
		}
		/////////////////////////////////////////////////�û�����ȷ��
		goto_xy(10, 28);
		printf("                                                                                ");
		goto_xy(47, 17);
		strcpy(pass, input_pass_back());
		i++;
		if (strcmp(pass, "!#%&(") == 0)
			return;
		///////////////////////////////////////////////////��ȡ����

		int flag_pass;
		flag_pass = pass_true(name, pass);
		while(flag_pass == 0)
		{
			goto_xy(47, 17);
			printf("\a�������      ");
			goto_xy(10, 28);
			printf("���棺���������3����������룡                                ");
			if (i == 5)
			{
				goto lkj;
			}
			Sleep(3000);
			goto_xy(10, 28);
			printf("���棺����������������룡      �㻹��%d�λ���                ", 5 - i);
			goto_xy(47, 17);
			printf("                  ");
			goto_xy(47, 13);
			printf("                  ");
			goto lkj;
		}

		//////////////////////////////////////////////////������ȷ
		i = 0;
		printf("ok");//////////////////////////////////////////////////////�滻����

	}

	return ;
}
//��¼����