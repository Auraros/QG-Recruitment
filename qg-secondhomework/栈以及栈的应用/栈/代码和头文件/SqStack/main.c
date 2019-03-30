#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../head/SqStack.h"

void draw1()
{
	printf("\t|**********************************************|\n");
	printf("\t|*              ˳��ջATD                     *|\n");
	printf("\t|*                                            *|\n");
	printf("\t|*           �����ȳ�ʼ��˳��ջ               *|\n");
	printf("\t|*     0:��               1���˳�����         *|\n"); 
	printf("\t|**********************************************|\n");
}

void draw2()
{
	printf("\t|**********************************************|\n");
	printf("\t|*             ˳��ջADT                      *|\n");
	printf("\t|*          1.�ж�ջ�Ƿ�Ϊ��                  *|\n"); 
	printf("\t|*          2.�õ�ջ��Ԫ��                    *|\n");
	printf("\t|*          3.���ջ                          *|\n");
	printf("\t|*          4.����ջ                          *|\n");
	printf("\t|*          5.���ջ�ĳ���                    *|\n");
	printf("\t|*          6.��ջ                            *|\n");
	printf("\t|*          7.��ջ                            *|\n");
	printf("\t|*          8 .�˳�����                       *|\n");
	printf("\t|**********************************************|\n");
	printf("��������ѡ�����(1-8):\n");
}

int go_on(){
	int flag=1;
	char choice;
	while(1){                  //�ж��û��Ƿ�Ҫ�����ò��� 
		printf("������[Y/N]");
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

void push(SqStack *s){    //��ջ�������� 
	ElemType x;
	int flag=1,push_flag;   //��main���� 
	while(flag){
		printf("\n������Ҫ�����ջԪ��:");
		scanf("%d",&x);
		push_flag=pushStack(s,x);
		if (push_flag == 1)
			printf("��ջ�ɹ���\n");
		else
			printf("\n��ջʧ�ܡ�ջ�Ѿ����ˡ�\n");
		flag = go_on();
	}
}

void pop(SqStack *s){
	ElemType x;
	int flag=1, pop_flag;
	while(flag){
		pop_flag=popStack(s,&x);
		if(pop_flag == 1)
			printf("\n��ջ�ɹ�����ջԪ��Ϊ��%d\n",x);
		else
			printf("\n��ջʧ�ܡ�ջΪ��.\n");
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
		printf("\n������������ȷ�����֣�");
		choice1 = getche(); 
	}
	if(choice1 == '0'){
		printf("\n������Ҫ��ʼ��˳��ջ�Ĵ�С��");
		scanf("%d",&sizes);
		initStack(&s,sizes);
		printf("��ʼ���ɹ���\n"); 
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
			printf("\n��������ȷ������:");
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
