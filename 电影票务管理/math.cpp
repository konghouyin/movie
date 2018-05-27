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
//加密函数

char* u_encryption(char* p)
{
	int i;
	for (i = 0; p[i] != '\0'; i++)
	{
		p[i] = (p[i] + 15);
	}
	return p;
}
//解密函数


void delete_st(void*)
{

}