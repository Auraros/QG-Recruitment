#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#define MAXSIZE 100  //中缀表达式的长度 
#define STACK_INIT_SIZE 100      //定义栈的初始大小 
#define STACK_INCR_SIZE 10 

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef struct Data{
	int flag;    //1为字符，2为浮点数 
	union{
		double num;  //储存浮点数 
		char sign;   //储存字符 
	}number;
}data;

typedef int Status;
typedef data ElemType;

typedef struct
{
    ElemType *base;    //栈底指针
    ElemType *top;    //栈顶指针
    int stackSize;    //最大容量，这是可修改的
}sqStack;


//四则运算(基于数组的)的基础操作 
Status InitStack(sqStack *s);    //初始化操作，建立一个空栈
Status ClearStack(sqStack *s);    //将栈清空
Status StackEmpty(sqStack s);    //若栈存在，返回true，否则返回false
int StackLength(sqStack s);        //返回栈S的元素个数

Status GetTop(sqStack s, ElemType *e);    //若是栈存在且非空，用e返回S的栈顶元素
Status Push(sqStack *s, ElemType e);    // 若是栈存在，则插入新的元素e到栈S中并成为栈顶元素
Status Pop(sqStack *s, ElemType *e);    //若是栈存在且非空，删除栈顶元素，并用e返回其值
Status DestroyStack(sqStack *s);        //若是栈存在，则销毁他

void PrintStack(sqStack s);

//四则运算中需要的函数 
Status MatchBrack(char* str);    //匹配括号是否正确
Status RotateStack(sqStack* s);    //将栈中的数据翻转
Status GetMidStack(sqStack *s, char* str);    //获取中缀表达式,将字符串转换到栈中
Status GetBackStack(sqStack *s);     //获取后缀表达式
Status norGetBackStack(char *s); //获取正确的后缀表达式 
Status GetBackValue(sqStack *s, double* val);//获取后缀表达式计算出来的结果 


#endif  //STACK_H_INCLUDED
