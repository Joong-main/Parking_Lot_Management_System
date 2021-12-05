#include <stdio.h>										
#include <stdlib.h>
#include <string.h>

#define pwd 3848

typedef struct element	// �Ʒ� node����ü ���� ������ �ϳ�
{
	char phone[20];
	char car_num[20];
}element;
typedef struct node	//node ����ü ����
{
	struct element data;	//�̸�,��ȭ��ȣ ������
	struct node* next;	//���� ��带 ����Ű�� ������
}node;

//���Ǵ� �Լ���
void print_menu(void);
node* createnode(void);	//node�ϳ��� ����� �Լ�. insert�Լ��� �ι�° ���ڷ� �����ϱ�����
void insert(node** phead, node* newnode);	//���Ḯ��Ʈ�� ������ node�� newnode�� �����Ű�� �Լ�
node* search(node* phead);		//�Է��� �̸��� ���� node�� ã�� �Լ�
void delete(node** phead, node* remove);	//remove��带 search�Լ��� ã�Ƽ� ���ڷ� �����Ѵ�
void display(node* head);		//���Ḯ��Ʈ�� ��� ������ ����ϴ� �Լ�
void writefile(node* phead);	//����� ���Ͽ� ���Ḯ��Ʈ�� ������ �����ϴ� �Լ�
int is_admin(void);


int main()
{
	node* head = NULL;	//��� ������ ����
	int num = 0;
	int in = 0;
	node* se;	   //switch ���� case 3: ���� ã�� ����� �ּҰ��� �ӽ÷� �����ϱ� ���ؼ�
	int i = 0;

	FILE* des = fopen("UserInfo.txt", "rt");	//������ ������ ���ʷ� ���Ḯ��Ʈ ������ ���� �Է½�Ʈ�� ����

	if (des == NULL)	//�Է½�Ʈ���� ������ Ȯ��
	{
		printf("���� �б� ����!\n");
		return -1;	//���������� ���Ḧ �ǹ�
	}
	while (feof(des) == 0)
	{
		char ch;
		ch = fgetc(des);
		if (ch == ':')
		{
			char phone[20];
			char car_num[20];
			if (i % 2 == 0)
				fgets(phone, sizeof(phone), des);
			else if (i % 2 == 1)
			{
				int j = 0;
				node* newnode = (node*)malloc(sizeof(node));
				newnode->next = NULL;
				fgets(car_num, sizeof(car_num), des);
				for (j = 0; j < 20; j++)
				{
					if (phone[j] == '\n')	//name�� ����� \n�� 0���� �ٲ��ش�.
						phone[j] = 0;

					if (car_num[j] == '\n')	//phon�� ����� \n�� 0���� �ٲ��ش�.
						car_num[j] = 0;
				}
				strncpy(newnode->data.phone, phone, sizeof(newnode->data.phone));
				strncpy(newnode->data.car_num, car_num, sizeof(newnode->data.car_num));
				insert(&head, newnode);
			}
			i++;
		}
	}
	fclose(des);
	/*������ ���뿡�� ':' �̿��ؼ� ':' ������ ������ ���ڿ��� name,phon�� ���ʴ�� �ִ´�. �׸���
	�������� ���ο� ��忡 name,phon�� �Է½�Ű�� �� ���ο� ���� ���Ḯ��Ʈ�� �����Ѵ�.*/
	while (1)
	{	

		print_menu();
		printf("   �޴��� �����Ͻÿ� (���� �Է�): ");
		scanf("%d", &num);

		switch (num)		//switch ���� �̿��ؼ� �޴��� ����.
		{
		case 1:
			insert(&head, createnode());
			break;
		case 2:
			delete(&head, search(head));
			break;
		case 3:
			se = search(head);
			if (se != NULL)
			{
				printf("   ��ȭ��ȣ : %s ", se->data.phone);
				printf("   ������ȣ : %s\n", se->data.car_num);
			}
			else
			{
				printf("   ��ġ�ϴ� ������ �����ϴ�."); printf("\n");
			}
			break;
		case 4:

			if (is_admin() == 1) {
				display(head);
			}
			break;
		default:
			writefile(head);
			break;
		}
		if (num == 5)
			break;
	}
	return 0;
}






