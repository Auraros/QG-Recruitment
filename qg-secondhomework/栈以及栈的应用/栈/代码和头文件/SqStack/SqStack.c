#include"../head/SqStack.h"
#include<stdio.h>
#include<stdlib.h>

//顺序栈(基于数组的)
Status initStack(SqStack *s,int sizes){  //初始化栈
	s->elem = (ElemType *)malloc(sizes * sizeof(ElemType));
	if (s->elem == NULL){  //判断栈是否分配成功 
		printf("\n内存分配失败。\n");
		return ERROR; 
	}
	s->top = -1;
	s->size=sizes;
	return SUCCESS;
}

Status isEmptyStack(SqStack *s) {  //判断栈是否为空
	if(s->top == -1){
		printf("\n该栈为空栈。\n");
		return SUCCESS;
	}
	else{
		printf("\n该栈不为空。\n");
		return ERROR;
	}
	
}

Status getTopStack(SqStack *s,ElemType *e) {  //得到栈顶元素
	if (s->top == -1)     //判断栈是否为空 
		printf("\n栈空，没有元素。\n");
	else{
		*e = s->elem[s->top];   //将栈顶元素赋值给e 
		printf("\n栈顶元素为：");
		printf("%4d\n",*e);
		return SUCCESS;
	}
}

Status clearStack(SqStack *s) {  //清空栈
	if (s->top == -1)
		printf("\n栈已经为空。\n");
	else{
		s->top = -1;
		printf("\n清空完毕。\n"); 
		return SUCCESS;
	} 
}
	

Status destroyStack(SqStack *s){  //销毁栈
	s->size = 0;
	free(s->elem);
	return SUCCESS;
}

Status stackLength(SqStack *s,int *length){  //检测栈长度
	if (s->top == -1)     //判断栈是否为空 
		printf("\n栈空，没有元素。\n");
	printf("栈的长度为%4d\n",s->top+1);
	
}


Status pushStack(SqStack *s,ElemType data) { //入栈
	if( s == NULL || s->top==s->size-1)  //栈满
		return ERROR;
	s->top++;
	s->elem[s->top] = data;
	return SUCCESS;
}


Status popStack(SqStack *s,ElemType *data) {  //出栈
	if( s == NULL || s->top==-1)  //栈满
		return ERROR;
	*data = s->elem[s->top];              //将要删除的栈顶元素赋值给e 
	s->top--;                           //将栈顶指针减一 
	return SUCCESS;
}
