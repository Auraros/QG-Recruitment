#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../head/SqStack.h"

void draw1()
{
	printf("\t|**********************************************|\n");
	printf("\t|*              顺序栈ATD                     *|\n");
	printf("\t|*                                            *|\n");
	printf("\t|*           首先先初始化顺序栈               *|\n");
	printf("\t|*     0:是               1：退出程序         *|\n"); 
	printf("\t|**********************************************|\n");
}

void draw2()
{
	printf("\t|**********************************************|\n");
	printf("\t|*             顺序栈ADT                      *|\n");
	printf("\t|*          1.判断栈是否为空                  *|\n"); 
	printf("\t|*          2.得到栈顶元素                    *|\n");
	printf("\t|*          3.清空栈                          *|\n");
	printf("\t|*          4.销毁栈                          *|\n");
	printf("\t|*          5.检测栈的长度                    *|\n");
	printf("\t|*          6.入栈                            *|\n");
	printf("\t|*          7.出栈                            *|\n");
	printf("\t|*          8 .退出程序                       *|\n");
	printf("\t|**********************************************|\n");
	printf("请输入所选的序号(1-8):\n");
}

int go_on(){
	int flag=1;
	char choice;
	while(1){                  //判断用户是否要继续该操作 
		printf("继续吗？[Y/N]");
		choice = getche();
		if (choice == 'Y' || choice == 'y')
			break;
		else if (choice == 'N' || choice == 'n'){
			flag = 0;
			break;
		}
	}
	return flag;
}

void push(SqStack *s){    //出栈的主函数 
	ElemType x;
	int flag=1,push_flag;   //简化main函数 
	while(flag){
		printf("\n请输入要输入的栈元素:");
		scanf("%d",&x);
		push_flag=pushStack(s,x);
		if (push_flag == 1)
			printf("入栈成功。\n");
		else
			printf("\n入栈失败。栈已经满了。\n");
		flag = go_on();
	}
}

void pop(SqStack *s){
	ElemType x;
	int flag=1, pop_flag;
	while(flag){
		pop_flag=popStack(s,&x);
		if(pop_flag == 1)
			printf("\n出栈成功，出栈元素为：%d\n",x);
		else
			printf("\n出栈失败。栈为空.\n");
		flag = go_on();
	}
} 

int main(){
	SqStack s;
	char choice1,choice2;
	int sizes;
	int flag=1;
	draw1();
	choice1 = getche();
	while(choice1!='0'&& choice1!='1'){
		printf("\n请重新输入正确的数字：");
		choice1 = getche(); 
	}
	if(choice1 == '0'){
		printf("\n输入你要初始化顺序栈的大小：");
		scanf("%d",&sizes);
		initStack(&s,sizes);
		printf("初始化成功。\n"); 
	}
	else{
		return 0;
	}
	system("pause");
	system("cls");
	do{
		draw2();
		choice2 = getche();
		while(choice2!='1' && choice2!='2' && choice2!='3' && choice2!='4' && choice2!='5' && choice2!='6' && choice2!='7' && choice2!='8'){
			printf("\n请输入正确的数字:");
			choice2 = getche();
		}
		switch(choice2){
			case '1':isEmptyStack(&s);break;
			case '2':{
				ElemType e;
				getTopStack(&s,&e);
				break;
			}
			case '3':clearStack(&s);break;
			case '4':destroyStack(&s);flag = 0;break;
			case '5':{
				ElemType length;
				stackLength(&s,&length);
				break;
			}
			case '6':push(&s);break;
			case '7':pop(&s);break;
			case '8':flag = 0;break;
		}
		system("pause");
		system("cls");
	}while(flag==1);
} 
