#include"include.h"


void kuangjia(void);//����ģ��
void goto_xy(int x, int y);//��ת����
int jiantou(void);//��ͷʶ����
void kuangjia(void);//����ģ��
int choose_yn(void);//��ȡ�ǻ��
int jiantou_max(void);//�������Ҽ�ͷ��ȡ
int input_jiantou_back(void);//���¼�ͷ�ӷ��صĻ�ȡ
int choose_ayn(void);//��ȡ�Ƿ���Ǻ�
char* u_encryption(char* p);//���ܺ���



void cls(int x, int y)
{
	goto_xy(x, y);
	printf("                     ");
	goto_xy(x, y + 1);
	printf("   ");
	goto_xy(x + 19, y + 1);
	printf("   ");
	goto_xy(x, y + 2);
	printf("                     ");
	goto_xy(0, 0);
}
//������


void pt(int x, int y)
{
	goto_xy(x, y);
	printf("---------------------");
	goto_xy(x, y+1);
	printf("||");
	goto_xy(x+19, y + 1);
	printf("||");
	goto_xy(x, y+2);
	printf("---------------------");
}
//��ӡ˫�߿��

void pt_one(int x, int y)
{
	goto_xy(x, y);
	printf(" ---------------------");
	goto_xy(x, y + 1);
	printf("|");
	goto_xy(x + 19, y + 1);
	printf("   |");
	goto_xy(x, y + 2);
	printf(" ---------------------");
}
//��ӡ���߿��





void pt_main(int n)
{
	if (n == 1)
	{
		pt(43, 10);
		cls(43, 14);
		cls(43, 18);
		goto_xy(16, 28);
		printf("ѡ�����Ŀ�����Ե�¼ϵͳ�����й�Ʊ����Ϣ��ѯ��    ");
		goto_xy(0, 0);
	}
	else if (n == 2)
	{
		pt(43, 14);
		cls(43, 10);
		cls(43, 18);
		goto_xy(16, 28);
		printf("ѡ�����Ŀ������ע�ᣬ������ط���                  ");
		goto_xy(0, 0);
	}
	else if (n == 3)
	{
		pt(43, 18);
		cls(43,10);
		cls(43, 14);
		goto_xy(16, 28);
		printf("ѡ�����Ŀ�����԰�ȫ�˳������                        ");
		goto_xy(0, 0);
	}
}
//���˵���ӡת��

int list_main(void)
{
	int choose = 1;
	int jt;
	clrscr();
	kuangjia();
	goto_xy(23,6);
	printf("��ѡ���ܣ� ");
	goto_xy(50,11); 
	printf("1.��¼");
	goto_xy(50,15);
	printf("2.ע��");
	goto_xy(50,19);
	printf("3.�˳�");
	goto_xy(70, 25);
	printf("����  ѡ��     [Enter]   ȷ��");
	goto_xy(10,28);
	printf("˵����");


	
	pt_main(1);
	jt = jiantou();
	while (jt != 0)
	{
		if (jt == 2 && choose<3)
		{
			choose++;
		}
		else if (jt == 1 && choose > 1)
		{
			choose--;
		}
		pt_main(choose);
		jt = jiantou();
	}
	return choose;
}
//���˵���ѡ��





int list_reg_choose(void)
{
	clrscr();
	kuangjia();
	goto_xy(53,8);
	printf("�û���֪");
	Sleep(500);
	goto_xy(40,11);
	printf("1.ע��󼴿ɵ�¼ϵͳ��������ط���");
	Sleep(500);
	goto_xy(40,13);
	printf("2.���μ��˺ź����룬��������ϵ����Ա");
	Sleep(500);
	goto_xy(40,15);
	printf("3.�˺�1-10λ�ַ�������8-16λ�ַ�");
	Sleep(500);
	goto_xy(40,17);
	printf("4.�˺�����ֻ���ܳ����ַ� ");
	Sleep(800);
	goto_xy(35, 23);
	printf("[Enter]   ��һ��                 [Esc]   ȡ��");
	goto_xy(0, 0);

	return choose_yn();
}
//��֪�û�������棬��ȷ��

