#pragma once
/*---------------------头部引用及定义开始---------------------*/
#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"FilesOpera.h"

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define ELEMTYPE int
#define Status int
#define MAXSIZE 100	
//using namespace std;
/*---------------------头部引用及定义结束---------------------*/

struct Book {
	std::string id;//ISBN
	std::string name;//书名
	double price;//定价
	int number;//数量
};
typedef struct DuLNode {
	Book data; //数据域
	struct DuLNode *prior; //直接前驱
	struct DuLNode *next; //直接后继
} DuLNode, *DuLinkList;

std::string head_1, head_2, head_3, head_4;
int length;

Status InitDuList_L(DuLinkList &L) {
	//构造一个空的双向链表L
	L = new DuLNode; //生成新结点作为头结点，用头指针L指向头结点
	L->next = NULL; //头结点的指针域置空
	L->prior = NULL;
	return OK;
}

DuLNode *GetElemP_DuL(DuLinkList L, int i) {
	//在带头结点的双向链表L中查找第i个元素，返回结点的地址
	int j;
	DuLinkList p;
	p = L->next;
	j = 1; //初始化，p指向第一个结点，j为计数器
	while (j < i && p) { //顺链域向后扫描，直到p指向第i个元素或p为空
		p = p->next;
		++j;
	}
	if (!p || j > i)
		return NULL; //第i个元素不存在
	return p;
} //GetElemP_DuL

Status ListInsert_DuL(DuLinkList &L, int i, Book e) { //算法2.13 双向链表的插入
	//在带头结点的双向链表L中第i个位置之前插入元素e，i的合法值为1<=i<=表长+1
	DuLinkList s, p;
	if (!(p = GetElemP_DuL(L, i))) //在L中确定第i个元素的位置指针p
		return ERROR; //p为NULL时，第i个元素不存在
	if (i == 1) {//在双向链表的第一个元素上插入
		s = new DuLNode; //生成新结点s
		s->data = e; //将结点s数据置为e
		DuLinkList p = L->next;
		L->next = s;
		s->prior = L;
		s->next = p;//将结点*s插入L中
		p->prior = s;
		++length;
	}
	else if (i == length) {//在双向链表的最后一个元素上插入
		s = new DuLNode; //生成新结点s
		s->data = e; //将结点s数据置为e
		DuLinkList p = L;
		while (p->next)
			p = p->next;//将LinkList p指向双向链表结尾
		p->next = s;
		s->prior = p;//将结点*s插入到p的后面，插入到L中
		s->next = NULL;
		++length;
	}
	else {
		s = new DuLNode; //生成新结点*s
		s->data = e; //将结点*s数据域置为e
		s->prior = p->prior; //将结点*s插入L中，此步对应图2.20① 
		p->prior->next = s; //对应图2.20②
		s->next = p; //对应图2.20③
		p->prior = s; //对应图2.20④
		++length;
	}
	return OK;
} //ListInsert_DuL

Status ListDelete_DuL(DuLinkList &L, int i) { //算法2.14 双向链表的删除
	//删除带头结点的双向链表L中第i个位置之前插入元素e，i的合法值为1<=i<=表长
	DuLinkList p;
	if (!(p = GetElemP_DuL(L, i))) //在L中确定第i个元素的位置指针p
		return ERROR; //p为NULL时，第i个元素不存在
	if (i == 1)//删除双向链表的第一个元素
		L = L->next;
	else if (i == length) {//删除双向链表的最后一个元素
		p->prior->next = NULL;
		delete p;
		--length;
		return OK;
	}
	else {
		p->prior->next = p->next; //修改被删结点的前驱结点的后继指针，对应图2.21①
		p->next->prior = p->prior; //修改被删结点的后继结点的前驱指针，对应图2.21②
		delete p; //释放被删结点的空间 
		--length;
		return OK;
	}
}//ListDelete_DuL

