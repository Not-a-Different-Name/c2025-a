
#define NULL 0
#include <stdio.h>
#include <stdlib.h>



struct plate
{
	int value;
	struct plate* next;
	int sign;

}headnum;

void initList(struct plate* p1,int count)
{
	//64point
	for (int i = 2; i <= count; i++)
	{
		//创建一个新结点
		struct plate* p2 = (struct plate*)malloc(sizeof(struct plate));
		//给新结点P的数据域赋值
		p2->sign = i;
		p1->next = p2;
		p1 = p2;
		//将新结点插入表尾
		p2->next = NULL;
		p2->value = rand() % 10;
		printf("%d \t%d\n", p2->value, p2->sign);
	}
	//p1此时为尾结点,p2在局部
}

int free_list(struct plate* head)
{
	struct plate* p = head;
	while (p != NULL)
	{
		struct plate* temp = p;
		p = p->next;
		free(temp);
	}
	return 0;
}


struct plate* invertList(struct plate* p2)
{
	if (p2 == NULL || p2->next == NULL) {
		return p2;  // 空链表或单节点链表无需反转
	}
	//反序
	struct plate* p = NULL;//辅助指针2
	struct plate* next_node = p2->next;//辅助指针1
	//
	while (next_node->next != NULL)
	{
		next_node = p2->next;
		p2->next = p;
		p = p2;
		p2 = next_node;

	}
	next_node->next = p;//p3为新头结点
	/*head->next = NULL;*/
	return next_node;
}

int search_5(struct plate* next_node)
{
	//查找5
	int flag = 0;
	for (struct plate* p = next_node; p->next != NULL; p = p->next)
	{
		if (p->value == 5)
		{
			flag = p->sign;
			break;
		}
	}
	printf("%d \n", flag);
	//输出结果
	if(flag == 0)
	{
		printf("not find 5\n");
		return -1;
	}
	else if (flag != 0)
		printf("find 5 in %d\n", flag);
	return flag;

}


int continue_search_5(struct plate* next_node, int count)
{
	//查找5
	int flag = 0;
	for (struct plate* p = next_node; p->next != NULL; p = p->next)
	{
		if(p->sign >= count)
			continue;
		if (p->value == 5)
		{
			flag = p->sign;
			break;
		}
	}
	printf("%d \n", flag);
	//输出结果
	if (flag == 0)
	{
		printf("not find 5\n");
		return -1;
	}
	else if (flag != 0)
		printf("find 5 in %d\n", flag);
	return flag;

}


int main(void)
{
	headnum.value = 1;
	headnum.next = NULL;
	headnum.sign = 1;
	struct plate* head = &headnum;
	struct plate* next_node = NULL;
	int flag = 0;
	printf("%d \t%d\n", head->value, head->sign);

	initList(head,15);



	printf("------------------------------------------\n");

	head = invertList(head);

	//打印
	for(struct plate* p = head; p != NULL; p = p->next)
	{
		printf("%d \n", p->value);
	}

	printf("------------------------------------------\n");

	flag = search_5(head);
	system("pause");
	continue_search_5(head, flag);


	//释放内存
	free_list(head);
	free(head);
	head = NULL;
	return 0;
}//结尾p2为末项