void list_reg_in(void)
{
	clrscr();
	kuangjia();
	goto_xy(55, 8);
	printf("ע ��");
	
	goto_xy(40, 12);
	printf("�˺ţ�");
	pt_one(46, 11);

	goto_xy(40, 16);
	printf("���룺");
	pt_one(46, 15);

	goto_xy(40, 20);
	printf("���룺");
	pt_one(46, 19);

	goto_xy(45, 23);
	printf("��ʾ���� [Esc] ����ע��");


}
//��ʽע���б�

void list_reg_end(void)
{
	clrscr();
	kuangjia();

	goto_xy(30,8);
	printf("��ȷ����д��Ϣ:");
	goto_xy(40,12);
	printf("�˺� : ");
	goto_xy(40,15);
	printf("���� : ");
	goto_xy(42, 17);
	printf("�� [*] ��ʾ�����أ�����");
	goto_xy(36,22);
	printf("[Enter]  ȷ��                [Esc]  ����");

}
//���������ȷ��

void list_reg_pass(void)
{
	clrscr();
	kuangjia();
	goto_xy(30, 8);
	printf("���������Ա�������ע��:");
	goto_xy(40, 14);
	printf("���룺");
	pt_one(46, 13);
	

}
//��ȡ����Ա����




void list_log_in(void)
{
	clrscr();
	kuangjia();

	goto_xy(51, 9);
	printf("ϵ ͳ �� ¼");

	goto_xy(40, 13);
	printf("�˺ţ�");
	pt_one(46, 12);

	goto_xy(40, 17);
	printf("���룺");
	pt_one(46, 16);

	goto_xy(45, 21);
	printf("��ʾ���� [Esc] ���ɷ���");
}
//��¼�������




void pt_gly(int n)
{
	if (n == 1)
	{
		pt(28,11);
		cls(62,11);
		cls(28,15);
		cls(62,15);
		cls(28, 19);
		cls(62, 19);
		goto_xy(16, 28);
		printf("ѡ�����Ŀ���ɽ���Ʊ�����             ");
		goto_xy(0, 0);
	}
	else if (n == 2)
	{
		pt(62, 11);
		cls(28,11);
		cls(28,15);
		cls(62,15);
		cls(28,19);
		cls(62, 19);
		goto_xy(16, 28);
		printf("ѡ�����Ŀ�����Թ�������ע���û���                      ");
		goto_xy(0, 0);
	}
	else if (n == 3)
	{
		pt(28, 15);
		cls(28,11);
		cls(62,11);
		cls(62,15);
		cls(28,19);
		cls(62, 19);
		goto_xy(16, 28);
		printf("ѡ�����Ŀ�������Ӱ�༭��                                  ");
		goto_xy(0, 0);
	}
	else if (n == 4)
	{
		pt(62, 15);
		cls(28,11);
		cls(28,15);
		cls(62,11);
		cls(28,19);
		cls(62, 19);
		goto_xy(16, 28);
		printf("ѡ�����Ŀ�����볡�ر༭��                                   ");
		goto_xy(0, 0);
	}
	else if (n == 5)
	{
		pt(28, 19);
		cls(28, 11);
		cls(28, 15);
		cls(62, 11);
		cls(62, 15);
		cls(62, 19);
		goto_xy(16, 28);
		printf("ѡ�����Ŀ����ʾ��ӰƱ����ص�ͳ����Ϣ��                  ");
		goto_xy(0, 0);
	}

	else if (n == 6)
	{
		pt(62, 19);
		cls(28,11);
		cls(28,15);
		cls(62,11);
		cls(62,15);
		cls(28, 19);
		goto_xy(16, 28);
		printf("ѡ�����Ŀ���ɰ�ȫ�˳���¼��                        ");
		goto_xy(0, 0);
	}

}
//����Ա��ӡת��

