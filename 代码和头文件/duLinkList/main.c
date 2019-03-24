/***********************************************************
##filename   : main.c
##author     : Li Weile
##create time : 2019/3/23
************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"..\head\duLinkedList.h"


//��������
DuLinkedList IndexduList(DuLinkedList head, int n)
{
    DuLinkedList Index2;
    Index2 = head;
    int i=0;
    while(i<n-1 && Index2!=NULL)
    {
        Index2=Index2->next;
        i++;
    }
    return Index2;
}

//��β�巨����˫���б�
DuLinkedList *Creat_DuList_tail (DuLinkedList *head, int number)
{
	DuLinkedList node;
	DuLinkedList end;
	end = *head;
	int num,i;
	for( i=0;i<number;i++)
	{
		node=(DuLinkedList)malloc(sizeof(DuLNode));
		printf("Input the number you want:");
		scanf("%d",&num);
		node->data=num;
		end->next=node;
		node->prior=end;
		end=node;
	}
	end->next=NULL;
	*head=(*head)->next;
	(*head)->prior=NULL;
	return head;
 }


void PrintDuList(DuLinkedList head)  /*���ÿ���ڵ��������*/
{
    DuLinkedList index1;
    index1 = head;
    while(index1->next!=NULL)
    {
        printf("%d<->",index1->data);
        index1=index1->next;
    }
    printf("%d",index1->data);
}


void draw1()
{
	printf("\t|**********************************************|\n");
	printf("\t|*              ˫����ATD                     *|\n");
	printf("\t|*           ������Ҫ�������                 *|\n");
	printf("\t|*          ������β�巨�������              *|\n");
	printf("\t|**********************************************|\n");
}

void draw2()
{
	printf("\t|**********************************************|\n");
	printf("\t|*          1.����ĳ�ʼ����                  *|\n");
	printf("\t|*          2.��������                      *|\n");
	printf("\t|*          3.��qǰ����ڵ�                   *|\n");
	printf("\t|*          4.��q�����ڵ�                   *|\n");
	printf("\t|*          5.�����������                  *|\n");
	printf("\t|**********************************************|\n");
	printf("��������ѡ�����(1-5):\n");
}


int main()
{
    DuLinkedList *head_adress;
    head_adress = (DuLinkedList*)malloc(sizeof(DuLinkedList)); //�����ڴ�
    *head_adress=(DuLinkedList)malloc(sizeof(DuLNode));
	int node;
	draw1();
    printf("������Ҫ�ӵĽڵ�ĸ�����\n");  //û���ļ����ܶ��Ż������Բ���
    scanf("%d",&node);
    head_adress=Creat_DuList_tail(head_adress, node);
	printf("��������������Ϊ��\n");
	PrintDuList(*head_adress);
	system("pause");
	system("cls");
	draw2();
	int number2;
    scanf("%d",&number2);
    while(number2<1 || number2>10)
    {
        puts("������������ȷ�����֣�");
        scanf("%d",&number2);
    }
    switch(number2)
    {
        case(1):
            {
                InitList_DuL(head_adress);
                system("pause");
                break;
            }
        case(2):
            {
                DestroyList_DuL(head_adress);
                system("pause");
                break;
            }
         case(3):
            {
                int judge;  //�������ĺ����ƣ�������������Ȼ����⡣
                DuLinkedList Index2,q;
                Index2 = (DuLinkedList)malloc(sizeof(DuLNode));
                printf("������Ҫ���ڵڼ����ڵ�ǰ(0<x<%d)",node+1);
                scanf("%d",&judge);
                while(judge<1 || judge>node+1)
                {
                    puts("������������ȷ�����֣�");
                    scanf("%d",&judge);
                }
                Index2=IndexduList( *head_adress,  judge);
                q = (DuLinkedList)malloc(sizeof(DuLNode));
                InsertBeforeList_DuL(Index2, q);
                PrintDuList(*head_adress);
                system("pause");
                break;
            }
        case(4):
            {
                int judge;
                DuLinkedList Index2,q;
                Index2 = (DuLinkedList)malloc(sizeof(DuLNode));
                printf("������Ҫ���ڵڼ����ڵ��(0<x<%d)",node+1);
                scanf("%d",&judge);
                while(judge<1 || judge>node+1)
                {
                    puts("������������ȷ�����֣�");
                    scanf("%d",&judge);
                }
                Index2=IndexduList( *head_adress,  judge);
                q = (DuLinkedList)malloc(sizeof(DuLNode));
                InsertAfterList_DuL(Index2, q);
                PrintDuList(*head_adress);
                system("pause");
                break;
                }
        case(5):
            {
                PrintDuList(*head_adress);
                system("pause");
                break;
            }
}
    return 0;
}
