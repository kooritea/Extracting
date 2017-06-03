#ifndef _KTR_H_
#define _KTR_H_

#pragma once
#include<string>
#include<iostream>
#include<stdio.h>
using namespace std;

typedef struct
{
	string base;
	string diff;
	string x;
	string y;
	string w;
	string h;
}Data;                       //储存一行的数据的结构体
typedef struct txt_list_list
{
	struct txt_list_list *last;
	Data data;
	struct txt_list_list *next;
}txt_list_list, *zhentxt_list;

typedef struct
{
	Data *top;
	Data *base;
}txt_list_zhan;                                                                     //倒叙输出用的栈

void maketxt_list_zhan(txt_list_zhan &p)
{
	p.top = new Data[10000];
	p.base = p.top;
}

void setfilehkaitou(FILE *a)                                        //将指针移动到下一行的开头
{
	unsigned char n[1];
	while (fread(n, 1L, 1, a) != NULL)
	{
		if (n[0] == 0x0a)
		{
			break;
		}
	}
}


void setdata(Data &p, string base, string diff, string x, string y, string w, string h)
{
	p.base = base;
	p.diff = diff;
	p.x = x;
	p.y = y;
	p.w = w;
	p.h = h;
}

void maketxt_list(zhentxt_list &txt_list)
{
	txt_list = new txt_list_list;
	setdata(txt_list->data, "-1", "-1", "-1", "-1", "-1", "-1");
	txt_list->next = NULL;
	txt_list->last = NULL;
}

void addtxt_list_list(zhentxt_list &txt_list, string base, string diff, string x, string y, string w, string h)                 //将查找到的数据写进链表中
{
	static zhentxt_list rail = txt_list;
	zhentxt_list p = new txt_list_list;
	setdata(p->data, base, diff, x, y, w, h);
	p->next = NULL;
	p->last = rail;
	rail->next = p;
	rail = p;
	rail->next = NULL;
}

void push(txt_list_zhan &p, string base, string diff, string x, string y, string w, string h)
{
	p.top->base = base;
	p.top->diff = diff;
	p.top->x = x;
	p.top->y = y;
	p.top->w = w;
	p.top->h = h;
	p.top = p.top + 1;
}

void deltxt_list_list(zhentxt_list &linshi)
{
	zhentxt_list lasttxt_list_list, nexttxt_list_list;
	lasttxt_list_list = linshi->last;
	nexttxt_list_list = linshi->next;
	lasttxt_list_list->next = nexttxt_list_list;
	free(linshi);
	linshi = nexttxt_list_list;
	if (nexttxt_list_list != NULL)
	{
		nexttxt_list_list->last = lasttxt_list_list;
	}

}

void push_first_base(zhentxt_list &linshi, string &base, txt_list_zhan &p)
{
push_first_base1:
	if ((linshi->data.base) == base && (linshi->data.diff) == "-1")
	{
		p.top = p.base;
		push(p, linshi->data.base, linshi->data.diff, linshi->data.x, linshi->data.y, linshi->data.w, linshi->data.h);
		deltxt_list_list(linshi);
	}
	else
	{
		linshi = linshi->next;
		goto push_first_base1;
	}
}

void push_diff(zhentxt_list &linshi, string base, txt_list_zhan &p)
{
push_diff1:
	if (linshi != NULL)
	{
		if ((linshi->data.base) == base)
		{
			push(p, linshi->data.base, linshi->data.diff, linshi->data.x, linshi->data.y, linshi->data.w, linshi->data.h);
			deltxt_list_list(linshi);                                                                                       //已经将指针设置到下一个节点
			goto push_diff1;
		}
		else
		{
			linshi = linshi->next;
			goto push_diff1;
		}
	}
}

