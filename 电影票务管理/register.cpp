#include"include.h"



void kuangjia(void);//���
char* encryption(char*);//���ܺ���
char* u_encryption(char* p);//���ܺ���
void goto_xy(int x, int y);//�����ת

int list_reg_choose(void);//��֪�û�������棬��ȷ��
void reg_really(void);//��ʼע��
void list_reg_in(void);//��ʼע��  ��ӡ��������б�
char* input_add_back(void);//�ַ����Ļ�ȡ
char* input_pass_back(void);//����Ļ�ȡ
void list_reg_end(void);//���������ȷ��
int choose_ayn(void);//��ȡ �ǻ����Ǻ�
void list_reg_pass(void);//��ӡ�������Ա�����֪ͨ
void save_time(void);//���滺��
void right(void);//ע��ɹ�
void wrong(void);//ע��ʧ��


void reg(void)
{
	int flag_reg_choose;
	flag_reg_choose =list_reg_choose();
	switch (flag_reg_choose)
	{
	case 0: return;
	case 1:Sleep(200); reg_really();
	}
	return;
}
//ע����Ϣ

int chongfu(char *name)
{
	Node *top;
	top = (Node*)malloc(sizeof(Node));

	FILE *topn;
	topn = fopen("topn.txt", "r");
	if (NULL == topn)
	{
		printf("\n\n\n\n\n\n\t\t\t����Ա�ļ����ƻ�\a������ϵ��������̣��Ի�ȡ����֧�֣�\n");
		Sleep(5000);
		exit(EXIT_FAILURE);
	}
	getc(topn);
	if (feof(topn))
	{
		printf("\n\n\n\n\n\n\t\t\t����Ա�ļ����ƻ�\a������ϵ��������̣��Ի�ȡ����֧�֣�\n");
		Sleep(5000);
		exit(EXIT_FAILURE);
	}
	rewind(topn);
	fread(top, sizeof(Node), 1, topn);
	if ((strcmp(top->name, name)) == 0)
	{
		free(top);
		return 0;
	}
	

	FILE *midn;
	midn = fopen("midn.txt", "r");
	if (midn == NULL)
	{
		fprintf(stdout, "\n\t\t\tϵͳ�ļ����𻵣�����ϵ����Ա��\a\n");
		Sleep(5000);
		exit(EXIT_FAILURE);
	}
	getc(midn);
	if (feof(midn) != 0)
	{
		fclose(midn);
		return 1;
	}
	else
	{
		rewind(midn);
		Node_p *mid;
		mid = (Node_p*)malloc(sizeof(Node_p));
		while (fread(mid, sizeof(Node_p), 1, midn) != 0)
		{
			if ((strcmp(mid->name, name)) == 0)
			{
				free(mid);
				return 0;
			}
		}
		fclose(midn);
		free(mid);
		return 1;
	}
}
//�û�������

int pass_long(char* pass)
{
	int l = strlen(pass);
	if (l <= 16 && l >= 8)
		return 1;
	else
		return 0;
}
//���볤�ȿ���

Node* out_n(void)
{
	Node *top;
	top = (Node*)malloc(sizeof(Node));

	FILE *topn;
	topn = fopen("topn.txt", "r");
	if (NULL == topn)
	{
		printf("\n\n\n\n\n\n\t\t\t����Ա�����ļ����ƻ�\a������ϵ��������̣��Ի�ȡ����֧�֣����ù���Ա���룡\n");
		Sleep(5000);
		exit(EXIT_FAILURE);
	}
	getc(topn);
	if (feof(topn))
	{
		printf("\n\n\n\n\n\n\t\t\t����Ա�����ļ����ƻ�\a������ϵ��������̣��Ի�ȡ����֧�֣����ù���Ա���룡\n");
		Sleep(5000);
		exit(EXIT_FAILURE);
	}
	rewind(topn);
	fread(top, sizeof(Node), 1, topn);
	strcpy(top->password, u_encryption(top->password));
	fclose(topn);

	return top;
}
//����Ա�����

void save(Node_p* mid)
{
	FILE *midn;
	midn = fopen("midn.txt", "a");
	if (midn == NULL)
	{
		clrscr();
		kuangjia();
		goto_xy(56, 13);
		printf("Wrong!");
		goto_xy(43, 16);
		fprintf(stdout, "ϵͳ�ļ����𻵣�����ϵ����Ա��\a");
		Sleep(5000);
		exit(EXIT_FAILURE);
	}
	else
	{
		save_time();
		if (fwrite(mid, sizeof(Node_p), 1, midn) == 1)
		{
			fflush(midn);
			right();
			Sleep(3000);
			return;
		}
		else
		{
			wrong();
			Sleep(3000);
			return;
		}
	}
}
//ע����Ϣ����


