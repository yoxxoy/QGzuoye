 #include <stdio.h> 
 #include <stdlib.h>
 


struct Num { //创建双向链表 
	long num;
	struct Num *prev;
	struct Num *next;
};

void displayMenu() { 
		printf("\n--- 双向链表 ---\n"); 
		printf("1. 创建链表\n"); 
		printf("2. 插入数据\n"); 
		printf("3. 反转链表\n"); 
		printf("4. 显示链表\n"); 
		printf("5. 判断是否成环\n"); 
		printf("6. 删除数据\n"); 
   		printf("7. 奇偶反转\n");
		printf("8. 查找数据\n"); 
		printf("9. 构造循环链表\n"); 
		printf("10. 退出程序\n"); 
}

void printList(struct Num *head);//声明打印链表函数 

struct Num *createList() {//创建双向链表 
    struct Num *head, *p1, *p2;
    int n = 0;
    int x, i = 0;
    p1 = p2 = (struct Num *)malloc(sizeof(struct Num));//创建初始节点 
    printf("创建几个节点：");
    scanf("%d", &x);
    printf("请输入第%d个节点的数据(长度不超10)", n + 1);
    scanf("%ld", &p1->num);
    head = NULL;
    while (i < x - 1) {
        n = n + 1;
        if (n == 1)//初始节点，则头节点为此节点 
            head = p1;
        else {
            p2->next = p1;
            p1->prev = p2;
        }
        p2 = p1;
        p1 = (struct Num *)malloc(sizeof(struct Num));
        printf("请输入第%d个节点的数据(长度不超10)", n + 1);
        scanf("%ld", &p1->num);
        i++;
    }
    p2->next = p1;
    p1->prev = p2;
    p1->next = NULL;
    return head;
}


struct Num *insertNode(struct Num *head, long num, int position) { //插入节点函数 
 	struct Num *newNode = (struct Num *)malloc(sizeof(struct Num)); //创建插入的节点 
	newNode->num = num; 
	newNode->prev = NULL; 
	newNode->next = NULL;
	if (position == 0) {
    	newNode->next = head;
    if (head != NULL) {
        head->prev = newNode;
    }
    head = newNode;
	} 
	else {
    struct Num *temp = head;
    int i;
    for (i = 0; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("插入位置无效！\n");
        free(newNode);
        return head;
    }
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
	}
	return head;
} 


struct Num *reverseList(struct Num *head) {//反转链表 
    struct Num *temp = NULL;
    struct Num *current = head;

    while (current != NULL) {//遍历链表，头尾指针交换 
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if (temp != NULL) {
        head = temp->prev;
    }

    return head;
}



void printList(struct Num *head) { //打印双向链表元素 
 	if (head == NULL) { 
 		printf("链表为空！\n"); 
		return; 
	}	
	struct Num *temp = head;
	printf("链表中的数据：");
	while (temp != NULL) {		   //遍历输出元素 
    	printf("%ld ", temp->num);
    	temp = temp->next;
	}
	printf("\n");
}



int isLoop(struct Num *head) { //判断是否成环 
	if (head == NULL) { 
		return 0; 
	}
	struct Num *slow = head;
	struct Num *fast = head;

	while (fast != NULL && fast->next != NULL) {//快慢指针，若相遇则成环 
    	slow = slow->next;
    	fast = fast->next->next;
    	if (slow == fast) {
        	return 1;
    	}
	}

	return 0;
}


struct Num *deleteNode(struct Num *head, long num) { //删除节点 
 	struct Num *temp = head;
 	while (temp != NULL && temp->num != num) {		 //遍历查找并记录要找节点 
    	temp = temp->next;
	}

	if (temp == NULL) {								 //循环完未找到 
    	printf("未找到要删除的学号！\n");
    	return head;
	}

	if (temp->prev != NULL) {						 //非头节点则制空该节点 
    	temp->prev->next = temp->next;
	}
	else {
    	head = temp->next;							 //删除头节点则直接头节点下移一位 
	}

	if (temp->next != NULL) {						 //制空该节点  
    	temp->next->prev = temp->prev;
	}

	free(temp);
	return head;
} 


struct Num *swap(struct Num *head) {				 //奇偶反转 
	if (head == NULL || head->next == NULL) { 
		return head; 
	}
	struct Num *prev = NULL;
	struct Num *current = head;

	while (current != NULL && current->next != NULL) {
    	struct Num *nextNode = current->next;
    	current->next = nextNode->next;
    	nextNode->next = current;
    	if (prev != NULL) {
        	prev->next = nextNode;
    	} 
		else {
        	head = nextNode;
    	}
    	nextNode->prev = prev;
    	current->prev = nextNode;
    	if (current->next != NULL) {
        	current->next->prev = current;
    	}
    	prev = current;
    	current = current->next;
	}
	return head;
}


struct Num *searchNode(struct Num *head, long num) { //查找元素 
 	struct Num *temp = head; 
	while (temp != NULL) { 
		if (temp->num == num) { 
			return temp; 
		} 
		temp = temp->next; 
	} 
	return NULL; 
}


struct Num *createLoopList(struct Num *head) { //构造成环链表 
	if (head == NULL) { 
		return head; 
	}
	struct Num *temp = head;
	while (temp->next != NULL) {
    	temp = temp->next;
	}
	temp->next = head;
	head->prev = temp;
	return head;
}


int main() { 
	int numStudents = 0; 
	int choice; 
	struct Num *head = NULL; 
	long num; 
	int position;
	while (1) {
    	displayMenu();
    	printf("请输入你的选择: ");
    	scanf("%d", &choice);

    	switch (choice) {
    		case 1:
        	head = createList();
        	break;
    	case 2:
        	printf("请输入要插入位置(第几位后面)：");
        	scanf("%d", &position);
      		printf("请输入要插入的内容：");
       		scanf("%ld", &num);
        	head = insertNode(head, num, position);
        	break;
    	case 3:
    	    head = reverseList(head);
    	    break;
    	case 4:
    	    printList(head);
    	    break;
    	case 5:
    	    if (isLoop(head)) {
    	        printf("链表成环\n");
    	    } else {
    	        printf("链表不成环\n");
    	    }
    	    break;
    	case 6:
    	    printf("请输入要删除的号码：");
    	    scanf("%ld", &num);
    	    head = deleteNode(head, num);
    	    break;
    	case 7:
    	    head = swap(head);
    	    break;
    	case 8:
    	    printf("请输入要查询的数字：");
            scanf("%ld", &num);
            struct Num *node = searchNode(head, num);
        	if (node != NULL) {
               printf("找到了，数字为：%ld\n", node->num);
            } else {
                printf("未找到该学号\n");
            }
    	    break;
        case 9:
            head = createLoopList(head);
            printf("构造成功\n");
            break;
        case 10:
            printf("退出程序\n");
            exit(0);
            break;
        default:
            printf("无效的选择，请重新输入\n");
        }
        fflush(stdin);//清除缓冲区 
        printf("请按回车键继续......");
        getchar();
        system("cls"); // 清屏操作
    }

    return 0;
}
