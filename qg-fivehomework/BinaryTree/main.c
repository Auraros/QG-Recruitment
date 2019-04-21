#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"../head/BinaryTree.h"
int main(){

	BiTree BT;         //声明树 
	BT = (BiTree)malloc(sizeof(BiTNode)); //开辟空间 
//	TElemType x;  
//	BiTNode *p;
	InitBiTree(&BT);
	int flag=0;
	do{
		printf("............................\n");
		printf(".  1.创建二叉树            .\n");
		printf(".  2.摧毁二叉树            .\n");
		printf(".  3.先序遍历二叉树        .\n");
		printf(".  4.中序遍历二叉树        .\n");
		printf(".  5.后序遍历二叉树        .\n"); 
		printf(".  6.层次遍历二叉树        .\n");
		printf(".  7.非递归先序遍历二叉树  .\n");
		printf(".  8.非递归中序遍历二叉树  .\n");
		printf(".  9.非递归后续遍历二叉树  .\n");
		printf(".  a.生成前缀表达式树      .\n"); 
		printf("............................\n");
		printf("请输入（1-8）：");
		int choice;
		choice = getche();
		printf("\n");
		while(choice!='1'&& choice!='2' && choice!='3' && choice!='4' && choice!='5' && choice!='6' && choice!='7' && choice!='8' && choice!='9' && choice!='a'){
		printf("\n请重新输入正确的数字：");   //用户输入错误处理 
		choice = getche();	
			}
		switch(choice){
			case '1': {
				printf("\n请按先序次序输入\n");
				printf("请输入根结点："); 
				CreateBiTree(&BT);  //创建树 
				break;
			}
			case '2': {
				DestroyBiTree(&BT);  //摧毁树 
				flag == 1;
				break;
			}
			case '3': {
				printf("树的递归先序遍历结果为：");
				PreOrderTraverse(BT, visit);  //递归先序 
				break;
			}
			case '4': {
				printf("树的递归中序遍历结果为：");
				InOrderTraverse(BT, visit);  //递归中序 
				break;
			}
			case '5': {
				printf("树的递归后续遍历结果为：");
				PostOrderTraverse(BT,visit);  //递归后序 
				break;
			}
			case '6': {
				printf("树的递归层次遍历结果为：");
				LevelOrderTraverse(BT, visit);  //层次 
				break;
			}
			case '7': {
				printf("树的非递归先序遍历结果为：");
				NRPreOrder_Traverse(BT, visit);  // 非递归先序 
				break;
			} 
			case '8':{
				printf("树的非递归中序遍历结果为：");
				NRInOrder_Traverse(BT, visit); //非递归中序 
				break;
			}
			case '9':{
				printf("树的非递归后序遍历结果为：");
				NRPostOrder_Traverse(BT, visit);  //非递归后续 
				break;
			}
			case 'a':{
				char str[]="*+A/-BCDE";
				BiTree T;     //生成前缀表达式树 
				createPrefix_recursive(str,T);
				searchPrefix(T);   
				printf("\n");
				break;
			}
		}
		system("pause");
		system("cls");
	}while(flag==0);
	return 0;
}
