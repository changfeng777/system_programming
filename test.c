#include "ContactBook.h"

void Test1()
{
	ContactBook cb;
	ContactInit(&cb);

	Contact ct = { "С��", 18, "18516283075", "���ƴ� ����-3��¥-601" };
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

	/*Contact ct1 = { "����", 18, "18516283076", "������ ����-3��¥-601" };
	Contact ct2 = { "�ν�", 20, "18516283077", "���ƴ� ����-3��¥-602" };
	Contact ct3 = { "����", 25, "18516283078", "���ƴ� ����-3��¥-603" };

	ContactInit(&cb);
	ContactAdd(&cb, ct1);
	ContactAdd(&cb, ct2);
	ContactAdd(&cb, ct3);*/

	//ContactBookLoadText(&cb);
	ContactBookLoadBin(&cb);
	int option;
	do{
		printf("********************************************\n");
		printf("1�������ϵ�� 2��������ϵ��\n");
		printf("3��ɾ����ϵ�� 4���޸���ϵ��\n");
		printf("5�����浽�ļ� 6����ӡ\n");
		printf("0���˳�\n");
		printf("��ѡ��");
		scanf("%d", &option);
		printf("********************************************\n");

		switch (option)
		{
		case ADD:
			printf("�������������� ���� �绰���� ��ַ��\n");
			scanf("%s", ct.name);
			scanf("%d", &ct.age);
			scanf("%s", ct.tel);
			scanf("%s", ct.addr);
			ContactAdd(&cb, ct);
			break;
		case SEARCH:
			printf("������Ҫ�����˵�����:");
			scanf("%s", name);
			Contact* pct = ContactSearch(&cb, name);
			if (pct == NULL)
			{
				printf("�޴���ϵ��\n");
			}
			else
			{
				printf("������%s\n", pct->name);
				printf("���䣺%d\n", pct->age);
				printf("�绰��%s\n", pct->tel);
				printf("��ַ��%s\n", pct->addr);
			}
			break;
		case DEL:
			printf("������Ҫɾ���˵�����:");
			scanf("%s", name);
			ContactDel(&cb, name);
			break;
		case UPDATE:
			printf("1����������  2�����µ绰\n");
			printf("3����������  4�����µ�ַ\n");
			printf("��ѡ��");
			//scanf("%c", &ch);
			scanf("%d", &option);
			if (option == 2)
			{
				char name[NAME_MAX];
				char tel[TEL_MAX];
				printf("��������Ҫ�������ּ��绰:\n");
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
			printf("û�д�ѡ�������ѡ��\n");
			break;
		}
	} while (option != 0);
}

void Test2()
{
	ContactBook cb;
	ContactInit(&cb);
	Contact ct = { "����", 18, "18516283076", "������ ����-3��¥-601" };
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
	//	printf("���ļ�ʧ��:%s\n", strerror(errno));
	//	exit(-1);
	//}

	//int i = 4;
	//fprintf(fin, "%d\n", i);
	//fwrite(&i, sizeof(int), 1, fin);

	//fclose(fin);
	//getchar();

	return 0;
}