void print_menu(void) {
	printf("   _______________________________________\n");
	printf("  |                                       |\n");
	printf("  |           ���� ���� �ý���            |\n");
	printf("  |                                       |\n");
	printf("  |                                       |\n");
	printf("  |    1. ����                            |\n");
	printf("  |    2. ����                            |\n");
	printf("  |    3. ���� ����                       |\n");
	printf("  |    4. ������                          |\n");
	printf("  |    5. ����                            |\n");
	printf("  |                                       |\n");
	printf("  |_______________________________________|\n");
	printf("\n");
}



node* createnode(void)
{
	node* newnode = (node*)malloc(sizeof(node));		//���ο� ��� ����
	printf("\n   ��ȭ��ȣ:");	scanf("%s", (newnode->data).phone);	//name �Է�
	printf("\n   ������ȣ:");	scanf("%s", (newnode->data).car_num);	//phone �Է�
	newnode->next = NULL;
	return newnode;	//newnode �� �ּҰ��� ��ȯ
}
void insert(node** phead, node* newnode)
{
	node* ptr = *phead;
	node* p = NULL;
	if (*phead == NULL)	//���Ḯ��Ʈ�� �ƹ� ������ ������
	{
		(*phead) = newnode;
		newnode->next = NULL;
	}
	else
	{
		while (ptr != NULL)	//������ ����� �ּҰ��� ã�� �ݺ���
		{
			p = ptr;
			ptr = ptr->next;
		}
		ptr = newnode;
		p->next = ptr;	//���Ḯ��Ʈ�� ���� newnode�� ����
	}
}
node* search(node* phead)
{
	node* ptr = phead;
	element el;
	printf("   ��ȭ��ȣ:");	scanf("%s", el.phone);
	while (ptr != NULL)
	{
		if (!strcmp(ptr->data.phone, el.phone))	//�� ����� ������ ���� �̸��� ã�� �̸��� ��
			return ptr;	//ã�� �̸��� ���� ����� �ּҰ��� ��ȯ
		ptr = ptr->next;
	}
	return NULL;
}
void delete(node** phead, node* remove)
{
	node* ptr = *phead;
	node* p = NULL;
	if (ptr == NULL)
		return;
	else
	{
		if (*phead == remove)		//ù��° ��带 �����Ҷ�
		{
			*phead = (*phead)->next;
			free(remove);
		}
		else
		{
			while (ptr != NULL)
			{
				if (ptr == remove)
				{
					p->next = remove->next;	//remove��带 ���Ḯ��Ʈ���� ����
					free(remove);
					return;
				}
				p = ptr;
				ptr = ptr->next;
			}
		}
	}
}
void display(node* head)
{
	int i = 1;
	node* p = head;
	while (p != NULL)
	{
		printf("\n\n-------------Member List--------------\n");
		printf("%d.\n", i);
		printf("    ��ȭ��ȣ:%s\n", (p->data).phone);
		printf("    ������ȣ:%s\n\n", (p->data).car_num);
		printf("\n");
		p = p->next;
		i++;
	}
}
void writefile(node* phead)
{
	node* ptr = phead;
	int i = '1';
	FILE* des = fopen("UserInfo.txt", "wt");	//��� ��Ʈ�� ����

	if (ptr == NULL)
		return;
	else
	{
		while (ptr != NULL)
		{
			fputc(i, des); fputs("��°\n", des);
			fputs("��ȭ��ȣ:", des); fputs(ptr->data.phone, des); fputs("\n", des);
			fputs("������ȣ:", des); fputs(ptr->data.car_num, des); fputs("\n", des);
			ptr = ptr->next;
			i++;
		}
	}
	fclose(des);
	return;
}

int is_admin(void) {

	int num;
	printf("   ��й�ȣ�� �Է��ϼ���: ");
	scanf("%d", &num);

	if (num == pwd) {
		return 1;
	}

	else {
		return 0;
	}


}