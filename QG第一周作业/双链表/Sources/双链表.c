 #include <stdio.h> 
 #include <stdlib.h>
 


struct Num { //����˫������ 
	long num;
	struct Num *prev;
	struct Num *next;
};

void displayMenu() { 
		printf("\n--- ˫������ ---\n"); 
		printf("1. ��������\n"); 
		printf("2. ��������\n"); 
		printf("3. ��ת����\n"); 
		printf("4. ��ʾ����\n"); 
		printf("5. �ж��Ƿ�ɻ�\n"); 
		printf("6. ɾ������\n"); 
   		printf("7. ��ż��ת\n");
		printf("8. ��������\n"); 
		printf("9. ����ѭ������\n"); 
		printf("10. �˳�����\n"); 
}

void printList(struct Num *head);//������ӡ������ 

struct Num *createList() {//����˫������ 
    struct Num *head, *p1, *p2;
    int n = 0;
    int x, i = 0;
    p1 = p2 = (struct Num *)malloc(sizeof(struct Num));//������ʼ�ڵ� 
    printf("���������ڵ㣺");
    scanf("%d", &x);
    printf("�������%d���ڵ������(���Ȳ���10)", n + 1);
    scanf("%ld", &p1->num);
    head = NULL;
    while (i < x - 1) {
        n = n + 1;
        if (n == 1)//��ʼ�ڵ㣬��ͷ�ڵ�Ϊ�˽ڵ� 
            head = p1;
        else {
            p2->next = p1;
            p1->prev = p2;
        }
        p2 = p1;
        p1 = (struct Num *)malloc(sizeof(struct Num));
        printf("�������%d���ڵ������(���Ȳ���10)", n + 1);
        scanf("%ld", &p1->num);
        i++;
    }
    p2->next = p1;
    p1->prev = p2;
    p1->next = NULL;
    return head;
}


struct Num *insertNode(struct Num *head, long num, int position) { //����ڵ㺯�� 
 	struct Num *newNode = (struct Num *)malloc(sizeof(struct Num)); //��������Ľڵ� 
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
        printf("����λ����Ч��\n");
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


struct Num *reverseList(struct Num *head) {//��ת���� 
    struct Num *temp = NULL;
    struct Num *current = head;

    while (current != NULL) {//��������ͷβָ�뽻�� 
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



void printList(struct Num *head) { //��ӡ˫������Ԫ�� 
 	if (head == NULL) { 
 		printf("����Ϊ�գ�\n"); 
		return; 
	}	
	struct Num *temp = head;
	printf("�����е����ݣ�");
	while (temp != NULL) {		   //�������Ԫ�� 
    	printf("%ld ", temp->num);
    	temp = temp->next;
	}
	printf("\n");
}



int isLoop(struct Num *head) { //�ж��Ƿ�ɻ� 
	if (head == NULL) { 
		return 0; 
	}
	struct Num *slow = head;
	struct Num *fast = head;

	while (fast != NULL && fast->next != NULL) {//����ָ�룬��������ɻ� 
    	slow = slow->next;
    	fast = fast->next->next;
    	if (slow == fast) {
        	return 1;
    	}
	}

	return 0;
}


struct Num *deleteNode(struct Num *head, long num) { //ɾ���ڵ� 
 	struct Num *temp = head;
 	while (temp != NULL && temp->num != num) {		 //�������Ҳ���¼Ҫ�ҽڵ� 
    	temp = temp->next;
	}

	if (temp == NULL) {								 //ѭ����δ�ҵ� 
    	printf("δ�ҵ�Ҫɾ����ѧ�ţ�\n");
    	return head;
	}

	if (temp->prev != NULL) {						 //��ͷ�ڵ����ƿոýڵ� 
    	temp->prev->next = temp->next;
	}
	else {
    	head = temp->next;							 //ɾ��ͷ�ڵ���ֱ��ͷ�ڵ�����һλ 
	}

	if (temp->next != NULL) {						 //�ƿոýڵ�  
    	temp->next->prev = temp->prev;
	}

	free(temp);
	return head;
} 


struct Num *swap(struct Num *head) {				 //��ż��ת 
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


struct Num *searchNode(struct Num *head, long num) { //����Ԫ�� 
 	struct Num *temp = head; 
	while (temp != NULL) { 
		if (temp->num == num) { 
			return temp; 
		} 
		temp = temp->next; 
	} 
	return NULL; 
}


struct Num *createLoopList(struct Num *head) { //����ɻ����� 
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
    	printf("���������ѡ��: ");
    	scanf("%d", &choice);

    	switch (choice) {
    		case 1:
        	head = createList();
        	break;
    	case 2:
        	printf("������Ҫ����λ��(�ڼ�λ����)��");
        	scanf("%d", &position);
      		printf("������Ҫ��������ݣ�");
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
    	        printf("����ɻ�\n");
    	    } else {
    	        printf("�����ɻ�\n");
    	    }
    	    break;
    	case 6:
    	    printf("������Ҫɾ���ĺ��룺");
    	    scanf("%ld", &num);
    	    head = deleteNode(head, num);
    	    break;
    	case 7:
    	    head = swap(head);
    	    break;
    	case 8:
    	    printf("������Ҫ��ѯ�����֣�");
            scanf("%ld", &num);
            struct Num *node = searchNode(head, num);
        	if (node != NULL) {
               printf("�ҵ��ˣ�����Ϊ��%ld\n", node->num);
            } else {
                printf("δ�ҵ���ѧ��\n");
            }
    	    break;
        case 9:
            head = createLoopList(head);
            printf("����ɹ�\n");
            break;
        case 10:
            printf("�˳�����\n");
            exit(0);
            break;
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
