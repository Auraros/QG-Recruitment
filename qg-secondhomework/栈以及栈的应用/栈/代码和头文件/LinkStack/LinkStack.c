#include"../head/LinkStack.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//链栈(基于链表的)
Status initLStack(LinkStack *s) {  //初始化
	 
	s->top = NULL;
	s->count = 0;
	printf("\n内存分配成功。\n");
	return SUCCESS;
}


	
Status isEmptyLStack(LinkStack *s){  //判断链栈是否为空
	if(s->count == 0){           //用count来判断是否为空链表 
		printf("\n链栈为空。\n");
		return SUCCESS;
	}
	else{
		printf("链栈不为空。\n");	
		return ERROR;
	}
}

Status getTopLStack(LinkStack *s,ElemType *e){  //得到栈顶元素
	if(s->count == 0){
		printf("\n栈空，不能去栈顶元素.\n");
		return ERROR;
		}
	else{
		*e = s->top->data;    //将栈顶元素赋值给e 
		printf("\n栈顶元素为：");
		printf("%d\n",*e);
		return SUCCESS;
	}
}
	
	
Status clearLStack(LinkStack *s){  //清空栈
	LinkStackPtr p;
	if(s->count == 0){
		printf("\n栈已经为空，清空失败.\n");
		return ERROR;
		}
	while(s->top){
		p = s->top;      //利用循环出栈，直到该栈为空 
		s->top = s->top->next;
		s->count--;
		free(p);
	}
	return SUCCESS;
}

Status destroyLStack(LinkStack *s){   //销毁栈
	LinkStackPtr p;
	while(s->top){    //操作一样，清空栈 
		p = s->top;
		s->top = s->top->next;
		s->count--;
		free(p);    //释放内存 
	}
	free(s);
	printf("销毁成功。\n");
	return SUCCESS;
}

Status LStackLength(LinkStack *s,int *length){    //检测栈长度
	printf("栈的长度为%d.\n",s->count); 
	return SUCCESS;
}


Status pushLStack(LinkStack *s,ElemType data) {  //入栈
	LinkStackPtr q;
	q = (LinkStackPtr)malloc(sizeof(StackNode));   
	if(s->count == 0){   //如果栈为空 
		s->top = q;    //将头指针赋值给q 
		q->data = data;   
		q->next = NULL;   //将q->next指向空 
	}
	else{
		q->data = data;   //如果栈不为空 
		q->next = s->top;
		s->top = q;
	}
	s->count++;
	return SUCCESS;
}

Status popLStack(LinkStack *s,ElemType *data){   //出栈
	LinkStackPtr p;
	if(s->count == 0){    
		printf("链栈为空。\n");
		return ERROR;
	}
	*data=s->top->data;     //将栈顶元素赋值给data 
	p=s->top;
	s->top = s->top->next;   
	free(p);
	s->count--;       
	return SUCCESS;
}
