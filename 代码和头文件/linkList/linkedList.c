#include "../head/linkedList.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 *  @name        : Status InitList(LinkList *L);
 *	@description : initialize an empty linked list with only the head node without value
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList(LinkedList  *L) {
     (*L)=NULL;
     printf("��ʼ���ɹ���");  //��ʼ������
	 return SUCCESS;
}

/**
 *  @name        : void DestroyList(LinkedList *L)
 *	@description : destroy a linked list, free all the nodes
 *	@param		 : L(the head node)
 *	@return		 : None
 *  @notice      : None
 */
void DestroyList(LinkedList *L) {
	LinkedList psave;
    while(*L)     /*ʹ��ѭ��������������ʹ��free������ÿһ���������ͷ�*/
    	{
    	    psave=(*L)->next;
    	    free(*L);
    	    *L=psave;
    	}
    printf("���ٳɹ���");
}

/**
 *  @name        : Status InsertList(LNode *p, LNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : Status
 *  @notice      : None
 */
Status InsertList(LNode *p, LNode *q) {
	if (p!=NULL)  /*�ж�p�ڵ��Ƿ����*/
	{
		puts("����Ҫ�����ֵ��");
		scanf("%d",&q->data);     //����nextָ����в���
		q->next=p->next;
		p->next=q;
		puts("����ɹ���");
	}
	else
		puts("�ڵ㲻���ڡ�\n");
	return SUCCESS;

}
/**
 *  @name        : Status DeleteList(LNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : Status
 *  @notice      : None
 */
Status DeleteList(LNode *p, ElemType *e){
	if(p!=NULL)
	{
	    //�Ƚ�ֵ��ֵ��ָ�룬�ڽ�����������������ڲ��������г����˴�����ʱ��û�н��
		p->next=p->next->next;
	}
	else
		puts("û�иýڵ㡣\n");
    printf("ɾ���ɹ���");
	return SUCCESS;
}

/**
 *  @name        : void TraverseList(LinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit
 *	@return		 : None
 *  @notice      : None
 */
void TraverseList(LinkedList L, void (*visit)(ElemType e)) {
	LinkedList pnode = L;            //visitΪһ������ָ������ʹ�õ�ʱ�����Ǳ��������˴���
	while(pnode != NULL)
	{
		(*visit)(pnode->data);
		pnode = pnode->next;
	}
}

/**
 *  @name        : Status SearchList(LinkedList L, ElemType e)
 *	@description : find the first node in the linked list according to e
 *	@param		 : L(the head node), e
 *	@return		 : Status
 *  @notice      : None
 */
Status SearchList(LinkedList L, ElemType e){
	LinkedList pnode;
	pnode=(LinkedList)malloc(sizeof(LNode));
	pnode->next = L->next;
	int index=1,flag=0;            //flag��������ڵ��Ƿ����
	while (pnode!=NULL&&pnode->next!=NULL)
	{
	    if(pnode->data!=e)
		{
		    pnode=pnode->next;
            index++;
        }
        else
        {
            flag=1;
            break;
        }
	}
	if(flag==1)
    {
        printf ("��%d���ڵ��ֵ��%d��ȡ�\n",index,e);
    }
    else{
        printf ("û����ҪѰ�ҵĽڵ㡣");
    }
	return SUCCESS;
}


/**
 *  @name        : Status ReverseList(LinkedList *L)
 *	@description : reverse the linked list
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status ReverseList(LinkedList *L) {
	LinkedList head,node,pre;
	head=*L;
	node=head->next;
	while(node)
	{
		pre=node->next;
		node->next=head;
		head=node;
		node=pre;
	}
	(*L)->next=NULL;
	*L=head;
	return SUCCESS;
}

/**
 *  @name        : Status IsLoopList(LinkedList L)
 *	@description : judge whether the linked list is looped
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status IsLoopList(LinkedList L) {
	if(!L)
        return 0;
    LinkedList fast,slow;
    while(1)
    {
        if(!fast || fast->next){
            printf("��������ѭ������");
            return ERROR;}
        else if (fast==slow || fast->next == slow){
            printf("��������һ��ѭ������");
            return SUCCESS;
        }
        else {
            slow = slow->next;
            fast = fast->next->next;
        }
    }
}

/**
 *  @name        : LNode* ReverseEvenList(LinkedList *L)
 *	@description : reverse the nodes which value is an even number in the linked list, input: 1 -> 2 -> 3 -> 4  output: 2 -> 1 -> 4 -> 3
 *	@param		 : L(the head node)
 *	@return		 : LNode(the new head node)
 *  @notice      : choose to finish
 */
LNode *ReverseEvenList(LinkedList *L) {
	LinkedList front = (LinkedList)malloc(sizeof(LNode));
	front->next = *L;
	LinkedList t = front, t1=NULL, t2=NULL;
	while(t && t->next && t->next->next){
        t1 = t->next;
        t2 = t1->next;
        t->next = t2;
        t1->next = t2->next;
        t2->next = t1;
        t = t1;
	}
	t=front->next;
	free(front);
	return t;
}

/**
 *  @name        : LNode* FindMidNode(LinkedList *L)
 *	@description : find the middle node in the linked list
 *	@param		 : L(the head node)
 *	@return		 : LNode
 *  @notice      : choose to finish
 */
LNode* FindMidNode(LinkedList *L) {
	LinkedList fast=*L;   /*��ָ������������ָ����һ������ָ�����꣬��ָ������м�ڵ��ϡ�*/
	LinkedList slow=*L;
	while(fast)
	{
		if(fast->next!=NULL)
			fast=fast->next->next;
		else
			break;
		slow=slow->next;
	}
	return slow;
}
