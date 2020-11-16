#include "ContactBook.h"

void Test1()
{
	ContactBook cb;
	ContactInit(&cb);

	Contact ct = { "小李", 18, "18516283075", "西科大 宿舍-3号楼-601" };
	ContactAdd(&cb, ct);
}

enum OPTION
{
	QUIT = 0,
	ADD = 1,
	SEARCH = 2,
	DEL = 3,
	UPDATE = 4,
	SAVE = 5,
	PRINT = 6,
};

void ContackBookMenu()
{
	Contact ct;
	ContactBook cb;
	char name[NAME_MAX];
	ContactInit(&cb);

	/*Contact ct1 = { "武松", 18, "18516283076", "西工程 宿舍-3号楼-601" };
	Contact ct2 = { "宋江", 20, "18516283077", "西科大 宿舍-3号楼-602" };
	Contact ct3 = { "李逵", 25, "18516283078", "西科大 宿舍-3号楼-603" };

	ContactInit(&cb);
	ContactAdd(&cb, ct1);
	ContactAdd(&cb, ct2);
	ContactAdd(&cb, ct3);*/

	//ContactBookLoadText(&cb);
	ContactBookLoadBin(&cb);
	int option;
	do{
		printf("********************************************\n");
		printf("1、添加联系人 2、查找联系人\n");
		printf("3、删除联系人 4、修改联系人\n");
		printf("5、保存到文件 6、打印\n");
		printf("0、退出\n");
		printf("请选择：");
		scanf("%d", &option);
		printf("********************************************\n");

		switch (option)
		{
		case ADD:
			printf("请依次输入姓名 年龄 电话号码 地址：\n");
			scanf("%s", ct.name);
			scanf("%d", &ct.age);
			scanf("%s", ct.tel);
			scanf("%s", ct.addr);
			ContactAdd(&cb, ct);
			break;
		case SEARCH:
			printf("请输入要查找人的名字:");
			scanf("%s", name);
			Contact* pct = ContactSearch(&cb, name);
			if (pct == NULL)
			{
				printf("无此联系人\n");
			}
			else
			{
				printf("姓名：%s\n", pct->name);
				printf("年龄：%d\n", pct->age);
				printf("电话：%s\n", pct->tel);
				printf("地址：%s\n", pct->addr);
			}
			break;
		case DEL:
			printf("请输入要删除人的名字:");
			scanf("%s", name);
			ContactDel(&cb, name);
			break;
		case UPDATE:
			printf("1、更新名字  2、更新电话\n");
			printf("3、更新年龄  4、更新地址\n");
			printf("请选择：");
			//scanf("%c", &ch);
			scanf("%d", &option);
			if (option == 2)
			{
				char name[NAME_MAX];
				char tel[TEL_MAX];
				printf("请输入你要更新名字及电话:\n");
				scanf("%s", name);
				scanf("%s", tel);
				ContactUpdateTel(&cb, name, tel);
			}
			break;
		case QUIT:
			break;
		case SAVE:
			ContactBookSaveBin(&cb);
			break;
		case PRINT:
			ContactBookPrint(&cb);
			break;
		default:
			printf("没有此选项，请重新选择\n");
			break;
		}
	} while (option != 0);
}

void Test2()
{
	ContactBook cb;
	ContactInit(&cb);
	Contact ct = { "武松", 18, "18516283076", "西工程 宿舍-3号楼-601" };
	for (int i = 0; i < 501; ++i)
	{
		ct.age = i;
		ContactAdd(&cb, ct);
	}

	ContactBookPrint(&cb);
}

int main()
{
	//Test1();
	//ContackBookMenu();
	//Test2();

	//FILE* fin = fopen("contact_book.bin", "wb");
	//if (fin == NULL)
	//{
	//	printf("打开文件失败:%s\n", strerror(errno));
	//	exit(-1);
	//}

	//int i = 4;
	//fprintf(fin, "%d\n", i);
	//fwrite(&i, sizeof(int), 1, fin);

	//fclose(fin);
	//getchar();

	return 0;
}