#include"../head/Arithmetic1.h"
#include<stdio.h>
#include<stdlib.h>

//栈操作
/*初始化栈*/ 
Status InitStack(sqStack *s){
    s->base = (ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType));  //为栈底分配内存 
    if (!s->base)    //分配失败处理 
        return ERROR;
    s->top = s->base;     //将栈顶置于栈底 
    s->stackSize = STACK_INIT_SIZE;  //最大size 
}

/*返回栈的长度*/ 
int StackLength(sqStack s){
    int length = s.top - s.base;    //栈顶-栈底，即长度 
    return length;
} 

/*清空栈*/ 
Status ClearStack(sqStack *s){ 
    if (s == NULL)
        return ERROR;
    s->top = s->base;   //将栈顶指针指向栈底 
    return OK;
}

/*判断栈是否为空*/ 
Status StackEmpty(sqStack s){
    if (s.base == s.top) 
        return TRUE;
    return FALSE;
}

/*得到栈顶元素*/ 
Status GetTop(sqStack s, ElemType *e){
    if (!e || StackEmpty(s) || !s.base)  //异常处理判断 
        return ERROR;
    *e = *(s.top - 1);   //将栈顶元素赋值给e 
    return OK;
}

/*入栈*/ 
Status Push(sqStack *s, ElemType e)
{
    ElemType* newStack;   
    if (!s->base)
        return ERROR;
    *(s->top) = e;
    s->top++;
    return OK;
}

/*出栈*/ 
Status Pop(sqStack *s, ElemType *e){
    if (!s->base || !e || StackEmpty(*s))
        return ERROR;
    *e = *(--s->top);
    return OK;
}

/*销毁栈*/ 
Status DestroyStack(sqStack *s){
    if (!s->base)    //若是栈存在
    {
        s->stackSize = 0; 
        free(s->base);
        s->base = s->top = NULL;  //将两个指针都指向空  
    }
    return OK;
}

/*遍历输出栈 */ 
void PrintStack(sqStack s){
    data d;
    int len = StackLength(s);
    int i;
    for ( i = 0; i < len;i++)   
    {
        Pop(&s, &d);
        if (d.flag == 1) // 通过flag来判断，输出为数字还是字符 
            printf("%c", d.number.sign);
        else
            printf("%.3lf", d.number.num);
    }
}


