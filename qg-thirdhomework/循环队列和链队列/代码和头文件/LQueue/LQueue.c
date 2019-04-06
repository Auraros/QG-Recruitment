#include"../head/LQueue.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//跟循环队列有很多相似的地方 
void InitLQueue(LQueue *Q){ //初始化
	Node *p = (Node *)malloc(sizeof(Node));   //对节点p开辟内存 
	if(NULL == p)
		return;
	p->next = NULL; 
	Q->front = p;  //将头指针和尾指针都指向p 
	Q->rear = p;
	printf("\n初始化成功。\n");
	return;
}

void DestoryLQueue(LQueue *Q){  //摧毁队列 
	Node *p, *q;
	Q->rear = Q->front;   
	p = Q->front->next; 
	while (NULL != p) {  //利用q指针一个个释放节点 
		q = p;
		p = p->next;
		free(q);
	}
	free(p);
	free(Q->front);  //将队头指针和队尾指针释放 
	printf("\n摧毁队列成功。\n");
} 


Status IsEmptyLQueue(const LQueue *Q){   //判断队列是否为空 
	if(Q->front == Q->rear){     //公式 
		printf("该队列为空。\n");
		return TRUE;}
	else {
		printf("该队列不为空。\n");
		return FALSE;}
}


Status GetHeadLQueue(LQueue *Q, void *e){  //取出队头元素 
	if(Q->front == Q->rear){
		printf("该队列为空"); 
		return FALSE;} 
	printf("该队列的队头函数为：");
	memcpy(e, Q->front->next->data, Q->length);  //复制 
	if (Q->length == sizeof(double))   //根据不同类型进行输出 
		printf("%lf\n", *(double *)e);
	if (Q->length == sizeof(char))
		printf("%c\n", *(char *)e);
	if (Q->length == sizeof (int))
		printf("%d\n", *(int *)e);
	return TRUE;	
}


int LengthLQueue(LQueue *Q){   //判断队列的长度 
	int length;
	Node *p = (Node *)malloc(sizeof(Node));  //用一个节点p 
	p = Q->front;           //p指向队头 
	for(length = 0; p != Q->rear; length++)  //利用循环，当p到达尾指针时，length为长度 
		p = p->next;
	return length;	
}


Status EnLQueue(LQueue *Q, void *data){  //入队 
	Node *p = (Node*)malloc(sizeof(Node));  //建立一个节点 
	if(NULL == p)    
		return FALSE;       
	p->data = (void*)malloc(Q->length);  //为数据域开辟空间 
	memcpy(p->data, data, Q->length);  //拷贝 
	p->next = NULL;      //指针 
	Q->rear->next = p;
	Q->rear = p;
	return TRUE;
}


void ClearLQueue(LQueue *Q) { //清空队列 
	if (Q->front == Q->rear){
		printf("该队列已经是空队列。\n"); 
		return;}
	Node *p, *q;
	Q->rear = Q->front;   //一个个循环释放节点 
	p = Q->front->next; 
	while (NULL != p) {
		q = p;
		p = p->next;
		free(q);
	}
	free(p);
	printf("\n清空队列成功。") ;
	return;
}

Status DeLQueue(LQueue *Q){   //出队 
	if(Q->front == Q->rear){
		printf("该队列是空队列，不能出队。");
		return FALSE;}
	Node *p = (Node *)malloc(sizeof(Node));
	p = Q->front->next;       //指向队头的下一个节点 
	Q->front->next = p->next;   //将队头的下一个节点指向p的节点 
	if (NULL == Q->front->next)  //如果只有一个元素情况 
		Q->rear = Q->front;
	free(p);
	return TRUE;
}

int flag;
Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q)){ //遍历输出队列 
	if (Q->front == Q->rear){
		printf("该队列为空队列。不能进行该操作。\n");
		return FALSE;}
		if (Q->length == sizeof(double))
			flag = 1;
		if (Q->length == sizeof(char))
			flag = 2;
		if (Q->length == sizeof (int))
			flag = 3;
		Node* p = (void *)malloc(Q->length); 
		p = Q->front->next;  //p指向队头指针指向的节点 
		printf("\n该队列的元素为：");
		while (p != NULL) { 
			foo(p->data);
			p = p->next;
		}
		printf("NULL\n");
	return TRUE;
}


void LPrint(void *q){
	if (flag == 1)
		printf("%lf", *(double *)q);
	if (flag == 2)
		printf("%c", *(char *)q);
	if (flag == 3)
		printf("%d", *(int *)q);
	printf("-<");
}