int list_gly(void)
{
	int choose = 1;
	int jt;

	clrscr();
	kuangjia();

	goto_xy(50, 7);
	printf("�� �� Ա �� ��");

	goto_xy(33,12);
	printf("1.Ʊ�����");

	goto_xy(67,12);
	printf("2.�û�����");

	goto_xy(33,16);
	printf("3.��Ӱ����");

	goto_xy(67,16);
	printf("4.���ع���");

	goto_xy(33,20);
	printf("5.ͳ����Ϣ");

	goto_xy(67, 20);
	printf("6.�˳���¼");


	goto_xy(66, 25);
	printf("��������  ѡ��     [Enter]   ȷ��");


	pt_gly(1);
	jt = jiantou_max();
	while (jt != 0)
	{
		if (choose==1||choose==3||choose==5)
		{
			if (jt == 4)
			{
				choose++;
				goto bbtt;
			}
		}
		if (choose==2||choose==4||choose==6)
		{
			if (jt == 3)
			{
				choose--;
				goto bbtt;
			}
		}
		if (choose == 1 || choose == 2 || choose == 3 || choose == 4)
		{
			if (jt == 2)
			{
				choose += 2;
				goto bbtt;
			}
		}
		if (choose == 3 || choose == 4 || choose == 5 || choose == 6)
		{
			if (jt == 1)
			{
				choose -= 2;
				goto bbtt;
			}
		}
		bbtt:pt_gly(choose);
		jt = jiantou_max();
	}
	return choose;
}
//����Ա�˵���ѡ��




void list_place_input(void)
{
	clrscr();
	kuangjia();

	goto_xy(51, 7);
	printf("�� �� �� ��");

	goto_xy(40, 11);
	printf("��ţ�");
	pt_one(46, 10);

	goto_xy(40, 15);
	printf("������");
	pt_one(46, 14);

	goto_xy(40, 19);
	printf("������");
	pt_one(46, 18);

	goto_xy(45, 23);
	printf("��ʾ���� [Esc] ���ɷ���");
}
//��ӳ�����Ϣ

void list_place_end(place *p)
{
	clrscr();
	kuangjia();

	goto_xy(40, 9);
	printf("��ȷ����д��Ϣ:");
	goto_xy(50, 12);
	printf("��� :   %d",p->num);
	goto_xy(50, 15);
	printf("���� :   %d",p->hang);
	goto_xy(50, 18);
	printf("���� :   %d", p->lie);
	goto_xy(36, 24);
	printf("[Enter]  ȷ��              [Esc]  ������д");
	goto_xy(0, 0);
}
//�������벢ȷ��

int list_place_delete_choose(place *p)
{
	clrscr();
	kuangjia();

	goto_xy(35, 8);
	printf("��ȷ���Ƿ�ɾ�������Ϣ:");
	goto_xy(50, 11);
	printf("��� :   %d", p->num);
	goto_xy(50, 14);
	printf("���� :   %d", p->hang);
	goto_xy(50, 17);
	printf("���� :   %d", p->lie);
	goto_xy(50, 20);
	printf("���� :   %d", p->site);
	goto_xy(36, 24);
	printf("[Enter]  ȷ��              [Esc]  ����");
	goto_xy(0, 0);

	if (choose_yn())
		return 1;
	else
		return 0;
}
//ɾ��������Ϣ��ȷ��

void list_place_star(int x, int y)
{
	goto_xy(x, y);
	printf("--->");
	int i;
	for (i = y - 2; i >= 11; i -= 2)
	{
		goto_xy(x, i);
		printf("    ");
	}
	for (i = y + 2; i <= 25; i += 2)
	{
		goto_xy(x, i);
		printf("    ");
	}
	goto_xy(0, 0);
	return;
}
//��ӡ�Ǻ�



