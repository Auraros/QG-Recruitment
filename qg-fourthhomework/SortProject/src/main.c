#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "../inc/qgsort.h"

void Printsort(int*a, int size){  //输出排序后的结果 
	int i;
	printf("\n排序后的顺序为：");
	for(i=0;i<size;i++){
		printf(" %d ",a[i]);
	}
}

int findMax(int *a, int size){  //找到最大的值 
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
	printf("\t|*             排序ADT                        *|\n");
	printf("\t|*        1.插入排序                          *|\n"); 
	printf("\t|*        2.归并排序                          *|\n");
	printf("\t|*        3.快速排序（递归版）                *|\n");
	printf("\t|*        4.快速排序（非递归版）              *|\n");
	printf("\t|*        5.计数排序                          *|\n");
	printf("\t|*        6.基数计数排序                      *|\n");
    printf("\t|*        7.颜色排序                          *|\n");
	printf("\t|*        8.在一个无序序列中找到第K大/小的数  *|\n");
	printf("\t|*        #.退出程序                          *|\n");
	printf("\t|**********************************************|\n");
	printf("请输入所选的序号(1-8)或者输入‘#’结束:\n");
}

int main(){
	int num;
	FILE *fpRead=fopen("data.txt","r");  //打开文件 
	if(fpRead == NULL){  
		return 0;
	}
	fscanf(fpRead,"%d",&num);  //读取第一个数组，定义为数组的长度 
	int i;
	int a[num];
	int choice;
	draw();
	choice = getche();
	while(choice!='1' && choice!='2' && choice!='3' && choice!='4' && choice!='5' && choice!='6' && choice!='7' && choice!='8' && choice!='9' && choice!='#'){
		printf("\n请输入正确的数字:");
		choice = getche();
	} 
	printf("你提取数字为：");
	for( i=0;i<num;i++)
	{
		fscanf(fpRead,"%d",&a[i]);
		printf(" %d ",a[i]);
	}
	switch(choice){
		case '1': {
			insertSort(a,num);  //插入排序 
			Printsort(a,num);
			break;}
		case '2': {
			int len = sizeof(a)/sizeof(a[0]);    //归并排序 
			int *temp=(int*)malloc(sizeof(int)*len);
			MergeSort(a , 0, len-1, temp);
			free(temp);
			Printsort(a,num);
			break;
		} 
		case '3':{
			QuickSort_Recursion(a, 0, num-1);  //快排 
			Printsort(a,num);
			break;
			}
		case '4':{
			QuickSort(a,num);   //非递归快排 
			Printsort(a,num);
			break;
		} 
		case '5':{
			int max ;
			max = findMax(a, num);  //计数排序 
			CountSort(a, num , max);
			Printsort(a,num);
			break;
		}
		case '6':{
			RadixCountSort(a,num);  //基数计数排序 
			Printsort(a,num);
			break;
		}
		case '7':{
			ColorSort(a,num);  //颜色排序 
			Printsort(a,num);
			break;
		}
		case '8':{
			int number,indexNum;   //找到第k个大的数字 
			printf("\n请输入你想要知道的第几个大的数字（不大于%d）：",num);
			while(scanf("%d",&number)==0){
				printf("请输入正确的数字：");
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

