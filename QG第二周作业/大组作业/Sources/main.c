#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  	//布尔型 
#include <string.h>
#include <ctype.h>		//判断是否为数字 

#define MAX_SIZE 100

typedef struct Node{	//定义链表 
	int date;			//储存输入数据 
	struct Node* next;   
}Node; 

typedef struct Stack {  //定义栈 
	Node* top;			//栈顶地址 
	int size;			//元素数量 
}Stack;

Stack* creatStack(){	 //指针函数，返回地址，创建新栈函数 
	Stack* stack=(Stack*)malloc(sizeof(Stack));//开辟空间 
	stack->top=NULL;						   //顶为空 
	stack->size=0;
	return stack;							   //返回栈的地址 
}

bool isEmpty(Stack* stack){//检查栈是否为空 
	return stack->size==0; //为空返回true，不空为false 
}

bool isFull(Stack* stack){//检查栈是否装满 
	return stack->size==MAX_SIZE;
}

void push(Stack* stack,int date){//压入数据 
	if(isFull(stack)){	  //判断栈是否满 
		printf("Stack is full\n");
		return;
	}
	Node* newNode=(Node*)malloc(sizeof(Node)); //开辟新节点 
	newNode->date=date;						   //存储内容 
	newNode->next=stack->top;				   //将新节点的next指向栈顶 
	stack->top=newNode;						   //将栈顶指向新节点 
	stack->size++;
}

int pop(Stack* stack){	//输出栈顶元素 
	if(isEmpty(stack)){
		printf("Stack is empty\n");
		return -1;
	}
	Node* temp=stack->top;//定义变量储存栈顶要提取元素 
	int date =temp->date; //提取元素内容 
	stack->top=temp->next;//更换栈顶 
	free(temp);			  //释放内存 
	stack->size--;
	return date;
}

int peek(Stack* stack){//读取栈顶元素，不出栈 
	if (isEmpty(stack)) {  // 如果栈为空，输出提示信息并返回-1
        printf("Stack is empty\n");
        return -1;
    }
    return stack->top->date;
}

void destroyStack(Stack* stack){//摧毁栈，释放内存 
	while(!isEmpty(stack)){
		pop(stack);
	}
	free(stack);
}

int precedence(char op){ //自定义运算优先级 
	if(op=='+'||op=='-')
		return 1;
	if(op=='*'||op=='/')
		return 2;
	return 0;
}

int applyOperator(int a,int b,char op){//运用运算符计算函数 
	switch(op){
		case '+':
			return a+b;
		case '-' :
			return a-b;
		case '*' :
			return a*b;
		case '/' :
			return a/b;
		default:						//错误处理 
            printf("没有这个符号\n");
            break;
	}
	return 0;
}

int evaluateExpression(char* expression){//计算表达式值的函数 
	Stack* values=creatStack();			 //创建储存数字的栈 
	Stack* operators=creatStack();		 //创建储存符号的栈 
	int i;
	for(i=0;i<strlen(expression);i++){   //遍历输入的内容进行运算 
		if(expression[i]==' ')			 //跳过空格 
			continue;
		if(isdigit(expression[i])){		 //若是数字则直接入栈 
			int val=0;
			while(i<strlen(expression)&&isdigit(expression[i])){//补全数字完整性 
				val=val*10+(expression[i]-'0');
				i++;
			}
			push(values,val);
			i--;
		}
		else if(expression[i]=='('){	  //左括号直接入栈 
			push(operators,expression[i]);
		}
		else if(expression[i]==')'){	  //遇到右括号，直接拿出上两位元素进行运算 
			while(!isEmpty(operators)&&peek(operators)!='('){
				int val2=pop(values);
				int val1=pop(values);
				char op=pop(operators);
				push(values,applyOperator(val1,val2,op));//将结果压入栈 
			}
			if(!isEmpty(operators)&&peek(operators)=='(')//将左括号出栈 
				pop(operators);
		}
		else{				//常规运算在运算符不为空，且新符号优先级不高于栈顶符号 
			while(!isEmpty(operators)&&precedence(expression[i])<=precedence(peek(operators))){
				int val2 = pop(values);
                int val1 = pop(values);
                char op = pop(operators); 
                push(values, applyOperator(val1, val2, op));//计算上两位结果并入栈 
			}
			push(operators,expression[i]);
		}
	}
	while(!isEmpty(operators)){ //处理剩下符号运算 
		int val2=pop(values);
		int val1=pop(values);
		char op=pop(operators);
		push(values,applyOperator(val1,val2,op));
	}
	int result=pop(values);
	destroyStack(values);  		//摧毁栈并释放内存 
	destroyStack(operators);    //摧毁栈并释放内存 
	return result;				//返回结果 
}


int main(){
	char expression[MAX_SIZE];
	printf("请输入表达式：");
	fgets(expression,MAX_SIZE,stdin);//从键盘输入获得数据放入expression数组中 
	expression[strcspn(expression,"\n")]=0;//将数组最后一位变成0 
	int result=evaluateExpression(expression);//调用函数 
    printf("Result: %d\n", result);			//输出结果 
    getchar();
	return 0;
}
