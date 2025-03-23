#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  	//������ 
#include <string.h>
#include <ctype.h>		//�ж��Ƿ�Ϊ���� 

#define MAX_SIZE 100

typedef struct Node{	//�������� 
	int date;			//������������ 
	struct Node* next;   
}Node; 

typedef struct Stack {  //����ջ 
	Node* top;			//ջ����ַ 
	int size;			//Ԫ������ 
}Stack;

Stack* creatStack(){	 //ָ�뺯�������ص�ַ��������ջ���� 
	Stack* stack=(Stack*)malloc(sizeof(Stack));//���ٿռ� 
	stack->top=NULL;						   //��Ϊ�� 
	stack->size=0;
	return stack;							   //����ջ�ĵ�ַ 
}

bool isEmpty(Stack* stack){//���ջ�Ƿ�Ϊ�� 
	return stack->size==0; //Ϊ�շ���true������Ϊfalse 
}

bool isFull(Stack* stack){//���ջ�Ƿ�װ�� 
	return stack->size==MAX_SIZE;
}

void push(Stack* stack,int date){//ѹ������ 
	if(isFull(stack)){	  //�ж�ջ�Ƿ��� 
		printf("Stack is full\n");
		return;
	}
	Node* newNode=(Node*)malloc(sizeof(Node)); //�����½ڵ� 
	newNode->date=date;						   //�洢���� 
	newNode->next=stack->top;				   //���½ڵ��nextָ��ջ�� 
	stack->top=newNode;						   //��ջ��ָ���½ڵ� 
	stack->size++;
}

int pop(Stack* stack){	//���ջ��Ԫ�� 
	if(isEmpty(stack)){
		printf("Stack is empty\n");
		return -1;
	}
	Node* temp=stack->top;//�����������ջ��Ҫ��ȡԪ�� 
	int date =temp->date; //��ȡԪ������ 
	stack->top=temp->next;//����ջ�� 
	free(temp);			  //�ͷ��ڴ� 
	stack->size--;
	return date;
}

int peek(Stack* stack){//��ȡջ��Ԫ�أ�����ջ 
	if (isEmpty(stack)) {  // ���ջΪ�գ������ʾ��Ϣ������-1
        printf("Stack is empty\n");
        return -1;
    }
    return stack->top->date;
}

void destroyStack(Stack* stack){//�ݻ�ջ���ͷ��ڴ� 
	while(!isEmpty(stack)){
		pop(stack);
	}
	free(stack);
}

int precedence(char op){ //�Զ����������ȼ� 
	if(op=='+'||op=='-')
		return 1;
	if(op=='*'||op=='/')
		return 2;
	return 0;
}

int applyOperator(int a,int b,char op){//������������㺯�� 
	switch(op){
		case '+':
			return a+b;
		case '-' :
			return a-b;
		case '*' :
			return a*b;
		case '/' :
			return a/b;
		default:						//������ 
            printf("û���������\n");
            break;
	}
	return 0;
}

int evaluateExpression(char* expression){//������ʽֵ�ĺ��� 
	Stack* values=creatStack();			 //�����������ֵ�ջ 
	Stack* operators=creatStack();		 //����������ŵ�ջ 
	int i;
	for(i=0;i<strlen(expression);i++){   //������������ݽ������� 
		if(expression[i]==' ')			 //�����ո� 
			continue;
		if(isdigit(expression[i])){		 //����������ֱ����ջ 
			int val=0;
			while(i<strlen(expression)&&isdigit(expression[i])){//��ȫ���������� 
				val=val*10+(expression[i]-'0');
				i++;
			}
			push(values,val);
			i--;
		}
		else if(expression[i]=='('){	  //������ֱ����ջ 
			push(operators,expression[i]);
		}
		else if(expression[i]==')'){	  //���������ţ�ֱ���ó�����λԪ�ؽ������� 
			while(!isEmpty(operators)&&peek(operators)!='('){
				int val2=pop(values);
				int val1=pop(values);
				char op=pop(operators);
				push(values,applyOperator(val1,val2,op));//�����ѹ��ջ 
			}
			if(!isEmpty(operators)&&peek(operators)=='(')//�������ų�ջ 
				pop(operators);
		}
		else{				//�����������������Ϊ�գ����·������ȼ�������ջ������ 
			while(!isEmpty(operators)&&precedence(expression[i])<=precedence(peek(operators))){
				int val2 = pop(values);
                int val1 = pop(values);
                char op = pop(operators); 
                push(values, applyOperator(val1, val2, op));//��������λ�������ջ 
			}
			push(operators,expression[i]);
		}
	}
	while(!isEmpty(operators)){ //����ʣ�·������� 
		int val2=pop(values);
		int val1=pop(values);
		char op=pop(operators);
		push(values,applyOperator(val1,val2,op));
	}
	int result=pop(values);
	destroyStack(values);  		//�ݻ�ջ���ͷ��ڴ� 
	destroyStack(operators);    //�ݻ�ջ���ͷ��ڴ� 
	return result;				//���ؽ�� 
}


int main(){
	char expression[MAX_SIZE];
	printf("��������ʽ��");
	fgets(expression,MAX_SIZE,stdin);//�Ӽ������������ݷ���expression������ 
	expression[strcspn(expression,"\n")]=0;//���������һλ���0 
	int result=evaluateExpression(expression);//���ú��� 
    printf("Result: %d\n", result);			//������ 
    getchar();
	return 0;
}
