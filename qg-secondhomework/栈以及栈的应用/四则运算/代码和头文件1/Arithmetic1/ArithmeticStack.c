#include"../head/Arithmetic1.h"
#include<stdio.h>
#include<stdlib.h>

//ջ����
/*��ʼ��ջ*/ 
Status InitStack(sqStack *s){
    s->base = (ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType));  //Ϊջ�׷����ڴ� 
    if (!s->base)    //����ʧ�ܴ��� 
        return ERROR;
    s->top = s->base;     //��ջ������ջ�� 
    s->stackSize = STACK_INIT_SIZE;  //���size 
}

/*����ջ�ĳ���*/ 
int StackLength(sqStack s){
    int length = s.top - s.base;    //ջ��-ջ�ף������� 
    return length;
} 

/*���ջ*/ 
Status ClearStack(sqStack *s){ 
    if (s == NULL)
        return ERROR;
    s->top = s->base;   //��ջ��ָ��ָ��ջ�� 
    return OK;
}

/*�ж�ջ�Ƿ�Ϊ��*/ 
Status StackEmpty(sqStack s){
    if (s.base == s.top) 
        return TRUE;
    return FALSE;
}

/*�õ�ջ��Ԫ��*/ 
Status GetTop(sqStack s, ElemType *e){
    if (!e || StackEmpty(s) || !s.base)  //�쳣�����ж� 
        return ERROR;
    *e = *(s.top - 1);   //��ջ��Ԫ�ظ�ֵ��e 
    return OK;
}

/*��ջ*/ 
Status Push(sqStack *s, ElemType e)
{
    ElemType* newStack;   
    if (!s->base)
        return ERROR;
    *(s->top) = e;
    s->top++;
    return OK;
}

/*��ջ*/ 
Status Pop(sqStack *s, ElemType *e){
    if (!s->base || !e || StackEmpty(*s))
        return ERROR;
    *e = *(--s->top);
    return OK;
}

/*����ջ*/ 
Status DestroyStack(sqStack *s){
    if (!s->base)    //����ջ����
    {
        s->stackSize = 0; 
        free(s->base);
        s->base = s->top = NULL;  //������ָ�붼ָ���  
    }
    return OK;
}

/*�������ջ */ 
void PrintStack(sqStack s){
    data d;
    int len = StackLength(s);
    int i;
    for ( i = 0; i < len;i++)   
    {
        Pop(&s, &d);
        if (d.flag == 1) // ͨ��flag���жϣ����Ϊ���ֻ����ַ� 
            printf("%c", d.number.sign);
        else
            printf("%.3lf", d.number.num);
    }
}


