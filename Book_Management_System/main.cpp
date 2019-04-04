#include<iomanip>
#include"FilesOpera.h"
#include"LinkList.h"

int main()
{
	int a, choose;
	bool b = true;
	int count = 1;
	int total;
	std::ofstream writefile;
	std::string ISBNTEMP;
	std::string bknametmp;
	std::string buku;
	Book e;
	DuLinkList L = nullptr, p = nullptr;
	std::cout << "请输入你所需功能的数字编号\n";
	std::cout << "1.  新建图书信息列表\n";
	std::cout << "2.  从 book.txt 中读取图书信息\n";
	std::cout << "3.  新增图书信息\n";
	std::cout << "4.  修改图书信息\n";
	std::cout << "5.  删除图书信息\n";
	std::cout << "6.  按价格升序重排图书信息\n";
	std::cout << "7.  按书名模糊检索图书\n";
	std::cout << "8.  出借图书\n";
	std::cout << "9.  归还图书\n";
	std::cout << "10. 输出现有图书信息\n";
	std::cout << "11. 存盘现有图书信息\n";
	std::cout << "0.  退出系统\n\n";

	choose = -1;
	while (choose != 0)
	{
		std::cout << "你处于主菜单中，请选择:";
		std::cin >> choose;
		switch (choose)
		{
		case 1: //建立一个双向链表
			if (InitDuList_L(L))
				std::cout << "成功建立图书信息存储列表，存储结构为双向链表!\n\n";
			break;
		case 2: //使用后插法创建双向链表
			CreateDuList_L(L);
			std::cout << "读取 book.txt 信息完毕\n\n";
			break;
		case 3: //双向链表的插入
			std::cout << "请输入新增图书的信息:\n";
			std::cout << "请输入插入的位置:"; std::cin >> a;
			while (std::cin.fail())           //判断cin是否failbit，即输入了非整型数据
			{
				std::cin.clear();             //是则置空并清除缓冲区，以免死循环
				std::cin.ignore();
				if (b)                        //b作为标记，仅让提示输出一次
				{
					std::cout << "位置非法，请重新输入:"; b = 0;
				}
				std::cin >> a;
			}
			std::cout << "请输入ISBN号："; std::cin >> e.id;// >> e.name >> e.price >> e.number;
			std::cout << "请输入书名："; std::cin >> e.name;
			std::cout << "请输入价格："; std::cin >> e.price;
			std::cout << "请输入数量："; std::cin >> e.number;
			if (ListInsert_DuL(L, a, e))
				std::cout << "新增图书信息成功.\n\n";
			else
				std::cout << "新增图书信息失败!\n\n";
			break;
		case 4: //修改图书信息
			std::cout << "请输入你要修改的图书的ISBN号:";
			std::cin >> ISBNTEMP;
			p = ISBNcompare(L, ISBNTEMP);
			if (p)
			{
				std::cout << "检索成功，当前书名为：《" << p->data.name << "》\t" << "当前价格为：" << p->data.price << std::endl;
				std::cout << "请输入新价格：";
				int pricetemp;
				std::cin >> pricetemp;
				p = FixInfor(p, pricetemp);
				std::cout << "修改成功，当前价格为：" << p->data.price << std::endl;
			}
			else {
				std::cout << "未检索到你所要的图书，请重新核实\n";
				break;
			}
			break;
		case 5: //双向链表的删除
			std::cout << "请输入所要删除的图书的位置:";
			std::cin >> a;
			if (ListDelete_DuL(L, a))
				std::cout << "删除成功!\n\n";
			else
				std::cout << "删除失败!\n\n";
			break;
		case 6://按价格排序图书
			std::cout << "以价格升序重排列图书\n";
			//			DuLinkList y;
			Sort_books_prince(L);
			if (L)
				std::cout << "排序成功!!\n";
			else
				std::cout << "不好意思，目前任何图书信息\n";
			break;
		case 7: //检索图书
			std::cout << "请输入一个关键字以检索图书（不含空格）:";
			std::cin >> bknametmp;
			FindBk(L, bknametmp);
			break;
		case 8://出借图书
			std::cout << "请输入您想要借的书的序号:" << std::endl;
			int n; int store_num;
			std::cin >> n;
			store_num = Search_book(L, n);
			if (store_num == -1)
			{
				std::cout << "您的序号超范围！\n" << std::endl;
				break;
			}
			else if (store_num != 0)
				std::cout << "本书库存为：\n" << store_num << std::endl;
			else
			{
				std::cout << "本书库存为零\n" << std::endl;
				break;
			}
			std::cout << "您想借的数量：" << std::endl;
			int shu;
			std::cin >> shu;
			Change_store(L, n, shu);
			break;
		case 9:// 归还图书
			std::cout << "请输入您要归还的书的ISBN号" << std::endl;
			std::cin >> buku;
			total = 0;
			std::cout << "请输入您要归还的书的数量" << std::endl;
			std::cin >> total;
			Return_book(L, buku, total);
		case 10://双向链表的输出
			std::cout << "当前图书系统信息输出:\n";
			std::cout << "序号" << "\t" << std::left << std::setw(15) << "ISBN号" << std::left << std::setw(50) << "书名" << "\t" << std::left << std::setw(5) << "价格" << "\t" << std::left << std::setw(15) << "数量" << std::endl;
			//L = new DuLinkList;
			p = L->next;
			count = 0;
			while (p)
			{
				//count = 1;
				std::cout << ++count << ")" << "\t" << std::left << std::setw(15) << p->data.id << "\t" << std::left << std::setw(50) << p->data.name << "\t" << std::left << std::setw(5) << p->data.price << "\t" << std::left << std::setw(5) << p->data.number << std::endl;
				std::cout << "----------------------------------------------------------------------------------------------" << std::endl;
				p = p->next;
			}
			p = Total(L);
			std::cout << std::left << std::setw(15) << "总计" << std::left << std::setw(50) << "   " << "\t\t" << std::left << std::setw(5) << p->data.price << "\t" << std::left << std::setw(15) << p->data.number << std::endl;
			std::cout << std::endl;
			break;
		case 11://双向链表的写文件
			writefile.open("new book.txt");
			std::cout << "图书系统正在进行信息输出:\n";
			writefile << "当前图书系统信息输出:\n";
			writefile << "序号" << "\t" << std::left << std::setw(15) << "ISBN号" << std::left << std::setw(50) << "书名" << "\t" << std::left << std::setw(5) << "价格" << "\t" << std::left << std::setw(15) << "数量" << std::endl;
			//L = new DuLinkList;
			p = L->next;
			count = 0;
			while (p)
			{
				//count = 1;
				writefile << ++count << ")" << "\t" << std::left << std::setw(15) << p->data.id << "\t" << std::left << std::setw(50) << p->data.name << "\t" << std::left << std::setw(5) << p->data.price << "\t" << std::left << std::setw(5) << p->data.number << std::endl;
				writefile << "----------------------------------------------------------------------------------------------" << std::endl;
				p = p->next;
			}
			p = Total(L);
			writefile << std::left << std::setw(15) << "总计" << std::left << std::setw(50) << "   " << "\t\t" << std::left << std::setw(5) << p->data.price << "\t" << std::left << std::setw(15) << p->data.number << std::endl;
			std::cout << std::endl;
			writefile << std::endl;
			writefile.close();
			std::cout << "图书系统输出完成\n";
			break;
		}
	}
	return 0;
}


