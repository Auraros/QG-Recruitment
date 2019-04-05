#include "../head/AQueue.h"
#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void InitAQueue(AQueue *Q){   //��ʼ������
	int i;
	for (i=0; i<MAXQUEUE;i++)      //ʹ��ѭ��Ϊÿһ��data���ٿռ� 
		Q->data[i] = (void*)malloc(Q->length);
	Q->front = Q->rear = 0;    
	printf("\n��ʼ���ɹ�.\n");
}

void DestoryAQueue(AQueue *Q){  //�ݻٶ���
	int i;
	for(i = 0; i<MAXQUEUE; i++)  //��ÿһ��data�Ŀռ��ͷŵ� 
		free(Q->data[i]);
	printf("�ݻٳɹ���\n");
	return;	
}

Status IsFullAQueue(const AQueue *Q){  //�������Ƿ����� 
	if((Q->rear+1) % MAXQUEUE == Q->front){  //��ʽ 
		printf("\n�ö���������\n"); 
		return TRUE;}
	else{
		printf("\n������û����\n"); 
		return FALSE;}
}

Status IsEmptyAQueue(const AQueue *Q){
	if (Q->front == Q->rear){   //ͷָ���βָ����� 
		printf("\n�ö���Ϊ��.\n");
		return TRUE;}
	else {
		printf("\n�ö��в�Ϊ�ա�\n");
		return FALSE;}
} 

Status GetHeadAQueue(AQueue *Q, void *e){ //�鿴��ͷԪ�� 
	if (Q->front == Q->rear){   //�ж��Ƿ�Ϊ�� 
		printf("�ö���Ϊ�գ�û�ж�ͷԪ�ء�\n"); 
		return FALSE;}
	int i = Q->front; 
	i = (i + 1) % MAXQUEUE;  //��Ϊͷָ��ָ��գ�����ͷָ��+1���Ƕ�ͷԪ�� 
	memcpy(e, Q->data[i], Q->length);
	printf("\n�ö��е�ͷԪ���ǣ�");
	if(Q->length == sizeof(char))    //if�ж�data����ʲô���� 
		printf("%c\n", *(char*)e);
	else if (Q->length == sizeof(double))
		printf("%lf\n", *(double*)e);
	else if (Q->length == sizeof(int))
		printf("%d\n", *(int*)e);
	return TRUE;
}


int LengthAQueue(AQueue *Q){    //ȷ�����г���
	int k;
	k = (Q->rear - Q->front + MAXQUEUE) % MAXQUEUE;  //��ʽ 
	return (k); 
}

Status EnAQueue(AQueue *Q, void *data){  //��Ӳ��� 
	if ((Q->rear+1) % MAXQUEUE == Q->front){
		printf("����������ӡ�\n");
		return FALSE;
	}
	else{
		Q->rear = (Q->rear + 1) % MAXQUEUE;   
		memcpy(Q->data[Q->rear], data, Q->length);  //���� 
		return TRUE;
	}
}

Status DeAQueue(AQueue *Q){   //���Ӳ��� 
	if(Q->front == Q->rear){
		printf("\n�ӿգ����ܳ��ӡ�\n");
		return FALSE;
	} 
	else{
		Q->front = (Q->front + 1) % MAXQUEUE;  //ͷָ��ָ����һ����Ԫ�� 
		return TRUE;
	}
}

void ClearAQueue(AQueue *Q){   //��ն��� 
	if(Q->front == Q->rear){
		printf("�ö����Ѿ�Ϊ�ա�\n");
		return ;}
	Q->front = 0;
	Q->rear = 0;
	printf("��ն��гɹ���\n");
} 

Status TraverseAQueue(const AQueue *Q, void (*foo)(void *q, int size)){  //������������ 
	if (Q->front == Q->rear){
		printf("�ö���Ϊ�ա�\n");
		return FALSE;}
	int i = Q->front + 1;
	printf("\n");
	while (i <= (MAXQUEUE - Q->front + Q->rear) % MAXQUEUE ) {  //���iû�б�������β 
		foo(Q->data[i], Q->length);	
		i = (i + 1) % MAXQUEUE;
	}
	printf("NULL");
	printf("\n");
	return TRUE;
}

void APrint(void *q, int size){  //�� ӡ���� 
	if(size == sizeof(char))    //���ݴ��治ͬ�����͵ı��������д�ӡ 
		printf("%c", *(char*)q);
	else if (size == sizeof(double))
		printf("%lf", *(double*)q);
	else if (size == sizeof(int))
		printf("%d", *(int*)q);
	printf("-<");
} 
