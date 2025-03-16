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

struct Num *createList() {//�������� 
    struct Num *head, *p1, *p2;
    n = 0;
    int x=0,i=0;
    p1 = p2 = (struct Num *)malloc(LEN);//���ٽڵ� 
    printf("���������ڵ㣺");
    scanf("%d",&x);
    printf("�������%d���ڵ������(���Ȳ���10)",n+1);
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
        printf("�������%d���ڵ������(���Ȳ���10)",n+1);
        scanf("%ld", &p1->num);
        i++;
    }
    p2->next = p1;
    p1->next = NULL;
    return head;
}


void displayMenu() {            //��ӡ�˵�����
    printf("1. ��ʼ������\n");
    printf("2. �����½ڵ�\n");
    printf("3. ��ת����\n");
    printf("4. �������\n");
    printf("5. �м�����\n");
    printf("6. �ж��Ƿ�ɻ�\n");
    printf("7. ɾ���ڵ� \n");
    printf("8. ��ż��ת\n");
    printf("9. ��ѯ����\n");
    printf("10. ����ѭ������\n");
    printf("11. �˳�ϵͳ\n");
}

struct Num *insertNode(struct Num *head, long num, int position) {//���뺯�� 
    // �����½ڵ�
    struct Num *newNode, *p;
    int i;
    newNode = (struct Num *)malloc(LEN);
    newNode->num = num;
    newNode->next = NULL;
    // �������Ϊ�գ����½ڵ�����Ϊͷ�ڵ�
    if (head == NULL) {
        head = newNode;
        return head;
    }
    // �������λ��Ϊ0�����½ڵ���뵽����ͷ��
    if (position == 0) {
        newNode->next = head;
        head = newNode;
        return head;
    }
    // �ҵ�����λ�õ�ǰһ���ڵ�
    p = head;
    for (i = 0; i < position - 1 && p != NULL; i++) {
        p = p->next;
    }
    // ���pΪNULL��˵��position�����������ȣ����뵽����ĩβ
    if (p == NULL) {
        p = head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newNode;
    } else {
        // ���½ڵ���뵽ָ��λ��
        newNode->next = p->next;
        p->next = newNode;
    }
    return head;
}

struct Num *reverseList(struct Num *head) {//��ת���� 
    struct Num *prev, *curr, *next;
    prev = NULL;//ǰһ�ڵ� 
    curr = head;//ͷ�ڵ�ΪΪβ�ڵ� 
    while (curr != NULL) {//����ǰ�ڵ㲻Ϊ��
        next = curr->next;//������һ�ڵ� 
        curr->next = prev;//����ǰ�ڵ��nextָ��ǰһ�ڵ� 
        prev = curr;//�ƶ��ڵ� 
        curr = next;
    }
    head = prev;
    return head;
}

void printList(struct Num *head) {//��ӡ�������� 
    struct Num *p;
    p = head;
    if (p == NULL) {
        printf("����Ϊ�գ�\n");
        return;
    }
    // ʹ�� p ��Ϊѭ������
    while (p != NULL) {
        printf("%ld ", p->num);
        p = p->next;
    }
    printf("\n");
}

struct Num *findMiddleNode(struct Num *head) {//���������м�ֵ 
    struct Num *slow, *fast;
    slow = fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

int isLoop(struct Num *head) {//�ж������Ƿ�ɻ� 
    struct Num *slow, *fast;//��ָ����ָ�� 
    slow = fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)//������������Ϊ�ɻ� 
            return 1;
    }
    return 0;
}

struct Num *deleteNode(struct Num *head, long num) {//ɾ���ڵ� ����ͷ�ڵ��Ҫɾ������ 
    struct Num *p, *prev;
    p = head;
    prev = NULL;//��¼ǰһλ�� 
    while (p != NULL && p->num != num) {//��������ֱ���ҵ�����Ԫ�� 
        prev = p;
        p = p->next;
    }
    if (p == NULL) {//������û�ҵ� 
        printf("δ�ҵ�Ҫɾ���Ľڵ㣡\n");
        return head;
    }
    if (prev == NULL) {//���ɾ��ͷ�ڵ� 
        head = p->next;
    } else {		  // �ƿոýڵ� 
        prev->next = p->next;
    }
    free(p);		  //�ͷ�p 
    return head;
}

