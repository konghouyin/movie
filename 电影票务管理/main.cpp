#include"include.h"

int list_main(void);//���˵��б�
void door(void);//��������
void end(void);//�����˳�
void reg(void);//ע�����
void log(void);//��¼�����Ϣ


void gly_(void);//////////////////////////////////


int main(void)
{
	system("��ӰƱ�����ϵͳ---V3.2.2");
	door();
	int flag_list;
	while (1)
	{
		flag_list = list_main();
		switch (flag_list)
		{
		case 1:	Sleep(200); log(); break;
		case 2:Sleep(200);reg(); break;
		case 3:end();
		}
	}
	gly_();
	
	return 0;
}