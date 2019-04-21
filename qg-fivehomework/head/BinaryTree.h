#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED


typedef char TElemType;     // 假设二叉树结点的元素类型为字符
typedef struct BiTNode {
    TElemType      data;     // 数据域
    struct BiTNode  *lchild,*rchild;  // 左、右孩子指针
} BiTNode, *BiTree;   // 二叉链表

typedef enum Status{
	ERROR,
	SUCCESS
}Status;

//二叉树节点栈     
struct biTreeStack{
    struct biTreeNode *base;
    struct biTreeNode *top;
    int stackSize;
};

//操作数栈
struct numStack{
    struct nodeNum *base;
    struct nodeNum *top;
    int stackSize;
};

//操作符栈
struct chaStack{
    struct nodeCha *base;
    struct nodeCha *top;
    int stackSize;
};

#define MAXSIZE 100
typedef struct{
	BiTNode *qu[MAXSIZE];
	int front,rear;   //循环顺序链表，存放二叉树结点地址 
}SeqQueue;


typedef struct{
	BiTNode *p;
	int flag;
}StackType;




/**
 *  @name        : Status InitBiTree(BiTree T);
 *  @description : 构造空二叉树T
 *  @param       : 二叉树根结点T
 */
Status InitBiTree(BiTree *T);
Status CreateBiTree(BiTree *T);

/**
 *  @name        : Status DestroyBiTree(BiTree T);
 *  @description : 摧毁二叉树T
 *  @param       : 二叉树根结点T
 */
Status DestroyBiTree(BiTree *T);


/**
 *  @name        : Status CreateBiTree(BiTree T, char* definition);
 *  @description : 构造二叉树T
 *  @param       : 二叉树根结点T, 二叉树先序 遍历字 符串definition
 */
Status CreateBiTree1(BiTree *T);


/**
 *  @name        : Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType e));
 *  @description : 先序遍历二叉树T
 *  @param       : 二叉树根结点T, 对结点的操作函数visit
 */
Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType e));


/**
 *  @name        : Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e));	
 *  @description : 中序遍历二叉树T
 *  @param       : 二叉树根结点T, 对结点的操作函数visit
 */
Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e));	


/**
 *  @name        : Status PostOrderTraverse(BiTree T, Status (*visit)(TElemType e)));
 *  @description : 后序遍历二叉树T
 *  @param       : 二叉树根结点T, 对结点的操作函数visit
 */

Status PostOrderTraverse(BiTree T, Status (*visit)(TElemType e));

/**
 *  @name        : Status LevelOrderTraverse(BiTree T, Status (*visit)(TElemType e));
 *  @description : 层序遍历二叉树T
 *  @param       : 二叉树根结点T, 对结点的操作函数visit
 */
Status LevelOrderTraverse(BiTree T, Status (*visit)(TElemType e));
Status visit(TElemType e);

void NRPreOrder_Traverse(BiTree T, Status (*visit)(TElemType e)); //非递归先序 
void NRInOrder_Traverse(BiTree T, Status (*visit)(TElemType e)); //非递归中序 
void NRPostOrder_Traverse(BiTree T, Status (*visit)(TElemType e)) ;  //非递归后序 
char nextToken(char infix[]);//括号、操作数、操作符等 都为一个字符 
int isOpNum(char ch);//是否是操作数 
void createPrefix_recursive(char prefix[],BiTree T);//前缀表达式构建表达式树（递归）
void searchPrefix(BiTree T);  //前缀表达式树 

/**
 *  @name        : int Value(BiTree T);
 *  @description : 对构造出的前缀表达式二叉树求值
 *  @param       : 二叉树根结点T
 *  @note        : 可在结点结构体中设置个Tag值标志数字与操作符来构造二叉树，
 *                 可根据需要自行增加操作.
 */
int Value(BiTree T);
 
#endif // BINARYTREE_H_INCLUDED
