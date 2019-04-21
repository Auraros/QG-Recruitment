#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include "../head/BinaryTree.h"


Status InitBiTree(BiTree *T){
	assert(T);
	if(*T == NULL)     //判断初始化是否成功 
		return ERROR;
	*T = NULL;   //初始化 
	return SUCCESS;
} 

Status DestroyBiTree(BiTree *T){
	assert(T);
	if(*T == NULL)
		return ERROR;
	DestroyBiTree(&((*T)->lchild));   //摧毁左节点 
	DestroyBiTree(&((*T)->rchild));   //摧毁右结点 
	free(T);    //释放T 
	*T = NULL;  //树结点设为空 
}

Status CreateBiTree(BiTree *T){
	char ch;
    scanf("%c", &ch);     //用户输入字符 
	getchar();
    if(ch == '#')   //如果是#则设为空 
        *T = NULL; 
    else{
        *T = (BiTree)malloc(sizeof(BiTNode));  //给结点开辟空间 
        (*T) -> data = ch;  //赋值 
        printf("请输入%c的左子树:", ch);  //方便建树 
        CreateBiTree(&((*T) -> lchild));  //递归输入 
        printf("请输入%c的右子树:", ch);   
        CreateBiTree(&((*T) -> rchild));
    }
}

	
Status visit(TElemType e){
	printf("%c",e);  //输出 
}

Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType e)){  //先序遍历 
	if(T!=NULL){
		visit(T->data);   //输出 
		PreOrderTraverse(T->lchild, visit);  //遍历左结点 
		PreOrderTraverse(T->rchild, visit);  //遍历右结点 
	}
}

Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e)){  //中序遍历 
	if(T!=NULL){
		InOrderTraverse(T->lchild, visit); //遍历左节点 
		visit(T->data);    //输出 
		InOrderTraverse(T->rchild, visit); //遍历右结点 
	}
}

Status PostOrderTraverse(BiTree T, Status (*visit)(TElemType e)){ //后续遍历 
	if(T!=NULL){ 
		PostOrderTraverse(T->lchild, visit); //遍历做节点 
		PostOrderTraverse(T->rchild, visit);  //遍历右结点 
		visit(T->data);  //输出 
	}
}

Status LevelOrderTraverse(BiTree T, Status (*visit)(TElemType e)){  //层次遍历 
	BiTNode *p;  //建立树结点 
	SeqQueue Q;   //建立一个循环队列 
	Q.front = Q.rear = -1;  //初始化队列 
	Q.rear++;   //入队 
	Q.qu[Q.rear]=T;  //根结点入队 
	while(Q.front!=Q.rear){  //不是空队列 
		Q.front = (Q.front+1)%MAXSIZE;  
		p = Q.qu[Q.front];   //队头出列 
		visit(p->data);
		if(p->lchild!=NULL){  //左孩子地址入队 
			Q.rear = (Q.rear+1)%MAXSIZE;
			Q.qu[Q.rear] = p->lchild;
		}
		if(p->rchild != NULL){ //右孩子地址入队 
			Q.rear = (Q.rear+1)%MAXSIZE;
			Q.qu[Q.rear] = p->rchild;
		}
	}
}

void NRPreOrder_Traverse(BiTree T, Status (*visit)(TElemType e)){  //非递归先序遍历二叉树
	BiTNode *stack[MAXSIZE], *p;  //定义栈 
	int top;
	if(T == NULL)  //树为空 
		return;
	top = 0;
	p=T;
	while(p!=NULL || top!=0){
		while(p!=NULL){
			visit(p->data);  //输出结点元素 
			if(top<MAXSIZE -1){  //当前指针p入栈 
			stack[top]=p;
			top++; 
		}
		else{
			printf("\n栈溢出。\n");
			return;
		}
		p = p->lchild;  //指针指向左孩子 
	} 
	if(top<0)  //栈为空的时候返回 
		return;
	else{
		top--;  //栈顶元素出栈 
		p=stack[top];
		p=p->rchild;  //指针指向p的右孩子结点 
		}
	}
}
 
void NRInOrder_Traverse(BiTree T, Status (*visit)(TElemType e)){
	BiTNode *stack[MAXSIZE], *p;  //定义栈 
	int top;
	if(T == NULL)  //树为空 
		return;
	top = 0;
	p=T;
	while(p!=NULL || top!=0){
		while(p!=NULL){
			if(top<MAXSIZE -1){  //当前指针p入栈 
			stack[top]=p;
			top++; 
		}
		else{
			printf("\n栈溢出。\n");
			return;
		}
		p = p->lchild;  //指针指向左孩子 
	} 
	if(top<0)  //栈为空的时候返回 
		return;
	else{
		top--;
		p=stack[top];
		visit(p->data);   //输出元素 
		p=p->rchild;  //指针指向p的右孩子结点 
		}
	}
}

void NRPostOrder_Traverse(BiTree T, Status (*visit)(TElemType e)) {
	StackType  stack[MAXSIZE];  //定义栈 
	BiTree p;
	int top,sign;
	if(T == NULL)  //树为空 
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

 char nextToken(char infix[])  {  //括号、操作数、操作符等 都为一个字符 
     static int pos=0;
     while(infix[pos]!='\0' && infix[pos]==' '){pos++;}//跳过空格 
     return infix[pos++];
 }

int isOpNum(char ch) {  //是否是操作数 
    if(ch=='#' || ch=='(' || ch==')' || ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch==' ' || ch=='|' ){
        return 0;
    }
    return 1;
}

void createPrefix_recursive(char prefix[],BiTree T){//递归方式_由前缀表达式构建表达式树 
    char x=nextToken(prefix);
    T=(BiTree)malloc(sizeof(BiTNode));
    T->data=x;
    T->lchild=NULL;
    T->rchild=NULL;
    if(!isOpNum(x))//是操作 符。前缀表达式的最后一个字符一定是操作数，所 以下面的递归会停止。 
    { 
        createPrefix_recursive(prefix,T->lchild);
        createPrefix_recursive(prefix,T->rchild);
    }
}

void searchPrefix(BiTree T){
    if(T!=NULL){        
	if(T->lchild!=NULL && T->rchild!=NULL){  //如果左右结点不为空 
		printf("(");   
	}
        printf("%c",T->data);  //输出 
        searchPrefix(T->lchild);  //递归左结点 
        searchPrefix(T->rchild);  //递归右结点 
        if(T->lchild!=NULL && T->rchild!=NULL){  //右结点不为空 
		printf(")");}  
	}	
}

