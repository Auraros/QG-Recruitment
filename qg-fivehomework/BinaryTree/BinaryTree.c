#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include "../head/BinaryTree.h"


Status InitBiTree(BiTree *T){
	assert(T);
	if(*T == NULL)     //�жϳ�ʼ���Ƿ�ɹ� 
		return ERROR;
	*T = NULL;   //��ʼ�� 
	return SUCCESS;
} 

Status DestroyBiTree(BiTree *T){
	assert(T);
	if(*T == NULL)
		return ERROR;
	DestroyBiTree(&((*T)->lchild));   //�ݻ���ڵ� 
	DestroyBiTree(&((*T)->rchild));   //�ݻ��ҽ�� 
	free(T);    //�ͷ�T 
	*T = NULL;  //�������Ϊ�� 
}

Status CreateBiTree(BiTree *T){
	char ch;
    scanf("%c", &ch);     //�û������ַ� 
	getchar();
    if(ch == '#')   //�����#����Ϊ�� 
        *T = NULL; 
    else{
        *T = (BiTree)malloc(sizeof(BiTNode));  //����㿪�ٿռ� 
        (*T) -> data = ch;  //��ֵ 
        printf("������%c��������:", ch);  //���㽨�� 
        CreateBiTree(&((*T) -> lchild));  //�ݹ����� 
        printf("������%c��������:", ch);   
        CreateBiTree(&((*T) -> rchild));
    }
}

	
Status visit(TElemType e){
	printf("%c",e);  //��� 
}

Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType e)){  //������� 
	if(T!=NULL){
		visit(T->data);   //��� 
		PreOrderTraverse(T->lchild, visit);  //�������� 
		PreOrderTraverse(T->rchild, visit);  //�����ҽ�� 
	}
}

Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e)){  //������� 
	if(T!=NULL){
		InOrderTraverse(T->lchild, visit); //������ڵ� 
		visit(T->data);    //��� 
		InOrderTraverse(T->rchild, visit); //�����ҽ�� 
	}
}

Status PostOrderTraverse(BiTree T, Status (*visit)(TElemType e)){ //�������� 
	if(T!=NULL){ 
		PostOrderTraverse(T->lchild, visit); //�������ڵ� 
		PostOrderTraverse(T->rchild, visit);  //�����ҽ�� 
		visit(T->data);  //��� 
	}
}

Status LevelOrderTraverse(BiTree T, Status (*visit)(TElemType e)){  //��α��� 
	BiTNode *p;  //��������� 
	SeqQueue Q;   //����һ��ѭ������ 
	Q.front = Q.rear = -1;  //��ʼ������ 
	Q.rear++;   //��� 
	Q.qu[Q.rear]=T;  //�������� 
	while(Q.front!=Q.rear){  //���ǿն��� 
		Q.front = (Q.front+1)%MAXSIZE;  
		p = Q.qu[Q.front];   //��ͷ���� 
		visit(p->data);
		if(p->lchild!=NULL){  //���ӵ�ַ��� 
			Q.rear = (Q.rear+1)%MAXSIZE;
			Q.qu[Q.rear] = p->lchild;
		}
		if(p->rchild != NULL){ //�Һ��ӵ�ַ��� 
			Q.rear = (Q.rear+1)%MAXSIZE;
			Q.qu[Q.rear] = p->rchild;
		}
	}
}

void NRPreOrder_Traverse(BiTree T, Status (*visit)(TElemType e)){  //�ǵݹ��������������
	BiTNode *stack[MAXSIZE], *p;  //����ջ 
	int top;
	if(T == NULL)  //��Ϊ�� 
		return;
	top = 0;
	p=T;
	while(p!=NULL || top!=0){
		while(p!=NULL){
			visit(p->data);  //������Ԫ�� 
			if(top<MAXSIZE -1){  //��ǰָ��p��ջ 
			stack[top]=p;
			top++; 
		}
		else{
			printf("\nջ�����\n");
			return;
		}
		p = p->lchild;  //ָ��ָ������ 
	} 
	if(top<0)  //ջΪ�յ�ʱ�򷵻� 
		return;
	else{
		top--;  //ջ��Ԫ�س�ջ 
		p=stack[top];
		p=p->rchild;  //ָ��ָ��p���Һ��ӽ�� 
		}
	}
}
 
void NRInOrder_Traverse(BiTree T, Status (*visit)(TElemType e)){
	BiTNode *stack[MAXSIZE], *p;  //����ջ 
	int top;
	if(T == NULL)  //��Ϊ�� 
		return;
	top = 0;
	p=T;
	while(p!=NULL || top!=0){
		while(p!=NULL){
			if(top<MAXSIZE -1){  //��ǰָ��p��ջ 
			stack[top]=p;
			top++; 
		}
		else{
			printf("\nջ�����\n");
			return;
		}
		p = p->lchild;  //ָ��ָ������ 
	} 
	if(top<0)  //ջΪ�յ�ʱ�򷵻� 
		return;
	else{
		top--;
		p=stack[top];
		visit(p->data);   //���Ԫ�� 
		p=p->rchild;  //ָ��ָ��p���Һ��ӽ�� 
		}
	}
}

void NRPostOrder_Traverse(BiTree T, Status (*visit)(TElemType e)) {
	StackType  stack[MAXSIZE];  //����ջ 
	BiTree p;
	int top,sign;
	if(T == NULL)  //��Ϊ�� 
		return;
	top = -1;
	p=T;
	while(p!=NULL || top!=-1){
		if(p!=NULL){
			top++;
			stack[top].p = p;
			stack[top].flag=1;
			p=p->lchild;
		}
		else{
			p=stack[top].p;
			sign = stack[top].flag;
			top--;
			if(sign==1){
				top++;
				stack[top].p=p;
				stack[top].flag=2;
				p=p->rchild;
			}
			else{
				visit(p->data);
				p=NULL;
			}
		}
	}	
}

 char nextToken(char infix[])  {  //���š����������������� ��Ϊһ���ַ� 
     static int pos=0;
     while(infix[pos]!='\0' && infix[pos]==' '){pos++;}//�����ո� 
     return infix[pos++];
 }

int isOpNum(char ch) {  //�Ƿ��ǲ����� 
    if(ch=='#' || ch=='(' || ch==')' || ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch==' ' || ch=='|' ){
        return 0;
    }
    return 1;
}

void createPrefix_recursive(char prefix[],BiTree T){//�ݹ鷽ʽ_��ǰ׺���ʽ�������ʽ�� 
    char x=nextToken(prefix);
    T=(BiTree)malloc(sizeof(BiTNode));
    T->data=x;
    T->lchild=NULL;
    T->rchild=NULL;
    if(!isOpNum(x))//�ǲ��� ����ǰ׺���ʽ�����һ���ַ�һ���ǲ��������� ������ĵݹ��ֹͣ�� 
    { 
        createPrefix_recursive(prefix,T->lchild);
        createPrefix_recursive(prefix,T->rchild);
    }
}

void searchPrefix(BiTree T){
    if(T!=NULL){        
	if(T->lchild!=NULL && T->rchild!=NULL){  //������ҽ�㲻Ϊ�� 
		printf("(");   
	}
        printf("%c",T->data);  //��� 
        searchPrefix(T->lchild);  //�ݹ����� 
        searchPrefix(T->rchild);  //�ݹ��ҽ�� 
        if(T->lchild!=NULL && T->rchild!=NULL){  //�ҽ�㲻Ϊ�� 
		printf(")");}  
	}	
}

