#include"include.h"


char* encryption(char* p)
{
	int i;
	for (i = 0; p[i] != '\0'; i++)
	{
		p[i] = (p[i] - 15);
	}
	return p;
}
//���ܺ���

char* u_encryption(char* p)
{
	int i;
	for (i = 0; p[i] != '\0'; i++)
	{
		p[i] = (p[i] + 15);
	}
	return p;
}
//���ܺ���


void delete_st(void*)
{

}