void writezhaxiang(FILE *txt, char(&a)[2], int b, string cs, string ds, string es, string fs)                              //写入数据表情信息name id w h x y
{
	char huanhang[2]; huanhang[0] = 0x0d; huanhang[1] = 0x0a;
	string names = "name:         ";
	char name[100];
	strcpy(name, names.c_str());
	fwrite(name, strlen(name), 1, txt);
	fwrite(a, 2, 1, txt);
	fwrite(huanhang, 2, 1, txt);
	string layer_ids = "layer_id:     ";
	char layer_id[100];
	strcpy(layer_id, layer_ids.c_str());
	fwrite(layer_id, strlen(layer_id), 1, txt);
	fprintf(txt, "%d", b);
	fwrite(huanhang, 2, 1, txt);
	string widths = "width:        ";
	char width[100];
	char c[100];
	strcpy(width, widths.c_str());
	fwrite(width, strlen(width), 1, txt);
	strcpy(c, cs.c_str());
	fwrite(c, strlen(c), 1, txt);
	fwrite(huanhang, 2, 1, txt);
	string heights = "height:       ";
	char height[100];
	char d[100];
	strcpy(height, heights.c_str());
	fwrite(height, strlen(height), 1, txt);
	strcpy(d, ds.c_str());
	fwrite(d, strlen(d), 1, txt);
	fwrite(huanhang, 2, 1, txt);
	string lefts = "left:         ";
	char left[100];
	char e[100];
	strcpy(left, lefts.c_str());
	fwrite(left, strlen(left), 1, txt);
	strcpy(e, es.c_str());
	fwrite(e, strlen(e), 1, txt);
	fwrite(huanhang, 2, 1, txt);
	string tops = "top:          ";
	char top[100];
	char f[100];
	strcpy(top, tops.c_str());
	fwrite(top, strlen(top), 1, txt);
	strcpy(f, fs.c_str());
	fwrite(f, strlen(f), 1, txt);
	fwrite(huanhang, 2, 1, txt);
	string opacitys = "opacity:      255";
	char opacity[100];
	strcpy(opacity, opacitys.c_str());
	fwrite(opacity, strlen(opacity), 1, txt);
	fwrite(huanhang, 2, 1, txt);
	string layer_types = "layer_type:   0";
	char layer_type[100];
	strcpy(layer_type, layer_types.c_str());
	fwrite(layer_type, strlen(layer_type), 1, txt);
	fwrite(huanhang, 2, 1, txt);
	string types = "type:         13";
	char type[100];
	strcpy(type, types.c_str());
	fwrite(type, strlen(type), 1, txt);
	fwrite(huanhang, 2, 1, txt);
	string visibles = "visible:      1";
	char visible[100];
	strcpy(visible, visibles.c_str());
	fwrite(visible, strlen(visible), 1, txt);
	fwrite(huanhang, 2, 1, txt);
	fwrite(huanhang, 2, 1, txt);
}

void writehead(FILE *txt)
{
	string heads_1 = "image_width:  1280";
	string heads_2 = "image_height: 720";
	char huanhang[2]; huanhang[0] = 0x0d; huanhang[1] = 0x0a;
	fwrite(heads_1.c_str(), heads_1.length(), 1, txt);                                                              //规则头 共39字节
	fwrite(huanhang, 2, 1, txt);
	fwrite(heads_2.c_str(), heads_2.length(), 1, txt);
	fwrite(huanhang, 2, 1, txt);
	fwrite(huanhang, 2, 1, txt);
}

void writebase(FILE *txt, int maxw, int maxh)
{
	char huanhang[2]; huanhang[0] = 0x0d; huanhang[1] = 0x0a;
	string names = "name:         Aa";
	char name[100];
	strcpy(name, names.c_str());
	fwrite(name, strlen(name), 1, txt);
	fwrite(huanhang, 2, 1, txt);
	string layer_ids = "layer_id:     2";
	char layer_id[100];
	strcpy(layer_id, layer_ids.c_str());
	fwrite(layer_id, strlen(layer_id), 1, txt);
	fwrite(huanhang, 2, 1, txt);
	string widths = "width:        ";
	char width[100];
	strcpy(width, widths.c_str());
	fwrite(width, strlen(width), 1, txt);
	fprintf(txt, "%d", maxw);
	fwrite(huanhang, 2, 1, txt);
	string heights = "height:       ";
	char height[100];
	strcpy(height, heights.c_str());
	fwrite(height, strlen(height), 1, txt);
	fprintf(txt, "%d", maxh);
	fwrite(huanhang, 2, 1, txt);
	string lefts = "left:         0";
	char left[100];
	strcpy(left, lefts.c_str());
	fwrite(left, strlen(left), 1, txt);
	fwrite(huanhang, 2, 1, txt);
	string tops = "top:          0";
	char top[100];
	strcpy(top, tops.c_str());
	fwrite(top, strlen(top), 1, txt);
	fwrite(huanhang, 2, 1, txt);
	string opacitys = "opacity:      255";
	char opacity[100];
	strcpy(opacity, opacitys.c_str());
	fwrite(opacity, strlen(opacity), 1, txt);
	fwrite(huanhang, 2, 1, txt);
	string layer_types = "layer_type:   0";
	char layer_type[100];
	strcpy(layer_type, layer_types.c_str());
	fwrite(layer_type, strlen(layer_type), 1, txt);
	fwrite(huanhang, 2, 1, txt);
	string types = "type:         13";
	char type[100];
	strcpy(type, types.c_str());
	fwrite(type, strlen(type), 1, txt);
	fwrite(huanhang, 2, 1, txt);
	string visibles = "visible:      1";
	char visible[100];
	strcpy(visible, visibles.c_str());
	fwrite(visible, strlen(visible), 1, txt);
	fwrite(huanhang, 2, 1, txt);
	fwrite(huanhang, 2, 1, txt);
}