void CreateDuList_L(DuLinkList &L) {
	//正位序输入n个元素的值，建立带表头结点的双向链表L，同时建立前驱指针
	DuLinkList r, p;
	L = new DuLNode;
	L->next = NULL; //先建立一个带头结点的空链表
	r = L;//尾指针r指向头结点
	length = 0;
	std::fstream file;
	file.open("book.txt");
	if (!file) {
		std::cout << "未找到相关文件，无法打开！" << std::endl;
		exit(ERROR);
	}
	file >> head_1 >> head_2 >> head_3 >> head_4;
	while (!file.eof()) {
		p = new DuLNode; //生成新结点
		file >> p->data.id >> p->data.name >> p->data.price >> p->data.number; //输入元素值
		p->next = NULL;
		r->next = p;
		p->prior = r;//插入到表尾
		r = p; //r指向新的尾结点
		//p->prior = L->prior; //插入到表头
		//L->prior = p;
		length++;
	}
	file.close();
} //CreateDuList_L

DuLNode* ISBNcompare(DuLinkList L, std::string ISBN)           //通过ISBN查书
{
	DuLinkList p;
	p = L->next;  /* 初始化，p指向第一个结点 */
	while (p && ISBN.compare(p->data.id))
	{ /* 顺指针向后查找，直到p指向的当前元素与e相等或p为空 */
		p = p->next;
	}
	return p;
}

DuLNode* FixInfor(DuLinkList L, double pt)  //修改价格
{
	DuLinkList p;
	p = L;  /* 初始化，p指向第一个结点 */
	p->data.price = pt;
	return p;
}

DuLNode* Total(DuLinkList L)    //统计书籍数量
{
	DuLinkList p;
	double total_price = 0, total_number = 0;
	p = L->next;  /* 初始化，p指向第一个结点 */
	while (p && p->next)
	{ /* 顺指针向后查找，直到倒数第二个元素 */
		total_price += p->data.price*p->data.number;
		total_number += p->data.number;
		p = p->next;
	}
	total_price += p->data.price*p->data.number; //统计最后一个结点
	total_number += p->data.number;
	//s = new DuLNode; //生成新结点s
	L->data.price = total_price; //将统计数据放入头结点
	L->data.number = total_number;
	//p->next = s;
	//s->prior = p;//将结点*s插入到p的后面，插入到l中
	//s->next = null;
	return L;
}


void FindBk(DuLinkList L, std::string bkt)    //模糊检索图书
{
	int flag = 0;//指示是否检索到书目
	DuLinkList p;
	std::string a, b;
	p = L->next;  /* 初始化，p指向第一个结点 */
	std::cout << "已为你找到以下书目：\n";
	std::cout << std::left << std::setw(15) << "ISBN号" << std::left << std::setw(50) << "书名" << "\t" << std::left << std::setw(5) << "价格" << "\t" << std::left << std::setw(15) << "数量" << std::endl;
	while (p)
	{ /* 顺指针向后查找，直到p指向的当前元素ISBN匹配的图书 */
		a = p->data.name;
		const char *k = a.c_str();//两个const字符指针类型，用于使用子串匹配函数strstr()
		const char *l = bkt.c_str();
		if (strstr(k, l))//子串匹配函数
		{
			flag = 1;
			std::cout << std::left << std::setw(15) << p->data.id << "\t" << std::left << std::setw(50) << p->data.name << "\t" << std::left << std::setw(5) << p->data.price << "\t" << std::left << std::setw(5) << p->data.number << std::endl;
			/* 当前图书ISBN匹配则输出，否则跳转下一个 */
			//std::cout << a << std::endl;
		}
		p = p->next;
	}
	if (!flag)
	{
		//system("cls");
		std::cout << "未找到书目，请核实后重新输入\n";
	}
}

