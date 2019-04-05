#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "../head/AQueue.h"

void wait(){
	printf("\n按任意键继续...\n");
	getch();
}

int go_on(){   //对用户是否进行继续输入进行处理 
	int flag=1;
	char choice;
	while(1){
		printf("\n继续吗？[Y/N]：");
		choice = getche();
		if(choice == 'Y'|| choice == 'y')
			break;
		else if (choice == 'N' || choice == 'n'){
			flag = 0;
			break;
		}
	}
	return (flag);
}

void EnQueue(AQueue *Q){   //入队函数 
	int flag=1,enqueue_flag;
	while(flag){
		printf("\n输入你要入队的元素：");
		if(Q->length == sizeof(char)){   //根据不同类型来定义不同的变量 
			char a;
			scanf("%c",&a);             //输入字符 
			enqueue_flag=EnAQueue(Q, &a);
			}
		else if (Q->length == sizeof(double)){
			double b;
			scanf("%lf",&b);          //输入浮点数 
			enqueue_flag=EnAQueue(Q, &b);
			}
		else if (Q->length == sizeof(int)){
			int c;
			scanf("%d",&c);         //输入整数 
			enqueue_flag=EnAQueue(Q, &c);
			}
		if(enqueue_flag == 1)
			printf("入队成功.");
		else 
			printf("入队失败.");
		flag=go_on();
	}
}

void DeQueue(AQueue *Q){  //由于出队比较简单，就不需要分类型 
	int flag=1,dequeue_flag;
	while(flag){ 
		dequeue_flag=DeAQueue(Q);
		if (dequeue_flag==1)
			printf("\n出队成功.");
		else
			printf("\n出队失败。");
		flag = go_on();
	}
}


void draw2()
{
	printf("\t|**********************************************|\n");
	printf("\t|*              循环队列ATD                   *|\n");
	printf("\t|*                                            *|\n");
	printf("\t|*           首先先初始化循环队列             *|\n");
	printf("\t|*     0:是               1：退出程序         *|\n"); 
	printf("\t|**********************************************|\n");
}

void draw3()
{
	printf("\t|**********************************************|\n");
	printf("\t|*             循环队列ADT                    *|\n");
	printf("\t|*          1.摧毁队列                        *|\n"); 
	printf("\t|*          2.检查队列是否已满                *|\n");
	printf("\t|*          3.检查队列是否为空                *|\n");
	printf("\t|*          4.查看队头元素                    *|\n");
	printf("\t|*          5.检测队列的长度                  *|\n");
	printf("\t|*          6.入队                            *|\n");
	printf("\t|*          7.出队                            *|\n");
    printf("\t|*          8.清空队列                        *|\n");
	printf("\t|*          9.遍历函数操作                    *|\n");
	printf("\t|*          #.退出程序                        *|\n");
	printf("\t|**********************************************|\n");
	printf("请输入所选的序号(1-9)或者输入‘#’结束:\n");
}

void draw1(){
	printf("\t|**********************************************|\n");
	printf("\t|*          首先选择队列的数据类型            *|\n");
	printf("\t|*             1.整数                         *|\n");
	printf("\t|*             2.浮点数                       *|\n");
	printf("\t|*             3.字符                         *|\n");
	printf("\t|*             4.退出程序                     *|\n"); 
	printf("\t|**********************************************|\n");
	printf("请输入你所选择的序号（1-4）："); 
} 

int main() {
	AQueue Q;
	char choice1,choice2,choice3;  //三个选择 
	int flag = 1;
	draw1();
	choice1 = getche();
	while(choice1!='1'&& choice1!='2' && choice1!='3' && choice1!='4'){
	printf("\n请重新输入正确的数字：");   //用户输入错误处理 
	choice1 = getche(); 
	}
	switch(choice1){
		case '1': Q.length = sizeof(int);break;   //跟据用户的选择对data类型进行修改 
		case '2': Q.length = sizeof(double);break;
		case '3': Q.length = sizeof(char);break;
		case '4': wait(); return 0;
	}
	wait();
	system("cls");
	draw2();
	choice2 = getche();
	while(choice2!='0'&& choice2!='1'){
	printf("\n请重新输入正确的数字：");
	choice2 = getche(); 
	}
	switch(choice2){
		case '0': InitAQueue(&Q);break;  //初始化队列 
		case '1': wait(); return 0;
	}
	wait();
	system("cls");
	do{
		draw3();
		choice3 = getche();
		while(choice3!='1' && choice3!='2' && choice3!='3' && choice3!='4' && choice3!='5' && choice3!='6' && choice3!='7' && choice3!='8' && choice3!='9' && choice3!='#'){
			printf("\n请输入正确的数字:");
			choice3 = getche();
		} 
		switch(choice3){
			case '1': {
			DestoryAQueue(&Q);  //摧毁队列 
			flag=0;
			break;}
			case '2': IsFullAQueue(&Q);break;  // 判断队列是否已经满 
			case '3': IsEmptyAQueue(&Q);break;  // 判断队列是否为空 
			case '4':{
				if(Q.length == sizeof(char)){ //当为字符元素时 
					char a;
					GetHeadAQueue(&Q,&a);   //取出队列的头元素 
				}
				else if (Q.length == sizeof(double)){ //当为浮点数元素时 
					double b;
					GetHeadAQueue(&Q,&b);   
				}
				else if (Q.length == sizeof(int)){  //当为整数类型时 
					int c;
					GetHeadAQueue(&Q,&c);
				}
				break;
				}
			case '5':{
				int length;
				length = LengthAQueue(&Q);  //返回队列长度 
				printf("\n该队列的长度是：%d",length);
				break;
			} 
			case '6':EnQueue(&Q);break;  //入队 
			case '7':DeQueue(&Q);break;   //出队 
			case '8':ClearAQueue(&Q);break;  //清空队列 
			case '9':{
				TraverseAQueue(&Q, APrint);  //遍历输出队列 
				break;
			}
			case '#':flag=0;break;
		}
		wait();
		system("cls");
		}while(flag==1);
}
