#include<string>
#include<iostream>
#include<stdio.h>
#include"krt.h"
using namespace std;

void searchdata(FILE *a, string &base, string &diff, string &x, string &y, string &w, string &h)
{
	string m;                                                       //中间变量
	unsigned char n[1];
	int d;
	static int o = 1;                                               //静态变量 只执行一次   第几行
	base = "";
	diff = "";
	x = "";
	y = "";
	w = "";
	h = "";
	while (fread(n, 1L, 1, a) != NULL&&o == 1)                        //跳过第一行
	{
		if (n[0] == 0x0a)
		{
			o++;
			break;
		}
	}
	d = 0;
	while (n[0] != ',')
	{
		fread(n, 1L, 1, a);
	}
	fread(n, 1L, 1, a);
	while (n[0] != ',')
	{
		m = n[0];
		base = base + m;
		fread(n, 1L, 1, a);
	}
	fread(n, 1L, 1, a);
	if (n[0] != ',')
	{
		while (n[0] != ',')
		{
			m = n[0];
			diff = diff + m;
			fread(n, 1L, 1, a);
		}
	}
	else
	{
		diff = "-1";
	}
	fread(n, 1L, 1, a);
	while (n[0] != ',')
	{
		m = n[0];
		x = x + m;
		fread(n, 1L, 1, a);
	}
	fread(n, 1L, 1, a);
	while (n[0] != ',')
	{
		m = n[0];
		y = y + m;
		fread(n, 1L, 1, a);
	}
	fread(n, 1L, 1, a);
	while (n[0] != ',')
	{
		m = n[0];
		w = w + m;
		fread(n, 1L, 1, a);
	}
	fread(n, 1L, 1, a);
	while (n[0] != ',')
	{
		m = n[0];
		h = h + m;
		fread(n, 1L, 1, a);
	}
	setfilehkaitou(a);
}

void loadlist(FILE *a, zhentxt_list &txt_list)
{
	string base, diff, x, y, w, h;
	unsigned n[1];
	while (fread(n, 1L, 1, a) != NULL)
	{
		fseek(a, -1L, 1);
		searchdata(a, base, diff, x, y, w, h);
		addtxt_list_list(txt_list, base, diff, x, y, w, h);
	}
}

void main(int argc, char *argv[])
{
	zhentxt_list txt_list;                                        //存储整个txt_list数据的链表的指针																						 
	FILE *a;                                                                          //.csv的指针
	if ((a = fopen(argv[1], "r")) == NULL)                       //检查文件是否打开成功
	{
		printf("文件打开失败，任意键回车退出\n");
		exit(0);                                        //退出程序
	}
	else
	{
		printf("打开成功\n");
	}
	maketxt_list(txt_list);
	loadlist(a, txt_list);                                               //所有数据已经存入链表
	input_txt_for_txt_list(txt_list);
}