struct Num *swap(struct Num *head) {//������ż���� 
    struct Num *p2, *p3;//p123�ֱ��¼������λ 
    p2 = p3 = NULL;
    struct Num *p1 = head;
    if (head == NULL || head->next == NULL) {
        return head;	// �������Ϊ�ջ�ֻ��һ���ڵ㣬ֱ�ӷ���
    }
    if (p2 == NULL) {	//��һ�ν��� Ŀ��Ϊ����p1 p2 
        p2 = p1->next;
        p3 = p2->next;
        p1->next = p3;
        p2->next = p1;
        head = p2;		//�����µ�ͷ�ڵ� 
    }
    while (p1->next != NULL && p1->next->next != NULL) {//���ڶ��ν���������Ϊֹ ��ǰ��λp2 p1 p3 
        p2 = p3;
        p3 = p3->next;	//��λ������λ��
        p1->next = p3;
        p1 = p3;
        p3 = p3->next;
        p1->next = p2;
        p2->next = p3;
        p1 = p2;
    }
    return head;
}

struct Num *searchNode(struct Num *head, long num) {//����Ԫ�غ��� 
    struct Num *p = head;
    while (p != NULL) {		//���������Ƿ�����ͬԪ�� 
        if (p->num == num)
            return p;
        p = p->next;
    }
    return NULL;
}

struct Num *createLoopList(struct Num *head) {//�ɻ����� 
    struct Num *p;
    p = head;
    while (p->next != NULL) {	//�����ҵ����һ���ڵ� 
        p = p->next;
    }
    p->next = head;				//�����Ԫ�ص�nextָ��ͷ�ڵ� 
    return head;				//����ͷ�ڵ� 
}

int main() {
    int numStudents = 0;           //ͳ����¼��ѧ������
    int choice;                    //�˵�ѡ�������
    struct Num *head = NULL;
    long num;//�²��������
	int position;//�²���λ�õĵ�ַ 

    while (1) {
        displayMenu();//��ӡ�˵� 
        printf("���������ѡ��: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            head = createList();
            break;
        case 2:
        	printList(head);
			printf("������Ҫ����λ��(�ڼ�λ����)");
			scanf("%d",&position); 
            printf("������Ҫ��������ݣ�");            
            scanf("%ld", &num);
            head = insertNode(head, num,position);//�������� 
            printList(head);//������� 
            break;
        case 3:
            head = reverseList(head);//��ת���� 
            printList(head);//������� 
            break;
        case 4:
            printList(head);//������� 
            break;
        case 5:
            if (head == NULL) {
                printf("����Ϊ�գ�\n");
            } else {
                struct Num *middle = findMiddleNode(head);
                printf("�м�ڵ��ֵΪ��%ld\n", middle->num);
            }
            break;
        case 6:
            if (isLoop(head)) {
                printf("����ɻ�\n");
            } else {
                printf("�����ɻ�\n");
            }
            break;
        case 7:
        	printList(head);//������� 
            printf("������Ҫɾ���ĺ��룺");
            scanf("%ld", &num);
            head = deleteNode(head, num);
            printList(head);
            break;
        case 8:
            head = swap(head);
            printList(head);
            break;
        case 9:
            printf("������Ҫ��ѯ�����֣�");
            scanf("%ld", &num);
            struct Num *node = searchNode(head, num);
        	if (node != NULL) {
               printf("�ҵ��ˣ�����Ϊ��%ld\n", node->num);
            } else {
                printf("δ�ҵ���ѧ��\n");
            }
            break;
        case 10:
            head = createLoopList(head);
            printf("����ɹ�\n");
            break;
        case 11:
            printf("�˳�����\n");
            exit(0);
        default:
            printf("��Ч��ѡ������������\n");
        }
        fflush(stdin);//��������� 
        printf("�밴�س�������......");
        getchar();
        system("cls"); // ��������
    }

    return 0;
}

