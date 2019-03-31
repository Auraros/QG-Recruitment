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


//四则运算(基于数组的)
Status initStack(SqStack *s);//初始化栈
Status Push(SqStack *s,ElemType data);//入栈
Status Pop(SqStack *s,ElemType *data);//出栈


#endif // STACK_H_INCLUDED
