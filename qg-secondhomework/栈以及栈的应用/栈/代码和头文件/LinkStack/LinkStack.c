#include"../head/LinkStack.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//��ջ(���������)
Status initLStack(LinkStack *s) {  //��ʼ��
	 
	s->top = NULL;
	s->count = 0;
	printf("\n�ڴ����ɹ���\n");
	return SUCCESS;
}


	
Status isEmptyLStack(LinkStack *s){  //�ж���ջ�Ƿ�Ϊ��
	if(s->count == 0){           //��count���ж��Ƿ�Ϊ������ 
		printf("\n��ջΪ�ա�\n");
		return SUCCESS;
	}
	else{
		printf("��ջ��Ϊ�ա�\n");	
		return ERROR;
	}
}

Status getTopLStack(LinkStack *s,ElemType *e){  //�õ�ջ��Ԫ��
	if(s->count == 0){
		printf("\nջ�գ�����ȥջ��Ԫ��.\n");
		return ERROR;
		}
	else{
		*e = s->top->data;    //��ջ��Ԫ�ظ�ֵ��e 
		printf("\nջ��Ԫ��Ϊ��");
		printf("%d\n",*e);
		return SUCCESS;
	}
}
	
	
Status clearLStack(LinkStack *s){  //���ջ
	LinkStackPtr p;
	if(s->count == 0){
		printf("\nջ�Ѿ�Ϊ�գ����ʧ��.\n");
		return ERROR;
		}
	while(s->top){
		p = s->top;      //����ѭ����ջ��ֱ����ջΪ�� 
		s->top = s->top->next;
		s->count--;
		free(p);
	}
	return SUCCESS;
}

Status destroyLStack(LinkStack *s){   //����ջ
	LinkStackPtr p;
	while(s->top){    //����һ�������ջ 
		p = s->top;
		s->top = s->top->next;
		s->count--;
		free(p);    //�ͷ��ڴ� 
	}
	free(s);
	printf("���ٳɹ���\n");
	return SUCCESS;
}

Status LStackLength(LinkStack *s,int *length){    //���ջ����
	printf("ջ�ĳ���Ϊ%d.\n",s->count); 
	return SUCCESS;
}


Status pushLStack(LinkStack *s,ElemType data) {  //��ջ
	LinkStackPtr q;
	q = (LinkStackPtr)malloc(sizeof(StackNode));   
	if(s->count == 0){   //���ջΪ�� 
		s->top = q;    //��ͷָ�븳ֵ��q 
		q->data = data;   
		q->next = NULL;   //��q->nextָ��� 
	}
	else{
		q->data = data;   //���ջ��Ϊ�� 
		q->next = s->top;
		s->top = q;
	}
	s->count++;
	return SUCCESS;
}

Status popLStack(LinkStack *s,ElemType *data){   //��ջ
	LinkStackPtr p;
	if(s->count == 0){    
		printf("��ջΪ�ա�\n");
		return ERROR;
	}
	*data=s->top->data;     //��ջ��Ԫ�ظ�ֵ��data 
	p=s->top;
	s->top = s->top->next;   
	free(p);
	s->count--;       
	return SUCCESS;
}
