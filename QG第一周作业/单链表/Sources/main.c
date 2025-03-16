#include<stdio.h>
#include<stdlib.h>
#define LEN sizeof(struct Num)

struct Num *createList();
void displayMenu();
struct Num *insertNode(struct Num *head, long num, int position);
void printList(struct Num *head);
struct Num *reverseList(struct Num *head); 
int isLoop(struct Num *head); 
struct Num *deleteNode(struct Num *head, long num);
struct Num *swap(struct Num *head); 
struct Num *searchNode(struct Num *head, long num);
struct Num *searchNode(struct Num *head, long num);
struct Num *createLoopList(struct Num *head); 

struct Num
{
    long num;
    struct Num *next;
};
int n;

struct Num *createList() {//创建链表 
    struct Num *head, *p1, *p2;
    n = 0;
    int x=0,i=0;
    p1 = p2 = (struct Num *)malloc(LEN);//开辟节点 
    printf("创建几个节点：");
    scanf("%d",&x);
    printf("请输入第%d个节点的数据(长度不超10)",n+1);
    scanf("%ld", &p1->num);
    head = NULL;
    while (i<x-1) {
        n = n + 1;
        if (n == 1)
            head = p1;
        else
            p2->next = p1;
        p2 = p1;
        p1 = (struct Num *)malloc(LEN);
        printf("请输入第%d个节点的数据(长度不超10)",n+1);
        scanf("%ld", &p1->num);
        i++;
    }
    p2->next = p1;
    p1->next = NULL;
    return head;
}


void displayMenu() {            //打印菜单函数
    printf("1. 初始化链表\n");
    printf("2. 插入新节点\n");
    printf("3. 反转链表\n");
    printf("4. 输出链表\n");
    printf("5. 中间链表\n");
    printf("6. 判断是否成环\n");
    printf("7. 删除节点 \n");
    printf("8. 奇偶反转\n");
    printf("9. 查询链表\n");
    printf("10. 构造循环链表\n");
    printf("11. 退出系统\n");
}

struct Num *insertNode(struct Num *head, long num, int position) {//插入函数 
    // 创建新节点
    struct Num *newNode, *p;
    int i;
    newNode = (struct Num *)malloc(LEN);
    newNode->num = num;
    newNode->next = NULL;
    // 如果链表为空，将新节点设置为头节点
    if (head == NULL) {
        head = newNode;
        return head;
    }
    // 如果插入位置为0，将新节点插入到链表头部
    if (position == 0) {
        newNode->next = head;
        head = newNode;
        return head;
    }
    // 找到插入位置的前一个节点
    p = head;
    for (i = 0; i < position - 1 && p != NULL; i++) {
        p = p->next;
    }
    // 如果p为NULL，说明position超出了链表长度，插入到链表末尾
    if (p == NULL) {
        p = head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newNode;
    } else {
        // 将新节点插入到指定位置
        newNode->next = p->next;
        p->next = newNode;
    }
    return head;
}

struct Num *reverseList(struct Num *head) {//反转链表 
    struct Num *prev, *curr, *next;
    prev = NULL;//前一节点 
    curr = head;//头节点为为尾节点 
    while (curr != NULL) {//当当前节点不为空
        next = curr->next;//保存下一节点 
        curr->next = prev;//将当前节点的next指向前一节点 
        prev = curr;//移动节点 
        curr = next;
    }
    head = prev;
    return head;
}

void printList(struct Num *head) {//打印链表内容 
    struct Num *p;
    p = head;
    if (p == NULL) {
        printf("链表为空！\n");
        return;
    }
    // 使用 p 作为循环条件
    while (p != NULL) {
        printf("%ld ", p->num);
        p = p->next;
    }
    printf("\n");
}

struct Num *findMiddleNode(struct Num *head) {//查找链表中间值 
    struct Num *slow, *fast;
    slow = fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

int isLoop(struct Num *head) {//判断链表是否成环 
    struct Num *slow, *fast;//快指针慢指针 
    slow = fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)//若是能相遇则为成环 
            return 1;
    }
    return 0;
}

