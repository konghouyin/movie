#include"include.h"






void goto_xy(int x, int y);//��ת
void kuangjia(void);//�������
void save_time(void);//�洢��ʱ


int place_empty_choose(void);//�ճ��ص�ѡ��
int place_view_choose(void);//�����޸ĵ�ѡ��
void list_place_input(void);//��ӳ�����Ϣ
char* place_input(int x,int y);//������Ϣ��ȡ����
void list_place_end(place* p);//�������벢ȷ��
int choose_yn(void);//��ȡ�ǻ��
void list_place_star(int x, int y);//��ӡ�Ǻ�
int list_place_delete_choose(place *p);//ɾ����Ϣ��ȷ��



int place_chongfu(int n)
{
	place *pl;
	FILE *pln;
	pln = fopen("pln.txt", "a+");
	if (NULL == pln)
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

	pl = (place*)malloc(sizeof(place));
	while (fread(pl, sizeof(place), 1, pln) == 1)
	{
		if (n == pl->num)
			return 1;
	}
	return 0;
}
//����Ӱ���Ĳ���

place* open_place(void)
{
	place *pl, *pl_head, *mid;
	pl_head = (place*)malloc(sizeof(place));
	pl_head->next = NULL;
	mid = pl_head;

	FILE *pln;
	pln = fopen("pln.txt", "a+");
	if (NULL == pln)
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
	pl = (place*)malloc(sizeof(place));
	while (fread(pl, sizeof(place), 1, pln) == 1)
	{
		mid->next = pl;
		pl->next = NULL;
		mid = pl;
		pl = (place*)malloc(sizeof(place));
	}
	free(pl);
	return pl_head;
}
//�����ļ���


void save_place(place* pl)
{
	FILE *pln;
	pln = fopen("pln.txt", "w");
	if (pln == NULL)
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
		pl = pl->next;
		while (fwrite(pl, sizeof(place), 1, pln) == 1)
		{
			pl = pl->next;
			if (pl == NULL)
				break;
		}
	}
	fflush(pln);
	save_time();
	return;
}
//�����ļ��Ĵ洢


void output_place(place* pl)
{
	place *p, *pn;

	int i, j, n = 0;
	for (p = pl; p != NULL; p = p->next)
	{
		n++;
	}

	for (i = 0; i < n - 2; i++)
	{
		p = pl;
		for (j = 0; j < n - 2 - i; j++)
		{
			pn = p->next;
			if ((pn->num) >(pn->next->num))
			{
				p->next = p->next->next;
				pn->next = pn->next->next;
				p->next->next = pn;
			}
			p = p->next;
		}
	}


	clrscr();
	kuangjia();
	goto_xy(50, 6);
	printf("�� �� �� Ϣ �� ��");
	goto_xy(28, 8);
	printf("------------------------------------------------------------");
	goto_xy(31, 9);
	printf("ѡ��       ���ر��       ��       ��      ����������");


	i = 11;
	for (p = pl->next; p != NULL; p = p->next)
	{
		goto_xy(31, i);
		printf("             %2d           %2d       %2d           %3d", p->num,p->hang,p->lie ,p->site);
		i=i+2;
	}

	return;
}
//���򲢴�ӡ��صĳ�����Ϣ

int place_add(place *pl)
{
	char str[4];
	int flag_place;
	place *p;

	int n = 0;
	for (p = pl->next; p != NULL; p = p->next)
	{
		n++;
	}
	if (n >= 8)
	{
		clrscr();
		kuangjia();
		goto_xy(55,17);
		printf("Wrong!\a");
		goto_xy(50, 14);
		printf("Ӱ�����Ե�������!");
		goto_xy(50, 17);
		printf("3��󷵻س����б�");
		Sleep(3000);

		return 0;
	}


	p = (place*)malloc(sizeof(place));

	while (1)
	{
		int flag_place_chongfu;
		list_place_input();
		goto_xy(55, 11);
		strcpy(str, place_input(55,11));
		if (strcmp(str, "!") == 0)
		{
			free(p);
			return 0;
		}
		sscanf(str, "%d", &p->num);
		flag_place_chongfu = place_chongfu(p->num);
		if (flag_place_chongfu == 1)
		{
			clrscr();
			kuangjia();
			goto_xy(55, 11);
			printf("Wrong!\a");
			goto_xy(50, 14);
			printf("����Ӱ���Ѿ�¼��!");
			goto_xy(50, 17);
			printf("3���������Ϣ����");
			Sleep(3000);
			continue;
		}
		goto_xy(55, 15);
		strcpy(str, place_input(55,15));
		if (strcmp(str, "!") == 0)
		{
			free(p);
			return 0;
		}
		sscanf(str, "%d", &p->hang);

		goto_xy(55, 19);
		strcpy(str, place_input(55, 19));
		if (strcmp(str, "!") == 0)
		{
			free(p);
			return 0;
		}			
		sscanf(str, "%d", &p->lie);

		list_place_end(p);
		goto_xy(0, 0);
		flag_place = choose_yn();
		if (flag_place == 1)
			break;
	}
	p->site = p->hang*p->lie;
	p->next = pl->next;
	pl->next = p;
	return 1;
}
//���ص����

