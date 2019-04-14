#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "../inc/qgsort.h"

void Printsort(int*a, int size){  //��������Ľ�� 
	int i;
	printf("\n������˳��Ϊ��");
	for(i=0;i<size;i++){
		printf(" %d ",a[i]);
	}
}

int findMax(int *a, int size){  //�ҵ�����ֵ 
	int max=a[0];
	int i=0;
	for(i=0;i<size;i++){
		if(max<a[i])
			max=a[i];
	}
	return max;
}
void draw()
{
	printf("\t|**********************************************|\n");
	printf("\t|*             ����ADT                        *|\n");
	printf("\t|*        1.��������                          *|\n"); 
	printf("\t|*        2.�鲢����                          *|\n");
	printf("\t|*        3.�������򣨵ݹ�棩                *|\n");
	printf("\t|*        4.�������򣨷ǵݹ�棩              *|\n");
	printf("\t|*        5.��������                          *|\n");
	printf("\t|*        6.������������                      *|\n");
    printf("\t|*        7.��ɫ����                          *|\n");
	printf("\t|*        8.��һ�������������ҵ���K��/С����  *|\n");
	printf("\t|*        #.�˳�����                          *|\n");
	printf("\t|**********************************************|\n");
	printf("��������ѡ�����(1-8)�������롮#������:\n");
}

int main(){
	int num;
	FILE *fpRead=fopen("data.txt","r");  //���ļ� 
	if(fpRead == NULL){  
		return 0;
	}
	fscanf(fpRead,"%d",&num);  //��ȡ��һ�����飬����Ϊ����ĳ��� 
	int i;
	int a[num];
	int choice;
	draw();
	choice = getche();
	while(choice!='1' && choice!='2' && choice!='3' && choice!='4' && choice!='5' && choice!='6' && choice!='7' && choice!='8' && choice!='9' && choice!='#'){
		printf("\n��������ȷ������:");
		choice = getche();
	} 
	printf("����ȡ����Ϊ��");
	for( i=0;i<num;i++)
	{
		fscanf(fpRead,"%d",&a[i]);
		printf(" %d ",a[i]);
	}
	switch(choice){
		case '1': {
			insertSort(a,num);  //�������� 
			Printsort(a,num);
			break;}
		case '2': {
			int len = sizeof(a)/sizeof(a[0]);    //�鲢���� 
			int *temp=(int*)malloc(sizeof(int)*len);
			MergeSort(a , 0, len-1, temp);
			free(temp);
			Printsort(a,num);
			break;
		} 
		case '3':{
			QuickSort_Recursion(a, 0, num-1);  //���� 
			Printsort(a,num);
			break;
			}
		case '4':{
			QuickSort(a,num);   //�ǵݹ���� 
			Printsort(a,num);
			break;
		} 
		case '5':{
			int max ;
			max = findMax(a, num);  //�������� 
			CountSort(a, num , max);
			Printsort(a,num);
			break;
		}
		case '6':{
			RadixCountSort(a,num);  //������������ 
			Printsort(a,num);
			break;
		}
		case '7':{
			ColorSort(a,num);  //��ɫ���� 
			Printsort(a,num);
			break;
		}
		case '8':{
			int number,indexNum;   //�ҵ���k��������� 
			printf("\n����������Ҫ֪���ĵڼ���������֣�������%d����",num);
			while(scanf("%d",&number)==0){
				printf("��������ȷ�����֣�");
				getchar(); 
			}
			indexNum = findNum(a, 0, num-1, number);
			printf("%d",indexNum);
			break;
		}
		case '#':break;
	}
	system("pause");
	system("cls");
}