void pt_people(int n)
{
	if (n == 1)
	{
		pt(47, 12);
		cls(47, 17);
		goto_xy(16, 28);
		printf("ѡ�����Ŀ���ɽ���ע���û��Ĺ���                  ");
		goto_xy(0, 0);
	}
	else if (n == 2)
	{
		pt(47, 17);
		cls(47, 12);
		goto_xy(16, 28);
		printf("ѡ�����Ŀ�������޸Ĺ���Ա���롣                      ");
		goto_xy(0, 0);
	}
}
//��ӡ�����߿�

int list_gly_people(void)//���뺯����Ҫ�������ܹ������£���Ҫ���Ƿ���
{
	clrscr();
	kuangjia();

	goto_xy(30, 9);
	printf("��ѡ����Ҫ�鿴����Ϣ:");
	goto_xy(55, 13);
	printf("�û�");
	goto_xy(55, 18);
	printf("����Ա");
	goto_xy(50, 25);
	printf("����  ѡ��     [Enter]   ȷ��      [Esc]   ����");

	int choose = 1;
	int jt;

	pt_people(1);
	jt = input_jiantou_back();
	while (jt != 0 && jt !=3 )
	{
		if (jt == 2 && choose==1)
		{
			choose++;
		}
		else if (jt == 1 && choose ==2)
		{
			choose--;
		}
		pt_people(choose);
		jt = input_jiantou_back();
	}
	if (jt == 0)
		return choose;
	else
		return 0;
}
//��ӡ�û���Ϣѡ��˵���ѡ��


int list_gly_change_choose(Node *gly)
{
	int l = strlen(gly->password);
	char out[19];
	int i;
	for (i = 0; i < l; i++)
	{
		out[i] = '*';
	}
	out[l] = '\0';

	list_reg_end();
	goto_xy(30, 8);
	printf("�Ƿ���Ҫ�޸Ĺ���Ա��Ϣ��");
	goto_xy(48, 12);
	printf("%s", gly->name);
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
				printf("%s", gly->password);
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
			return 1;
		else if (flag_choose_ayn == 0)
			return 0;
		flag_choose_ayn = choose_ayn();
		goto_xy(0, 0);
	}
}
//�Ƿ��޸Ĺ���Ա��Ϣ

int list_people_delete_choose(Node_p *p)
{
	clrscr();
	kuangjia();

	char gd[19];
	strcpy(gd, p->password);
	goto_xy(35, 10);
	printf("��ȷ���Ƿ�ɾ�������Ϣ:");
	goto_xy(50, 13);
	printf("�û��� :   %s", p->name);
	goto_xy(50, 16);
	printf("���� :   %s", u_encryption(gd));
	goto_xy(36, 24);
	printf("[Enter]  ȷ��              [Esc]  ����");
	goto_xy(0, 0);

	if (choose_yn())
		return 1;
	else
		return 0;
}
//ɾ��������Ϣ��ȷ��



void list_people_find(void)
{
	clrscr();
	kuangjia();

	goto_xy(51, 7);
	printf("�� �� �� ѯ");

	goto_xy(40, 10);
	printf("�˺ţ�");
	pt_one(46, 9);

	goto_xy(50, 13);
	printf("�� [Esc] ����");
	
}
//�û���Ϣ��ѯ


void list_movie_add1(void)
{
	clrscr();
	kuangjia();

	goto_xy(48, 7);
	printf("�� Ӱ �� Ϣ �� ��");

	goto_xy(40, 11);
	printf("���ƣ�");

	goto_xy(40, 14);
	printf("ʱ�䣺");

	goto_xy(40, 17);
	printf("��");

	goto_xy(40, 23);
	printf("��Ӱ���ͣ�");

	goto_xy(30,25);
	printf("��ʾ����[Enter]ȷ���������󣬲���ʼ��д��һ��");
}
//��ӵ�Ӱ��Ϣ