int place_delete(place *pl, int n)
{
	place *p,*q;
	q = pl;
	for (int i = 1; i < n; i++)
	{
		q = q->next;
	}
	p = q->next;
	int flag_place_delete = list_place_delete_choose(p);
	if (flag_place_delete == 1)
	{
		q->next = q->next->next;
		free(p);
		return 1;
	}
	else
		return 0;
}
//���ص�ɾ��

int place_change(place *pl, int n)

{
	place *p,*mid;
	mid = (place*)malloc(sizeof(place));
	p = pl;
	for (int i = 0; i < n; i++)
	{
		p = p->next;
	}
	
	char str1[4];
	char str2[4];
	char str3[4];

	while(1)
	{
		int flag_place_chongfu;
		list_place_input();
		goto_xy(55, 11);
		strcpy(str1, place_input(55, 11));
		if (strcmp(str1, "!") == 0)
		{
			free(mid);
			return 0;
		}
		sscanf(str1, "%d", &mid->num);


		flag_place_chongfu = place_chongfu(mid->num);
		if (flag_place_chongfu == 1 && mid->num!=p->num)
		{
			clrscr();
			kuangjia();
			goto_xy(55, 10);
			printf("Wrong!\a");
			goto_xy(43, 13);
			printf("������ĳ�����Ϣ��֮ǰ����ĳ�ͻ��");
			goto_xy(50, 16);
			printf("3���������Ϣ����");
			Sleep(3000);
			continue;
		}

		goto_xy(55, 15);
		strcpy(str2, place_input(55, 15));
		if (strcmp(str2, "!") == 0)
		{
			free(mid);
			return 0;
		}
		sscanf(str2, "%d", &mid->hang);

		goto_xy(55, 19);
		strcpy(str3, place_input(55, 19));
		if (strcmp(str3, "!") == 0)
		{
			free(mid);
			return 0;
		}
		sscanf(str3, "%d", &mid->lie);

		list_place_end(mid);
		goto_xy(0, 0);
		int flag_place = choose_yn();
		if (flag_place == 1)
			break;
	}
	sscanf(str1, "%d", &p->num);
	sscanf(str2, "%d", &p->hang);
	sscanf(str3, "%d", &p->lie);
	p->site = p->hang*p->lie;
	
	free(mid);
	return 1;

}
//������Ϣ���޸�

void place_manage(void)
{
	place *head;

place_jump:head = open_place();
	if (head->next == NULL)
	{
		clrscr();
		kuangjia();
		goto_xy(50, 10);
		printf("�� �� �� Ϣ �� ��");
		goto_xy(41, 15);
		printf("û���κγ�����Ϣ���� [+] ����µĳ���");
		goto_xy(50, 18);
		printf("�� [Esc] ���ز˵�");

		int flag_empty_place;
		goto_xy(16, 28);
		printf("û���κγ�����Ϣ���� [+] ����µĳ���                                      ");
		flag_empty_place = place_empty_choose();

		if (flag_empty_place == 0)//�ͷ�malloc
		{
			return;
		}
		else if (flag_empty_place == 1)
		{
			if(place_add(head))
				save_place(head);//�ͷ�malloc
			goto place_jump;
		}
	}
	else
	{
		int flag_place;

		output_place(head);
		goto_xy(20, 28);
		printf("����  ѡ��      ��[+] ����     [-] ɾ��       [*] �޸�      [Esc] ����     ");
		

		int n = 0;//��ʾ�����еĽڵ����
		place *p;
		for (p = head->next; p != NULL; p = p->next)
		{
			n++;
		}

		int i=11;
		list_place_star(31, i);
		flag_place = place_view_choose();

		while (1)
		{
			if (flag_place == 3)//��
			{
				if (place_add(head))
					save_place(head);//�ͷ�malloc
				goto place_jump;
			}
			else if (flag_place == 4)//ɾ��
			{
				if(place_delete(head, (i - 9) / 2))
					save_place(head);//�ͷ�malloc
				goto place_jump;
			}
			else if (flag_place == 5)//�޸�
			{
				if (place_change(head, (i - 9) / 2))
					save_place(head);//�ͷ�malloc
				goto place_jump;
			}
			else if (flag_place == 0)//����
			{
				return;
			}
			else if (flag_place == 1)//��ͷ����
			{
				if (i > 11)
				{
					i -= 2;
				}
			}
			else if (flag_place == 2)//��ͷ����
			{
				if (i < 9+2*n)
				{
					i += 2;
				}
			}
			list_place_star(31, i);
			flag_place = place_view_choose();
		}
	}
}
//���ع���