#include"include.h"


int list_gly(void);//����Ա�˵��б��б�
void movie_manage(void);//��Ӱ���ݹ���
void place_manage(void);//������Ϣ����
void people_manage(void);//�û���Ϣ����


void gly_(void)
{
	int flag_gly;
	
	while (1)
	{	flag_gly=list_gly();
		switch (flag_gly)
		{
		case 1:
		case 2:Sleep(200); people_manage(); break;
		case 3:Sleep(200); movie_manage(); break;
		case 4:Sleep(200); place_manage(); break;
		case 5:
		case 6: return;
		}
	}
}
//����Ա����
