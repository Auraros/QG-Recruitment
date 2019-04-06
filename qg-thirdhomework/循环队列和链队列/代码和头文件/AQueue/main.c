#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "../head/AQueue.h"

void wait(){
	printf("\n�����������...\n");
	getch();
}

int go_on(){   //���û��Ƿ���м���������д��� 
	int flag=1;
	char choice;
	while(1){
		printf("\n������[Y/N]��");
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

void EnQueue(AQueue *Q){   //��Ӻ��� 
	int flag=1,enqueue_flag;
	while(flag){
		printf("\n������Ҫ��ӵ�Ԫ�أ�");
		if(Q->length == sizeof(char)){   //���ݲ�ͬ���������岻ͬ�ı��� 
			char a;
			scanf("%c",&a);             //�����ַ� 
			enqueue_flag=EnAQueue(Q, &a);
			}
		else if (Q->length == sizeof(double)){
			double b;
			scanf("%lf",&b);          //���븡���� 
			enqueue_flag=EnAQueue(Q, &b);
			}
		else if (Q->length == sizeof(int)){
			int c;
			scanf("%d",&c);         //�������� 
			enqueue_flag=EnAQueue(Q, &c);
			}
		if(enqueue_flag == 1)
			printf("��ӳɹ�.");
		else 
			printf("���ʧ��.");
		flag=go_on();
	}
}

void DeQueue(AQueue *Q){  //���ڳ��ӱȽϼ򵥣��Ͳ���Ҫ������ 
	int flag=1,dequeue_flag;
	while(flag){ 
		dequeue_flag=DeAQueue(Q);
		if (dequeue_flag==1)
			printf("\n���ӳɹ�.");
		else
			printf("\n����ʧ�ܡ�");
		flag = go_on();
	}
}


void draw2()
{
	printf("\t|**********************************************|\n");
	printf("\t|*              ѭ������ATD                   *|\n");
	printf("\t|*                                            *|\n");
	printf("\t|*           �����ȳ�ʼ��ѭ������             *|\n");
	printf("\t|*     0:��               1���˳�����         *|\n"); 
	printf("\t|**********************************************|\n");
}

void draw3()
{
	printf("\t|**********************************************|\n");
	printf("\t|*             ѭ������ADT                    *|\n");
	printf("\t|*          1.�ݻٶ���                        *|\n"); 
	printf("\t|*          2.�������Ƿ�����                *|\n");
	printf("\t|*          3.�������Ƿ�Ϊ��                *|\n");
	printf("\t|*          4.�鿴��ͷԪ��                    *|\n");
	printf("\t|*          5.�����еĳ���                  *|\n");
	printf("\t|*          6.���                            *|\n");
	printf("\t|*          7.����                            *|\n");
    printf("\t|*          8.��ն���                        *|\n");
	printf("\t|*          9.������������                    *|\n");
	printf("\t|*          #.�˳�����                        *|\n");
	printf("\t|**********************************************|\n");
	printf("��������ѡ�����(1-9)�������롮#������:\n");
}

void draw1(){
	printf("\t|**********************************************|\n");
	printf("\t|*          ����ѡ����е���������            *|\n");
	printf("\t|*             1.����                         *|\n");
	printf("\t|*             2.������                       *|\n");
	printf("\t|*             3.�ַ�                         *|\n");
	printf("\t|*             4.�˳�����                     *|\n"); 
	printf("\t|**********************************************|\n");
	printf("����������ѡ�����ţ�1-4����"); 
} 

int main() {
	AQueue Q;
	char choice1,choice2,choice3;  //����ѡ�� 
	int flag = 1;
	draw1();
	choice1 = getche();
	while(choice1!='1'&& choice1!='2' && choice1!='3' && choice1!='4'){
	printf("\n������������ȷ�����֣�");   //�û���������� 
	choice1 = getche(); 
	}
	switch(choice1){
		case '1': Q.length = sizeof(int);break;   //�����û���ѡ���data���ͽ����޸� 
		case '2': Q.length = sizeof(double);break;
		case '3': Q.length = sizeof(char);break;
		case '4': wait(); return 0;
	}
	wait();
	system("cls");
	draw2();
	choice2 = getche();
	while(choice2!='0'&& choice2!='1'){
	printf("\n������������ȷ�����֣�");
	choice2 = getche(); 
	}
	switch(choice2){
		case '0': InitAQueue(&Q);break;  //��ʼ������ 
		case '1': wait(); return 0;
	}
	wait();
	system("cls");
	do{
		draw3();
		choice3 = getche();
		while(choice3!='1' && choice3!='2' && choice3!='3' && choice3!='4' && choice3!='5' && choice3!='6' && choice3!='7' && choice3!='8' && choice3!='9' && choice3!='#'){
			printf("\n��������ȷ������:");
			choice3 = getche();
		} 
		switch(choice3){
			case '1': {
			DestoryAQueue(&Q);  //�ݻٶ��� 
			flag=0;
			break;}
			case '2': IsFullAQueue(&Q);break;  // �ж϶����Ƿ��Ѿ��� 
			case '3': IsEmptyAQueue(&Q);break;  // �ж϶����Ƿ�Ϊ�� 
			case '4':{
				if(Q.length == sizeof(char)){ //��Ϊ�ַ�Ԫ��ʱ 
					char a;
					GetHeadAQueue(&Q,&a);   //ȡ�����е�ͷԪ�� 
				}
				else if (Q.length == sizeof(double)){ //��Ϊ������Ԫ��ʱ 
					double b;
					GetHeadAQueue(&Q,&b);   
				}
				else if (Q.length == sizeof(int)){  //��Ϊ��������ʱ 
					int c;
					GetHeadAQueue(&Q,&c);
				}
				break;
				}
			case '5':{
				int length;
				length = LengthAQueue(&Q);  //���ض��г��� 
				printf("\n�ö��еĳ����ǣ�%d",length);
				break;
			} 
			case '6':EnQueue(&Q);break;  //��� 
			case '7':DeQueue(&Q);break;   //���� 
			case '8':ClearAQueue(&Q);break;  //��ն��� 
			case '9':{
				TraverseAQueue(&Q, APrint);  //����������� 
				break;
			}
			case '#':flag=0;break;
		}
		wait();
		system("cls");
		}while(flag==1);
}