void reg_really(void)
{
	int flag_name_again;
	int flag_pass_long;
	char name[12];
	char pass1[18],pass2[18];
	
	gbko:list_reg_in();

	gbkd:goto_xy(47, 12);
	strcpy(name, input_add_back());
	if (strcmp(name, "!#%&(") == 0)
		return;
	goto_xy(10, 28);
	printf("                                                  ");
	while (name[0] == '\0')
	{
		goto_xy(47, 12);
		printf("\a�˺�Ϊ�գ�");
		goto_xy(10, 28);
		printf("���棺�˺�Ϊ�գ����������룡                       ");
		Sleep(2000);
		goto_xy(47, 12);
		printf("             ");
		goto gbkd;
	}

	flag_name_again = chongfu(name);
	while (flag_name_again == 0)
	{
		goto_xy(47, 12);
		printf("\a�˺��ظ��� ");
		goto_xy(10,28);
		printf("���棺�˺��ظ������������룡                    ");
		Sleep(2000);
		goto_xy(47, 12);
		printf("             ");
		goto gbkd;
	}
	////////////////////////////////////////////////////////////�û����������
	gbk:goto_xy(47, 16);
	strcpy(pass1, input_pass_back());
	if (strcmp(pass1, "!#%&(") == 0)
		return;
	flag_pass_long = pass_long(pass1);
	while (flag_pass_long == 0)
	{
		goto_xy(47, 16);
		printf("\a���볤�ȴ���  ");
		goto_xy(10, 28);
		printf("���棺���볤�ȴ���������8-16λ��                  ");
		Sleep(2000);
		goto_xy(47, 16);
		printf("             ");


		goto_xy(47, 16);
		strcpy(pass1, input_pass_back());
		if (strcmp(pass1, "!#%&(") == 0)
			return;
		flag_pass_long = pass_long(pass1);
		goto_xy(10, 28);
		printf("                                                  ");
		goto_xy(0, 0);
	}

	goto_xy(47, 20);
	strcpy(pass2, input_pass_back());
	if (strcmp(pass2, "!#%&(") == 0)
		return;

	while (strcmp(pass1, pass2) != 0)
	{
		goto_xy(10, 28);
		printf("\a���棺�����������벻ͬ����3����������룡");
		Sleep(3000);
		goto_xy(47, 16);
		printf("                  ");
		goto_xy(47, 20);
		printf("                  ");
		goto gbk;
		
	}
	///////////////////////////////////////////////////////////////////�����������
	goto_xy(10, 28);
	printf("�� [*] �����л�������ʾģʽ��");

	int l = strlen(pass1);
	char out[19];
	int i;
	for (i = 0; i < l; i++)
	{
		out[i] = '*';
	}
	out[l] = '\0';
	///////////////////////////////////////////////////////////////////����

	list_reg_end();
	goto_xy(48, 12);
	printf("%s", name);
	goto_xy(48, 15);
	printf("%s", out);
	int flag_out = 0;//�жϵ�ǰ��ʾ���Ļ��ǰ���

	int flag_choose_ayn;
	flag_choose_ayn = choose_ayn();
	while (1)
	{
		if (flag_choose_ayn == 2)
		{
			if (flag_out % 2 == 0)
			{
				goto_xy(48, 15);
				printf("%s", pass1);
				flag_out++;
			}
			else
			{
				goto_xy(48, 15);
				printf("%s", out);
				flag_out++;
			}
		}
		else if (flag_choose_ayn == 1)
			break;
		else if (flag_choose_ayn == 0)
			goto gbko;
		flag_choose_ayn = choose_ayn();
		goto_xy(10, 28);
		printf("                                                  ");
		goto_xy(0, 0);
	}
	///////////////////////////////////////////////////////ȷ����������
	list_reg_pass();
	char gly_pass[19];
	Node *gly=out_n();//��ȡ��ȷ����

	int t = 0;

	pask:goto_xy(47, 14);
	strcpy(gly_pass, input_pass_back());
	if (strcmp(gly_pass, "!#%&(") == 0)
		return;
	t++;
	while ((strcmp(gly_pass, gly->password)))
	{
		if (t > 4)
		{

			goto_xy(47, 14);
			printf("        Wrong!    ");
			goto_xy(43, 20);
			printf("����������࣬������5����Զ��˳���");
			printf("\n\n\t\t\t\t�������ù���Ա���룬����ϵ��������̣��Ի�ȡ����֧�֣�");
			goto_xy(10, 28);
			printf("���棺�������������                                          \a");
			Sleep(5000);
			exit(EXIT_FAILURE);
		}

		goto_xy(10, 28);
		printf("\a���棺�������  ��3����������룡                ");
		goto_xy(47, 14);
		printf("\a�������        ");
		Sleep(3000);
		goto_xy(47, 14);
		printf("                    ");
		goto_xy(10, 28);
		printf("���棺�������  ���������룡 �㻹��%d�λ���                     ",5-t); 
		
		
		goto pask;
	}
	//////////////////////////////////////////////////////����Ա��������
	Node_p *mid;
	mid = (Node_p*)malloc(sizeof(Node_p));
	strcpy(mid->name, name);
	strcpy(mid->password, encryption(pass1));
	save(mid);

	free(mid);
	free(gly);

	return;
}
//��ʽ����ע��