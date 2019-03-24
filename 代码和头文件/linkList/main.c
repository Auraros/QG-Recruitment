/***********************************************************
##filename   : main.c
##author     : Li Weile
##create time : 2019/3/23
************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"..\head\linkedList.h"
#include"..\head\linkedList.h"

/**
 *  @name        : void PrintList(LinkedList head)
 *	@description : print every value of node
 *	@param		 : head(the head node), index1
 *	@return		 : void
 *  @notice      : None
 */
void PrintList(LinkedList head)  /*���ÿ���ڵ��������*/
{
    LinkedList index1;
    index1 = head;
    if(head->next==NULL || head==NULL)  //�Կ�������д���
        printf("������Ϊ��");
    while(index1->next!=NULL)   //ѭ���������
    {
        printf("%d->",index1->data);
        index1=index1->next;
    }
    printf("%d",index1->data);
}


/**
 *  @name        : LinkedList IndexList(LinkedList head, int n)
 *	@description : find the node you want
 *	@param		 : head(the head node), Index2
 *	@return		 : Index2
 *  @notice      : None
 */
LinkedList IndexList(LinkedList head, int n)
{
    LinkedList Index2;
    Index2 = head->next;
    int i=0;
    while(i<n-1 && Index2!=NULL) //����ѭ������������Ҫ�Ľڵ��λ��
    {
        Index2=Index2->next;
        i++;
    }
    return Index2;
}

/**
 *  @name        : LinkedList Create_list_tail (LinkedList *head, int number)
 *	@description : create the linkedlist,and input the value
 *	@param		 : head(the head node), number
 *	@return		 : head
 *  @notice      : None
 */
LinkedList *Create_list_tail (LinkedList *head, int number)
{
	LinkedList node=NULL;
	LinkedList end= NULL;
	end = *head;
	node=end;
	int num,i;
	for(i=0;i<number;i++)
	{
		node=(LinkedList)malloc(sizeof(LNode));
		printf("Input the number you want:");
		scanf("%d",&num);
		node->data=num;
		end->next=node;
		end=node;
	}
	end->next=NULL;
	*head=(*head)->next;
	return head;
 }


/**
 *  @name        : void draw3()
 *	@description : the menu of the ATD
 */
void draw3()
{
	printf("\t|**********************************************|\n");
	printf("\t|*              ������ATD                     *|\n");
	printf("\t|*           ������Ҫ�������                 *|\n");
	printf("\t|*          ������β�巨�������              *|\n");
	printf("\t|**********************************************|\n");
}

/**
 *  @name        : void draw4()
 *	@description : the menu of the ATD
 */
void draw4()
{
	printf("\t|**********************************************|\n");
	printf("\t|*          1.����ĳ�ʼ����                  *|\n");
	printf("\t|*          2.��������                      *|\n");
	printf("\t|*          3.����ڵ㡣                      *|\n");
	printf("\t|*          4.ɾ���ڵ��һ������ֵ��          *|\n");
	printf("\t|*          5.�����������                  *|\n");
	printf("\t|*          6.��ѯ����                      *|\n");
	printf("\t|*          7.���������                    *|\n");
	printf("\t|*          8.�ж��Ƿ�Ϊѭ������            *|\n");
	printf("\t|*          9.�ߵ�ż���ڵ㡣                  *|\n");
	printf("\t|*          10.Ѱ���м�ڵ㡣                 *|\n");
	printf("\t|**********************************************|\n");
	printf("��������ѡ�����(1-10):\n");
}



int main()
{
    LinkedList *head_adress;    //����һ��ָ��ͷ�ڵ��ָ��
    head_adress = (LinkedList*)malloc(sizeof(LinkedList)); //Ϊ���ָ������ڴ�
    *head_adress = (LinkedList)malloc(sizeof(LNode));
	int node;
	draw3();
    printf("������Ҫ�ӵĽڵ�ĸ�����");  //�û�������Ҫ�Ľڵ���Ŀ
    scanf("%d",&node);
    head_adress=Create_list_tail(head_adress,node);
	printf("��������������Ϊ��\n");
	PrintList(*head_adress);    //����û�����������
	system("pause");
	system("cls");
    draw4();
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
                InitList(head_adress);  //��ʼ������
                system("pause");
                break;
            }
        case(2):
            {
                DestroyList(head_adress); //�ݻ�����
                system("pause");
                break;
            }
        case(3):
            {
                int judge;
                LinkedList Index2,q;
                Index2 = (LinkedList)malloc(sizeof(LNode));
                printf("������Ҫ���ڵڼ����ڵ��(0<x<%d)",node+1);
                scanf("%d",&judge);                    ////�뷨���û���������Ҫ�����Ľڵ��λ��
                while(judge<1 || judge>node+1)
                {
                    puts("������������ȷ�����֣�");
                    scanf("%d",&judge);
                }
                Index2=IndexList( *head_adress,  judge);   //�����������ظýڵ��ָ��
                q = (LinkedList)malloc(sizeof(LNode));
                InsertList(Index2, q);              //���ø�ָ����в���
                PrintList(*head_adress);
                system("pause");
                break;
            }
        case(4):
            {
                int judge;
                LinkedList Index3;
                int *e;
                Index3 = (LinkedList)malloc(sizeof(LNode));    //����ͬ��
                printf("������Ҫɾ���ڼ����ڵ�(0<x<%d)",node);
                scanf("%d",&judge);
                while(judge<1 || judge>node+1)
                {
                    puts("������������ȷ�����֣�");
                    scanf("%d",&judge);
                }
                Index3=IndexList(*head_adress, judge);
                DeleteList(Index3, e);    //����Ļ�e���һ�û�뵽Ҫ���ʹ��
                PrintList(*head_adress);
                system("pause");
                break;
            }
        case(5):
            {
                PrintList(*head_adress);   //���ÿ��ֵ
                system("pause");
                break;
            }
        case(6):
            {
                int value;
                puts("��������Ҫ��ѯ��ֵ��");
                scanf("%d",&value);
                SearchList(*head_adress, value);   //�ҳ��û�Ҫ�ҵĽڵ㣬�������û��
                system("pause");
                break;
            }
        case(7):
            {
                ReverseList(head_adress);  //����ڵ�
                PrintList(*head_adress);
                system("pause");
                break;
            }
        case(8):
            {
                IsLoopList(*head_adress);  //�ж��Ƿ��ǻ�
                system("pause");
                break;
            }
        case(9):
            {
                *head_adress=ReverseEvenList(head_adress); //�����ڵ���������
                system("pause");
                PrintList(*head_adress);
                break;
            }
        case(10):
            {
                LinkedList low;      //������ָ��
                low=(LinkedList)malloc(sizeof(LNode));
                low=FindMidNode(head_adress);
                printf("%d",low->data);
                system("pause");
                break;
            }

    }

 }