struct Num *deleteNode(struct Num *head, long num) {//删除节点 传入头节点和要删除的数 
    struct Num *p, *prev;
    p = head;
    prev = NULL;//记录前一位置 
    while (p != NULL && p->num != num) {//遍历链表直到找到所找元素 
        prev = p;
        p = p->next;
    }
    if (p == NULL) {//遍历完没找到 
        printf("未找到要删除的节点！\n");
        return head;
    }
    if (prev == NULL) {//如果删除头节点 
        head = p->next;
    } else {		  // 制空该节点 
        prev->next = p->next;
    }
    free(p);		  //释放p 
    return head;
}

struct Num *swap(struct Num *head) {//交换奇偶函数 
    struct Num *p2, *p3;//p123分别记录连续三位 
    p2 = p3 = NULL;
    struct Num *p1 = head;
    if (head == NULL || head->next == NULL) {
        return head;	// 如果链表为空或只有一个节点，直接返回
    }
    if (p2 == NULL) {	//第一次交换 目的为交换p1 p2 
        p2 = p1->next;
        p3 = p2->next;
        p1->next = p3;
        p2->next = p1;
        head = p2;		//返回新的头节点 
    }
    while (p1->next != NULL && p1->next->next != NULL) {//当第二次交换到结束为止 当前排位p2 p1 p3 
        p2 = p3;
        p3 = p3->next;	//移位到交换位置
        p1->next = p3;
        p1 = p3;
        p3 = p3->next;
        p1->next = p2;
        p2->next = p3;
        p1 = p2;
    }
    return head;
}

struct Num *searchNode(struct Num *head, long num) {//查找元素函数 
    struct Num *p = head;
    while (p != NULL) {		//遍历查找是否有相同元素 
        if (p->num == num)
            return p;
        p = p->next;
    }
    return NULL;
}

struct Num *createLoopList(struct Num *head) {//成环函数 
    struct Num *p;
    p = head;
    while (p->next != NULL) {	//遍历找到最后一个节点 
        p = p->next;
    }
    p->next = head;				//将最后元素的next指向头节点 
    return head;				//返回头节点 
}

int main() {
    int numStudents = 0;           //统计已录入学生人数
    int choice;                    //菜单选择哪项功能
    struct Num *head = NULL;
    long num;//新插入的数字
	int position;//新插入位置的地址 

    while (1) {
        displayMenu();//打印菜单 
        printf("请输入你的选择: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            head = createList();
            break;
        case 2:
        	printList(head);
			printf("请输入要插入位置(第几位后面)");
			scanf("%d",&position); 
            printf("请输入要插入的内容：");            
            scanf("%ld", &num);
            head = insertNode(head, num,position);//插入数据 
            printList(head);//输出链表 
            break;
        case 3:
            head = reverseList(head);//反转链表 
            printList(head);//输出链表 
            break;
        case 4:
            printList(head);//输出链表 
            break;
        case 5:
            if (head == NULL) {
                printf("链表为空！\n");
            } else {
                struct Num *middle = findMiddleNode(head);
                printf("中间节点的值为：%ld\n", middle->num);
            }
            break;
        case 6:
            if (isLoop(head)) {
                printf("链表成环\n");
            } else {
                printf("链表不成环\n");
            }
            break;
        case 7:
        	printList(head);//输出链表 
            printf("请输入要删除的号码：");
            scanf("%ld", &num);
            head = deleteNode(head, num);
            printList(head);
            break;
        case 8:
            head = swap(head);
            printList(head);
            break;
        case 9:
            printf("请输入要查询的数字：");
            scanf("%ld", &num);
            struct Num *node = searchNode(head, num);
        	if (node != NULL) {
               printf("找到了，数字为：%ld\n", node->num);
            } else {
                printf("未找到该学号\n");
            }
            break;
        case 10:
            head = createLoopList(head);
            printf("构造成功\n");
            break;
        case 11:
            printf("退出程序\n");
            exit(0);
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

