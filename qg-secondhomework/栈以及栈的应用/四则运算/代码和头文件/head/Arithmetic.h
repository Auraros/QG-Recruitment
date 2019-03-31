#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#define STACK_INIT_SIZE 20
#define STACKINCREMENT 10

typedef enum Status {
	ERROR = 0, SUCCESS = 1
} Status;

typedef char ElemType;

typedef struct SqStack {
	ElemType *base;
	ElemType *top;
	int stackSize;
} SqStack;


//��������(���������)
Status initStack(SqStack *s);//��ʼ��ջ
Status Push(SqStack *s,ElemType data);//��ջ
Status Pop(SqStack *s,ElemType *data);//��ջ


#endif // STACK_H_INCLUDED
