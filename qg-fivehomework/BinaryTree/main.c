#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"../head/BinaryTree.h"
int main(){

	BiTree BT;         //������ 
	BT = (BiTree)malloc(sizeof(BiTNode)); //���ٿռ� 
//	TElemType x;  
//	BiTNode *p;
	InitBiTree(&BT);
	int flag=0;
	do{
		printf("............................\n");
		printf(".  1.����������            .\n");
		printf(".  2.�ݻٶ�����            .\n");
		printf(".  3.�������������        .\n");
		printf(".  4.�������������        .\n");
		printf(".  5.�������������        .\n"); 
		printf(".  6.��α���������        .\n");
		printf(".  7.�ǵݹ��������������  .\n");
		printf(".  8.�ǵݹ��������������  .\n");
		printf(".  9.�ǵݹ��������������  .\n");
		printf(".  a.����ǰ׺���ʽ��      .\n"); 
		printf("............................\n");
		printf("�����루1-8����");
		int choice;
		choice = getche();
		printf("\n");
		while(choice!='1'&& choice!='2' && choice!='3' && choice!='4' && choice!='5' && choice!='6' && choice!='7' && choice!='8' && choice!='9' && choice!='a'){
		printf("\n������������ȷ�����֣�");   //�û���������� 
		choice = getche();	
			}
		switch(choice){
			case '1': {
				printf("\n�밴�����������\n");
				printf("���������㣺"); 
				CreateBiTree(&BT);  //������ 
				break;
			}
			case '2': {
				DestroyBiTree(&BT);  //�ݻ��� 
				flag == 1;
				break;
			}
			case '3': {
				printf("���ĵݹ�����������Ϊ��");
				PreOrderTraverse(BT, visit);  //�ݹ����� 
				break;
			}
			case '4': {
				printf("���ĵݹ�����������Ϊ��");
				InOrderTraverse(BT, visit);  //�ݹ����� 
				break;
			}
			case '5': {
				printf("���ĵݹ�����������Ϊ��");
				PostOrderTraverse(BT,visit);  //�ݹ���� 
				break;
			}
			case '6': {
				printf("���ĵݹ��α������Ϊ��");
				LevelOrderTraverse(BT, visit);  //��� 
				break;
			}
			case '7': {
				printf("���ķǵݹ�����������Ϊ��");
				NRPreOrder_Traverse(BT, visit);  // �ǵݹ����� 
				break;
			} 
			case '8':{
				printf("���ķǵݹ�����������Ϊ��");
				NRInOrder_Traverse(BT, visit); //�ǵݹ����� 
				break;
			}
			case '9':{
				printf("���ķǵݹ����������Ϊ��");
				NRPostOrder_Traverse(BT, visit);  //�ǵݹ���� 
				break;
			}
			case 'a':{
				char str[]="*+A/-BCDE";
				BiTree T;     //����ǰ׺���ʽ�� 
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
