#include<iomanip>
#include"FilesOpera.h"
#include"LinkList.h"


int main() {
	int a, choose;
	string ISBNTEMP;
	Book e;
	DuLinkList L = nullptr,p = nullptr;
	cout << "请输入你所需功能的数字编号\n";
	cout << "1. 建立图书信息存储列表\n";
	cout << "2. 从 book.txt 中读取图书信息\n";
	cout << "3. 新增图书信息\n";
	cout << "4. 修改图书信息\n";
	cout << "5. 删除图书信息\n";
	cout << "6. 对图书信息进行重排序(价格升序)\n";
	cout << "7. 输出现有图书信息(含价格及数量统计)\n";
	cout << "0. 退出系统\n\n";

	choose = -1;
	while (choose != 0) {

		cout << "你处于主菜单中，请选择:";
		cin >> choose;
		switch (choose) {
		case 1: //建立一个双向链表
			if (InitDuList_L(L))
				cout << "成功建立图书信息存储列表，存储结构为双向链表!\n\n";
			break;
		case 2: //使用后插法创建双向链表
			CreateDuList_L(L);
			cout << "读取 book.txt 信息完毕\n\n";
			break;
		case 3: //双向链表的插入
			cout << "请输入两个数分别代表插入的位置和数值（书的信息：ISBN号 书名 价格 数量）:";
			cin >> a;
			cin >> e.id >> e.name >> e.price >> e.number;
			if (ListInsert_DuL(L, a, e))
				cout << "新增图书信息成功.\n\n";
			else
				cout << "新增图书信息失败!\n\n";
			break;
		case 4: //修改图书信息
			cout << "请输入你要修改的书的ISBN号:";
			cin >> ISBNTEMP;
			p = ISBNcompare(L, ISBNTEMP);
			if (p)
			{
				cout << "检索成功，当前书名为：《" << p->data.name << "》\t" << "当前价格为：" << p->data.price << endl;
				cout << "请输入新价格：";
				int pricetemp;
				cin >> pricetemp;
				p = FixInfor(p, pricetemp);
				cout << "修改成功，当前价格为：" << p->data.price << endl;
			}
			else {
				cout << "未检索到你所要的书目，请重新核实\n";
				break;
			}
			break;
		case 5: //双向链表的删除
			cout << "请输入所要删除的书籍的位置:";
			cin >> a;
			if (ListDelete_DuL(L, a))
				cout << "删除成功!\n\n";
			else
				cout << "删除失败!\n\n";
			break;

		case 6:
			cout << "对图书信息进行重排序(价格升序)\n";
			//			DuLinkList y;
			sort_books_prince(L);

			if (L)
				cout << "排序成功!!!!!\n";
			else
				cout << "不好意思，图书馆里没有书";
			break;
		case 7: //双向链表的输出
			cout << "当前图书系统信息输出:\n";
			cout << left<<"序号"<<"\t"<<left << setw(15) << "ISBN号" << left << setw(50) << "书名" << "\t" << left << setw(5) << "价格" << "\t" << left << setw(15) << "数量" << endl;
			//L = new DuLinkList;
			p = L->next;
			int count = 1;
			while (p) {
				cout <<left<<count++<<")"<<"\t"<<left << setw(15) << p->data.id << "\t" << left << setw(50) << p->data.name << "\t" << left << setw(5) << p->data.price << "\t" << left << setw(5) << p->data.number << endl;
				p = p->next;
			}
			p = Total(L);
			cout << left << setw(15) << "总计" << left << setw(50) << " " << "\t\t" << left << setw(5) << p->data.price << "\t" << left << setw(15) << p->data.number << endl;
			cout << endl;
			break;
		}
	}
	return 0;
}

