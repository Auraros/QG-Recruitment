#include"../head/LQueue.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//��ѭ�������кܶ����Ƶĵط� 
void InitLQueue(LQueue *Q){ //��ʼ��
	Node *p = (Node *)malloc(sizeof(Node));   //�Խڵ�p�����ڴ� 
	if(NULL == p)
		return;
	p->next = NULL; 
	Q->front = p;  //��ͷָ���βָ�붼ָ��p 
	Q->rear = p;
	printf("\n��ʼ���ɹ���\n");
	return;
}

void DestoryLQueue(LQueue *Q){  //�ݻٶ��� 
	Node *p, *q;
	Q->rear = Q->front;   
	p = Q->front->next; 
	while (NULL != p) {  //����qָ��һ�����ͷŽڵ� 
		q = p;
		p = p->next;
		free(q);
	}
	free(p);
	free(Q->front);  //����ͷָ��Ͷ�βָ���ͷ� 
	printf("\n�ݻٶ��гɹ���\n");
} 


Status IsEmptyLQueue(const LQueue *Q){   //�ж϶����Ƿ�Ϊ�� 
	if(Q->front == Q->rear){     //��ʽ 
		printf("�ö���Ϊ�ա�\n");
		return TRUE;}
	else {
		printf("�ö��в�Ϊ�ա�\n");
		return FALSE;}
}


Status GetHeadLQueue(LQueue *Q, void *e){  //ȡ����ͷԪ�� 
	if(Q->front == Q->rear){
		printf("�ö���Ϊ��"); 
		return FALSE;} 
	printf("�ö��еĶ�ͷ����Ϊ��");
	memcpy(e, Q->front->next->data, Q->length);  //���� 
	if (Q->length == sizeof(double))   //���ݲ�ͬ���ͽ������ 
		printf("%lf\n", *(double *)e);
	if (Q->length == sizeof(char))
		printf("%c\n", *(char *)e);
	if (Q->length == sizeof (int))
		printf("%d\n", *(int *)e);
	return TRUE;	
}


int LengthLQueue(LQueue *Q){   //�ж϶��еĳ��� 
	int length;
	Node *p = (Node *)malloc(sizeof(Node));  //��һ���ڵ�p 
	p = Q->front;           //pָ���ͷ 
	for(length = 0; p != Q->rear; length++)  //����ѭ������p����βָ��ʱ��lengthΪ���� 
		p = p->next;
	return length;	
}


Status EnLQueue(LQueue *Q, void *data){  //��� 
	Node *p = (Node*)malloc(sizeof(Node));  //����һ���ڵ� 
	if(NULL == p)    
		return FALSE;       
	p->data = (void*)malloc(Q->length);  //Ϊ�����򿪱ٿռ� 
	memcpy(p->data, data, Q->length);  //���� 
	p->next = NULL;      //ָ�� 
	Q->rear->next = p;
	Q->rear = p;
	return TRUE;
}


void ClearLQueue(LQueue *Q) { //��ն��� 
	if (Q->front == Q->rear){
		printf("�ö����Ѿ��ǿն��С�\n"); 
		return;}
	Node *p, *q;
	Q->rear = Q->front;   //һ����ѭ���ͷŽڵ� 
	p = Q->front->next; 
	while (NULL != p) {
		q = p;
		p = p->next;
		free(q);
	}
	free(p);
	printf("\n��ն��гɹ���") ;
	return;
}

Status DeLQueue(LQueue *Q){   //���� 
	if(Q->front == Q->rear){
		printf("�ö����ǿն��У����ܳ��ӡ�");
		return FALSE;}
	Node *p = (Node *)malloc(sizeof(Node));
	p = Q->front->next;       //ָ���ͷ����һ���ڵ� 
	Q->front->next = p->next;   //����ͷ����һ���ڵ�ָ��p�Ľڵ� 
	if (NULL == Q->front->next)  //���ֻ��һ��Ԫ����� 
		Q->rear = Q->front;
	free(p);
	return TRUE;
}

int flag;
Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q)){ //����������� 
	if (Q->front == Q->rear){
		printf("�ö���Ϊ�ն��С����ܽ��иò�����\n");
		return FALSE;}
		if (Q->length == sizeof(double))
			flag = 1;
		if (Q->length == sizeof(char))
			flag = 2;
		if (Q->length == sizeof (int))
			flag = 3;
		Node* p = (void *)malloc(Q->length); 
		p = Q->front->next;  //pָ���ͷָ��ָ��Ľڵ� 
		printf("\n�ö��е�Ԫ��Ϊ��");
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
