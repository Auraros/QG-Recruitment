#include "../head/duLinkedList.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/**
 *  @name        : Status InitList_DuL(DuLinkedList *L)
 *	@description : initialize an empty linked list with only the head node
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList_DuL(DuLinkedList *L) {
	(*L)->next=NULL;
	printf("初始化成功。");
	return SUCCESS;
}

/**
 *  @name        : void DestroyList_DuL(DuLinkedList *L)
 *	@description : destroy a linked list
 *	@param		 : L(the head node)
 *	@return		 : status
 *  @notice      : None
 */
void DestroyList_DuL(DuLinkedList *L) {
	DuLinkedList psave;
    while(*L)     /*使用循环遍历整个链表，使用free函数对每一个结点进行释放*/
    	{
    	    psave=(*L)->next;
    	    free(*L);
    	    *L=psave;
    	}
    printf("销毁成功。");
}

/**
 *  @name        : Status InsertBeforeList_DuL(DuLNode *p, LNode *q)
 *	@description : insert node q before node p
 *	@param		 : p, q
 *	@return		 : status
 *  @notice      : None
 */
Status InsertBeforeList_DuL(DuLNode *p, DuLNode *q) {
	q = (DuLNode*)malloc(sizeof(DuLNode));
	DuLinkedList r; /*原来p的上一个节点*/
	r = p->prior;
	int num;
	if(p!=NULL)  /*如果p不是空*/
	{
	    printf("请输入你想要的数据：");
	    scanf("%d",&num);
		q->prior=p->prior;
		q->data=num;
		r->next=q;
		p->prior=q;
		q->next=p;
	 }
	 return SUCCESS;
}

/**
 *  @name        : Status InsertAfterList_DuL(DuLNode *p, DuLNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : status
 *  @notice      : None
 */
Status InsertAfterList_DuL(DuLNode *p, DuLNode *q) {
	q = (DuLNode*)malloc(sizeof(DuLNode));
	DuLinkedList r; /*原来p的下一个节点*/
	r = p->next;
	int num;
	if(p!=NULL)  /*如果p不是空*/
	{
        printf("请输入你想要的数据：");
	    scanf("%d",&num);
		q->next=p->next;
		q->data=num;
		r->prior=q;
		p->next=q;
		q->prior=p;
	}
	return SUCCESS;
}

/**
 *  @name        : Status DeleteList_DuL(DuLNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : status
 *  @notice      : None
 */
Status DeleteList_DuL(DuLNode *p, ElemType *e) {
	DuLinkedList del,next;
	if(p!=NULL && p->next!=NULL && p->next->next!=NULL)
	{
		del=p->next;
		next=del->next;
		*e = del->data;
		p->next=del->next;
		next->prior=p;
	}
	return SUCCESS;
}

/**
 *  @name        : void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit
 *	@return		 : Status
 *  @notice      : None
 */
void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e)) {
	DuLinkedList pnode = L;
	while(pnode != NULL)
	{
		(*visit)(pnode->data);
		pnode = pnode->next;
	}
}

