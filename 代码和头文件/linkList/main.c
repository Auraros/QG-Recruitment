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
void PrintList(LinkedList head)  /*输出每个节点的数据域*/
{
    LinkedList index1;
    index1 = head;
    if(head->next==NULL || head==NULL)  //对空链表进行处理
        printf("该链表为空");
    while(index1->next!=NULL)   //循环遍历输出
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
    while(i<n-1 && Index2!=NULL) //利用循环，遍历到想要的节点的位置
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
	printf("\t|*              单链表ATD                     *|\n");
	printf("\t|*           首先需要添加链表                 *|\n");
	printf("\t|*          方法：尾插法添加链表              *|\n");
	printf("\t|**********************************************|\n");
}

/**
 *  @name        : void draw4()
 *	@description : the menu of the ATD
 */
void draw4()
{
	printf("\t|**********************************************|\n");
	printf("\t|*          1.链表的初始化。                  *|\n");
	printf("\t|*          2.销毁链表。                      *|\n");
	printf("\t|*          3.插入节点。                      *|\n");
	printf("\t|*          4.删除节点后一个并赋值。          *|\n");
	printf("\t|*          5.遍历输出链表。                  *|\n");
	printf("\t|*          6.查询链表。                      *|\n");
	printf("\t|*          7.链表的逆序。                    *|\n");
	printf("\t|*          8.判断是否为循环链表。            *|\n");
	printf("\t|*          9.颠倒偶数节点。                  *|\n");
	printf("\t|*          10.寻找中间节点。                 *|\n");
	printf("\t|**********************************************|\n");
	printf("请输入所选的序号(1-10):\n");
}



int main()
{
    LinkedList *head_adress;    //定义一个指向头节点的指针
    head_adress = (LinkedList*)malloc(sizeof(LinkedList)); //为这个指针分配内存
    *head_adress = (LinkedList)malloc(sizeof(LNode));
	int node;
	draw3();
    printf("输入你要加的节点的个数：");  //用户输入想要的节点数目
    scanf("%d",&node);
    head_adress=Create_list_tail(head_adress,node);
	printf("你所建立的链表为：\n");
	PrintList(*head_adress);    //输出用户建立的链表
	system("pause");
	system("cls");
    draw4();
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
                InitList(head_adress);  //初始化链表
                system("pause");
                break;
            }
        case(2):
            {
                DestroyList(head_adress); //摧毁链表
                system("pause");
                break;
            }
        case(3):
            {
                int judge;
                LinkedList Index2,q;
                Index2 = (LinkedList)malloc(sizeof(LNode));
                printf("输入你要插在第几个节点后(0<x<%d)",node+1);
                scanf("%d",&judge);                    ////想法：用户先输入想要操作的节点的位置
                while(judge<1 || judge>node+1)
                {
                    puts("请重新输入正确的数字：");
                    scanf("%d",&judge);
                }
                Index2=IndexList( *head_adress,  judge);   //利用索引返回该节点的指针
                q = (LinkedList)malloc(sizeof(LNode));
                InsertList(Index2, q);              //利用该指针进行操作
                PrintList(*head_adress);
                system("pause");
                break;
            }
        case(4):
            {
                int judge;
                LinkedList Index3;
                int *e;
                Index3 = (LinkedList)malloc(sizeof(LNode));    //操作同上
                printf("输入你要删除第几个节点(0<x<%d)",node);
                scanf("%d",&judge);
                while(judge<1 || judge>node+1)
                {
                    puts("请重新输入正确的数字：");
                    scanf("%d",&judge);
                }
                Index3=IndexList(*head_adress, judge);
                DeleteList(Index3, e);    //这里的话e，我还没想到要如何使用
                PrintList(*head_adress);
                system("pause");
                break;
            }
        case(5):
            {
                PrintList(*head_adress);   //输出每个值
                system("pause");
                break;
            }
        case(6):
            {
                int value;
                puts("输入你想要查询的值：");
                scanf("%d",&value);
                SearchList(*head_adress, value);   //找出用户要找的节点，否则输出没有
                system("pause");
                break;
            }
        case(7):
            {
                ReverseList(head_adress);  //倒序节点
                PrintList(*head_adress);
                system("pause");
                break;
            }
        case(8):
            {
                IsLoopList(*head_adress);  //判断是否是环
                system("pause");
                break;
            }
        case(9):
            {
                *head_adress=ReverseEvenList(head_adress); //两个节点两两交换
                system("pause");
                PrintList(*head_adress);
                break;
            }
        case(10):
            {
                LinkedList low;      //定义慢指阵
                low=(LinkedList)malloc(sizeof(LNode));
                low=FindMidNode(head_adress);
                printf("%d",low->data);
                system("pause");
                break;
            }

    }

 }
