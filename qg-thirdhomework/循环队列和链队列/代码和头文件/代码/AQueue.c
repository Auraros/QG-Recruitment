#include "../head/AQueue.h"
#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void InitAQueue(AQueue *Q){   //初始化队列
	int i;
	for (i=0; i<MAXQUEUE;i++)      //使用循环为每一个data开辟空间 
		Q->data[i] = (void*)malloc(Q->length);
	Q->front = Q->rear = 0;    
	printf("\n初始化成功.\n");
}

void DestoryAQueue(AQueue *Q){  //摧毁队列
	int i;
	for(i = 0; i<MAXQUEUE; i++)  //将每一个data的空间释放掉 
		free(Q->data[i]);
	printf("摧毁成功。\n");
	return;	
}

Status IsFullAQueue(const AQueue *Q){  //检查队列是否已满 
	if((Q->rear+1) % MAXQUEUE == Q->front){  //公式 
		printf("\n该队列已满。\n"); 
		return TRUE;}
	else{
		printf("\n该链表还没满。\n"); 
		return FALSE;}
}

Status IsEmptyAQueue(const AQueue *Q){
	if (Q->front == Q->rear){   //头指针和尾指针相等 
		printf("\n该队列为空.\n");
		return TRUE;}
	else {
		printf("\n该队列不为空。\n");
		return FALSE;}
} 

Status GetHeadAQueue(AQueue *Q, void *e){ //查看队头元素 
	if (Q->front == Q->rear){   //判断是否为空 
		printf("该队列为空，没有对头元素。\n"); 
		return FALSE;}
	int i = Q->front; 
	i = (i + 1) % MAXQUEUE;  //因为头指针指向空，所以头指针+1就是队头元素 
	memcpy(e, Q->data[i], Q->length);
	printf("\n该队列的头元素是：");
	if(Q->length == sizeof(char))    //if判断data属于什么类型 
		printf("%c\n", *(char*)e);
	else if (Q->length == sizeof(double))
		printf("%lf\n", *(double*)e);
	else if (Q->length == sizeof(int))
		printf("%d\n", *(int*)e);
	return TRUE;
}


int LengthAQueue(AQueue *Q){    //确定队列长度
	int k;
	k = (Q->rear - Q->front + MAXQUEUE) % MAXQUEUE;  //公式 
	return (k); 
}

Status EnAQueue(AQueue *Q, void *data){  //入队操作 
	if ((Q->rear+1) % MAXQUEUE == Q->front){
		printf("队满不能入队。\n");
		return FALSE;
	}
	else{
		Q->rear = (Q->rear + 1) % MAXQUEUE;   
		memcpy(Q->data[Q->rear], data, Q->length);  //拷贝 
		return TRUE;
	}
}

Status DeAQueue(AQueue *Q){   //出队操作 
	if(Q->front == Q->rear){
		printf("\n队空，不能出队。\n");
		return FALSE;
	} 
	else{
		Q->front = (Q->front + 1) % MAXQUEUE;  //头指针指向下一个队元素 
		return TRUE;
	}
}

void ClearAQueue(AQueue *Q){   //清空队列 
	if(Q->front == Q->rear){
		printf("该队列已经为空。\n");
		return ;}
	Q->front = 0;
	Q->rear = 0;
	printf("清空队列成功。\n");
} 

Status TraverseAQueue(const AQueue *Q, void (*foo)(void *q, int size)){  //遍历函数操作 
	if (Q->front == Q->rear){
		printf("该队列为空。\n");
		return FALSE;}
	int i = Q->front + 1;
	printf("\n");
	while (i <= (MAXQUEUE - Q->front + Q->rear) % MAXQUEUE ) {  //如果i没有遍历到队尾 
		foo(Q->data[i], Q->length);	
		i = (i + 1) % MAXQUEUE;
	}
	printf("NULL");
	printf("\n");
	return TRUE;
}

void APrint(void *q, int size){  //打 印队列 
	if(size == sizeof(char))    //根据储存不同的类型的变量来进行打印 
		printf("%c", *(char*)q);
	else if (size == sizeof(double))
		printf("%lf", *(double*)q);
	else if (size == sizeof(int))
		printf("%d", *(int*)q);
	printf("-<");
} 