void Sort_books_prince(DuLinkList &L)    //价格升序排序图书
{
	int n = 0;
	L->data.price = -1;
	DuLNode* star = L;
	DuLNode* p_locate, *p_compare, *p_next;
	p_locate = L->next;
	p_compare = L->next->next;
	p_next = L->next->next->next;

	while (p_compare)
	{
		while (p_locate->data.price >= p_compare->data.price)
		{
			p_locate = p_locate->prior;
			//cout << n++ << endl;
		}

		if (p_locate == p_compare->prior&&p_compare->next == NULL)
		{
			p_compare = NULL;
			continue;
		}


		if (p_compare->next != NULL)
		{
			p_compare->prior->next = p_compare->next;
			p_compare->next->prior = p_compare->prior;


			p_compare->next = p_locate->next;
			p_locate->next->prior = p_compare;
			p_locate->next = p_compare;
			p_compare->prior = p_locate;

			p_compare = p_next;
			//			cout << p_locate->data.name << endl;
			if (p_compare != NULL)
			{
				p_next = p_next->next;
			}

			p_locate = p_compare->prior;
		}

		else

		{
			p_compare->prior->next = NULL;
			p_compare->next = p_locate->next;
			p_locate->next->prior = p_compare;
			p_locate->next = p_compare;
			p_compare->prior = p_locate;

			p_compare = NULL;
		}

	}
}

void Change_store(DuLinkList &L, int n, int shuliang)    //出借图书
{
	DuLNode* p = L->next;
	int count1 = 1;

	while ((count1++) != n&&p)
	{
		p = p->next;
	}

	if (shuliang > p->data.number&&p)
		std::cout << "不好意思，您所借书本的数量超过库存\n" << std::endl;

	else
	{
		p->data.number -= shuliang;
		std::cout << "借出成功\n" << std::endl;
	}
}

void Return_book(DuLinkList &L, std::string buku, int num)    //归还图书
{
	DuLNode* p = L->next;

	while (p && strcmp(p->data.id.c_str(), buku.c_str()) != 0)
	{
		p = p->next;
	}
	if (!p)
	{
		std::cout << "本书库不存在您这本书，请问您是否要在书库中追加此书" << std::endl;
		std::cout << "需要请按 1； 不需要请按 2" << std::endl;
		int choice = 0; int a; Book e;
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			std::cout << "请输入您想存放的位置" << std::endl;
			std::cin >> a;
			std::cout << "请继续完善书本信息，依次填入：书名， 价格，数量" << std::endl;
			e.id = buku;
			std::cin >> e.name >> e.price >> e.number;

			if (ListInsert_DuL(L, a, e))
				std::cout << "添加成功.\n\n";
			else
				std::cout << "添加失败!\n\n";
			break;
		case 2:
			std::cout << "本次操作结束\n" << std::endl;
			break;
		}
	}
	else
	{
		p->data.number += num;
		std::cout << "已经载入库存！" << std::endl;
	}


}


int Search_book(DuLinkList &L, int xvhao)    //按序号匹配图书
{
	DuLNode* p = L->next;
	int count = 1;
	while (p && (count++) < xvhao)
	{
		p = p->next;
	}
	if (p)
	{
		return p->data.number;
	}
	else
	{
		return -1;
	}
}


int IfEmpty(DuLinkList &L, int &a)    //用于新增图示判表空
{
	DuLinkList s;
	int flag = 0;//指示用户是否接受在头部插入
	int cho;
	if (L->next == NULL)
	{
		std::cout << "当前图书信息为空，是否直接在头部插入？\n";
		std::cout << "按 1 确认在头部插入，按 2 退回到主菜单\n";
		std::cin >> cho;
		switch (cho)
		{
		case 1:
			s = new DuLNode;
			s->next = L->next;
			L -> next = s;
			flag = 1;
			a = 1;
			std::cout << "正在链表头部插入图书\n";
			break;
		case 2:
			break;
		}
	}
	else flag = 1;
	return flag;
}
