/***********************************************************
##filename   : main.c
##author     : Li Weile
##create time : 2019/3/23
************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"..\head\duLinkedList.h"


//用于索引
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

//用尾插法创建双向列表
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


void PrintDuList(DuLinkedList head)  /*输出每个节点的数据域*/
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
	printf("\t|*              双链表ATD                     *|\n");
	printf("\t|*           首先需要添加链表                 *|\n");
	printf("\t|*          方法：尾插法添加链表              *|\n");
	printf("\t|**********************************************|\n");
}

void draw2()
{
	printf("\t|**********************************************|\n");
	printf("\t|*          1.链表的初始化。                  *|\n");
	printf("\t|*          2.销毁链表。                      *|\n");
	printf("\t|*          3.在q前插入节点                   *|\n");
	printf("\t|*          4.在q后插入节点                   *|\n");
	printf("\t|*          5.遍历输出链表。                  *|\n");
	printf("\t|**********************************************|\n");
	printf("请输入所选的序号(1-5):\n");
}


int main()
{
    DuLinkedList *head_adress;
    head_adress = (DuLinkedList*)malloc(sizeof(DuLinkedList)); //分配内存
    *head_adress=(DuLinkedList)malloc(sizeof(DuLNode));
	int node;
	draw1();
    printf("输入你要加的节点的个数：\n");  //没来的及做很多优化处理，对不起
    scanf("%d",&node);
    head_adress=Creat_DuList_tail(head_adress, node);
	printf("你所建立的链表为：\n");
	PrintDuList(*head_adress);
	system("pause");
	system("cls");
	draw2();
	int number2;
    scanf("%d",&number2);
    while(number2<1 || number2>10)
    {
        puts("请重新输入正确的数字：");
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
                int judge;  //第三第四很类似，都是先索引，然后求解。
                DuLinkedList Index2,q;
                Index2 = (DuLinkedList)malloc(sizeof(DuLNode));
                printf("输入你要插在第几个节点前(0<x<%d)",node+1);
                scanf("%d",&judge);
                while(judge<1 || judge>node+1)
                {
                    puts("请重新输入正确的数字：");
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
                printf("输入你要插在第几个节点后(0<x<%d)",node+1);
                scanf("%d",&judge);
                while(judge<1 || judge>node+1)
                {
                    puts("请重新输入正确的数字：");
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
