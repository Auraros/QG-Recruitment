#include"../head/SqStack.h"
#include<stdio.h>
#include<stdlib.h>

//˳��ջ(���������)
Status initStack(SqStack *s,int sizes){  //��ʼ��ջ
	s->elem = (ElemType *)malloc(sizes * sizeof(ElemType));
	if (s->elem == NULL){  //�ж�ջ�Ƿ����ɹ� 
		printf("\n�ڴ����ʧ�ܡ�\n");
		return ERROR; 
	}
	s->top = -1;
	s->size=sizes;
	return SUCCESS;
}

Status isEmptyStack(SqStack *s) {  //�ж�ջ�Ƿ�Ϊ��
	if(s->top == -1){
		printf("\n��ջΪ��ջ��\n");
		return SUCCESS;
	}
	else{
		printf("\n��ջ��Ϊ�ա�\n");
		return ERROR;
	}
	
}

Status getTopStack(SqStack *s,ElemType *e) {  //�õ�ջ��Ԫ��
	if (s->top == -1)     //�ж�ջ�Ƿ�Ϊ�� 
		printf("\nջ�գ�û��Ԫ�ء�\n");
	else{
		*e = s->elem[s->top];   //��ջ��Ԫ�ظ�ֵ��e 
		printf("\nջ��Ԫ��Ϊ��");
		printf("%4d\n",*e);
		return SUCCESS;
	}
}

Status clearStack(SqStack *s) {  //���ջ
	if (s->top == -1)
		printf("\nջ�Ѿ�Ϊ�ա�\n");
	else{
		s->top = -1;
		printf("\n�����ϡ�\n"); 
		return SUCCESS;
	} 
}
	

Status destroyStack(SqStack *s){  //����ջ
	s->size = 0;
	free(s->elem);
	return SUCCESS;
}

Status stackLength(SqStack *s,int *length){  //���ջ����
	if (s->top == -1)     //�ж�ջ�Ƿ�Ϊ�� 
		printf("\nջ�գ�û��Ԫ�ء�\n");
	printf("ջ�ĳ���Ϊ%4d\n",s->top+1);
	
}


Status pushStack(SqStack *s,ElemType data) { //��ջ
	if( s == NULL || s->top==s->size-1)  //ջ��
		return ERROR;
	s->top++;
	s->elem[s->top] = data;
	return SUCCESS;
}


Status popStack(SqStack *s,ElemType *data) {  //��ջ
	if( s == NULL || s->top==-1)  //ջ��
		return ERROR;
	*data = s->elem[s->top];              //��Ҫɾ����ջ��Ԫ�ظ�ֵ��e 
	s->top--;                           //��ջ��ָ���һ 
	return SUCCESS;
}
