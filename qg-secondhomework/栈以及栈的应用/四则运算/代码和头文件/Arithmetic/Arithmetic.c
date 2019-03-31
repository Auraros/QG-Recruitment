#include"../head/Arithmetic.h"
#include<stdio.h>
#include<stdlib.h>

//��������(���������)
Status initStack(SqStack *s){  //��ʼ��ջ
	s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	if (!s->base)
		exit(0);
	s->top = s->base;
	s->stackSize =  STACK_INIT_SIZE;	
}

Status Push(SqStack *s,ElemType data) { //��ջ
	if(s->top - s->base >= s->stackSize){
		s->base = (ElemType *)realloc(s->base, (s->stackSize + STACKINCREMENT) * sizeof(ElemType));
		if(!s->base)
			exit(0);
			
		s->top = s->base + s->stackSize;
		s->stackSize = s->stackSize + STACKINCREMENT;
	}
	
	*(s->top) = data;
	s->top++;
}


Status Pop(SqStack *s,ElemType *data) {  //��ջ
	if( s->top == s->base)
		return;
		
	*data = *--(s->top);
}