void addname(char(&name)[2], int i)
{
	for (i; i > 0; i--)
	{
		if (name[1] == 'z')
		{
			name[0]++;
			name[1] = 'a';
		}
		else
		{
			name[1]++;
		}
	}
}

void reducename(char(&a)[2])
{
	if (a[1] == 'a')
	{
		a[0]--;
		a[1] = 'z';
	}
	else
	{
		a[1]--;
	}
}

int  get_txt_list_zhan_size(txt_list_zhan &p)
{
	int i = 0;
	Data *linshi;
	linshi = p.top;
	while (linshi != p.base)
	{
		linshi--;
		i++;
	}
	return i;
}

string caseletters(string z)                                                            //大写换小写
{
	int i;
	for (i = z.length(); i > 0; i--)
	{
		if (z[i - 1]<'Z'&&z[i - 1]>'A')
		{
			z[i - 1] = z[i - 1] + 32;
		}
	}
	return z;
}

void pop_txt_list_zhan_diff(txt_list_zhan &p, FILE *txt)                                                 //仅写入非底数据
{
	char name[2];
	char i[20];
	string newname, oldname, ints;
	name[0] = 'A'; name[1] = 'a';
	int layer_id = 1 + get_txt_list_zhan_size(p);                                                //获取栈的高度以设置name及id
	addname(name, get_txt_list_zhan_size(p) - 1);
pop_txt_list_zhan_diff1:
	if (p.top != p.base + 1)
	{
		p.top = p.top - 1;
		writezhaxiang(txt, name, layer_id, p.top->w, p.top->h, p.top->x, p.top->y);
		sprintf(i, "%d", layer_id);
		ints = i;
		newname = (p.top->base) + "+pimg+" + ints + ".bmp";
		oldname = caseletters(p.top->diff) + ".bmp";
		rename(oldname.c_str(), newname.c_str());
	}
	layer_id--;
	reducename(name);
	if (p.top != p.base + 1)
	{
		goto pop_txt_list_zhan_diff1;
	}
	layer_id = 1;
}

void renamebase(txt_list_zhan &p)
{
	string oldname, newname;
	oldname = caseletters(p.base->base) + ".bmp";
	newname = (p.base->base) + "+pimg+" + "2.bmp";
	rename(oldname.c_str(), newname.c_str());
}

void pop_txt(txt_list_zhan &p)
{
	FILE *txt;
	string txtnames;
	txtnames = p.base->base + "+pimg+layers.txt";
	txt = fopen(txtnames.c_str(), "wb");
	writehead(txt);                                                             //写入规定大小的规则头
	renamebase(p);																//更改底文件名
	pop_txt_list_zhan_diff(p, txt);                                                      //写入非底规格
	writebase(txt, 1280, 720);                                                  //写入底规则
	fclose(txt);
}

void henduotxt_list_list(txt_list_zhan &p, zhentxt_list &txt_list)
{
	string base;
	zhentxt_list linshi;
henduotxt_list_list1:
	linshi = txt_list->next;											//指向的第一个有数据的节点
	base = txt_list->next->data.base;								//n=第一个节点的base
	push_first_base(linshi, base, p);                           //当前底节点入栈并删除底节点
	linshi = txt_list->next;                                         //重置临时指针到第一个节点
	push_diff(linshi, base, p);                                 //将所有这个底的节点推入栈,并删除这些节点
	pop_txt(p);                                                 //完成同一个底的txt
	if (txt_list->next != NULL)
	{
		goto henduotxt_list_list1;
	}
}

void input_txt_for_txt_list(zhentxt_list &txt_list)
{
	txt_list_zhan p;
	maketxt_list_zhan(p);
	henduotxt_list_list(p, txt_list);
}

//input_txt_for_txt_list()使用
//zhentxt_list txt_list;
//maketxt_list(txt_list);
//提取base, diff, x, y, w, h   使用addtxt_list_list(txt_list, base, diff, x, y, w, h);直到所有数据存入链表中
//input_txt_for_txt_list(txt_list);

#endif
