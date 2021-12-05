#include <stdio.h>										
#include <stdlib.h>
#include <string.h>

#define pwd 3848

typedef struct element	// 아래 node구조체 내의 변수중 하나
{
	char phone[20];
	char car_num[20];
}element;
typedef struct node	//node 구조체 정의
{
	struct element data;	//이름,전화번호 데이터
	struct node* next;	//다음 노드를 가리키는 포인터
}node;

//사용되는 함수들
void print_menu(void);
node* createnode(void);	//node하나를 만드는 함수. insert함수의 두번째 인자로 전달하기위해
void insert(node** phead, node* newnode);	//연결리스트의 마지막 node에 newnode를 연결시키는 함수
node* search(node* phead);		//입력한 이름을 가진 node를 찾는 함수
void delete(node** phead, node* remove);	//remove노드를 search함수로 찾아서 인자로 전달한다
void display(node* head);		//연결리스트의 모든 내용을 출력하는 함수
void writefile(node* phead);	//종료시 파일에 연결리스트의 내용을 저장하는 함수
int is_admin(void);


int main()
{
	node* head = NULL;	//헤드 포인터 선언
	int num = 0;
	int in = 0;
	node* se;	   //switch 문의 case 3: 에서 찾은 노드의 주소값을 임시로 저장하기 위해서
	int i = 0;

	FILE* des = fopen("UserInfo.txt", "rt");	//파일의 내용을 기초로 연결리스트 구성을 위해 입력스트림 생성

	if (des == NULL)	//입력스트림의 생성을 확인
	{
		printf("파일 읽기 실패!\n");
		return -1;	//비정상적인 종료를 의미
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
					if (phone[j] == '\n')	//name에 저장된 \n을 0으로 바꿔준다.
						phone[j] = 0;

					if (car_num[j] == '\n')	//phon에 저장된 \n을 0으로 바꿔준다.
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
	/*파일의 내용에서 ':' 이용해서 ':' 다음에 나오는 문자열을 name,phon에 차례대로 넣는다. 그리고
	만들어놓은 새로운 노드에 name,phon을 입력시키고 이 새로운 노드로 연결리스트를 구성한다.*/
	while (1)
	{	

		print_menu();
		printf("   메뉴를 선택하시오 (숫자 입력): ");
		scanf("%d", &num);

		switch (num)		//switch 문을 이용해서 메뉴를 선택.
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
				printf("   전화번호 : %s ", se->data.phone);
				printf("   차량번호 : %s\n", se->data.car_num);
			}
			else
			{
				printf("   일치하는 정보가 없습니다."); printf("\n");
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
	printf("  |           주차 관리 시스템            |\n");
	printf("  |                                       |\n");
	printf("  |                                       |\n");
	printf("  |    1. 주차                            |\n");
	printf("  |    2. 출차                            |\n");
	printf("  |    3. 차량 정보                       |\n");
	printf("  |    4. 관리자                          |\n");
	printf("  |    5. 종료                            |\n");
	printf("  |                                       |\n");
	printf("  |_______________________________________|\n");
	printf("\n");
}



node* createnode(void)
{
	node* newnode = (node*)malloc(sizeof(node));		//새로운 노드 생성
	printf("\n   전화번호:");	scanf("%s", (newnode->data).phone);	//name 입력
	printf("\n   차량번호:");	scanf("%s", (newnode->data).car_num);	//phone 입력
	newnode->next = NULL;
	return newnode;	//newnode 의 주소값을 반환
}
void insert(node** phead, node* newnode)
{
	node* ptr = *phead;
	node* p = NULL;
	if (*phead == NULL)	//연결리스트에 아무 내용이 없을때
	{
		(*phead) = newnode;
		newnode->next = NULL;
	}
	else
	{
		while (ptr != NULL)	//마지막 노드의 주소값을 찾는 반복문
		{
			p = ptr;
			ptr = ptr->next;
		}
		ptr = newnode;
		p->next = ptr;	//연결리스트의 끝에 newnode를 연결
	}
}
node* search(node* phead)
{
	node* ptr = phead;
	element el;
	printf("   전화번호:");	scanf("%s", el.phone);
	while (ptr != NULL)
	{
		if (!strcmp(ptr->data.phone, el.phone))	//각 노드의 데이터 내의 이름과 찾을 이름을 비교
			return ptr;	//찾을 이름을 가진 노드의 주소값을 반환
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
		if (*phead == remove)		//첫번째 노드를 삭제할때
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
					p->next = remove->next;	//remove노드를 연결리스트에서 제외
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
		printf("    전화번호:%s\n", (p->data).phone);
		printf("    차량번호:%s\n\n", (p->data).car_num);
		printf("\n");
		p = p->next;
		i++;
	}
}
void writefile(node* phead)
{
	node* ptr = phead;
	int i = '1';
	FILE* des = fopen("UserInfo.txt", "wt");	//출력 스트림 형성

	if (ptr == NULL)
		return;
	else
	{
		while (ptr != NULL)
		{
			fputc(i, des); fputs("번째\n", des);
			fputs("전화번호:", des); fputs(ptr->data.phone, des); fputs("\n", des);
			fputs("차량번호:", des); fputs(ptr->data.car_num, des); fputs("\n", des);
			ptr = ptr->next;
			i++;
		}
	}
	fclose(des);
	return;
}

int is_admin(void) {

	int num;
	printf("   비밀번호를 입력하세요: ");
	scanf("%d", &num);

	if (num == pwd) {
		return 1;
	}

	else {
		return 0;
	}


}