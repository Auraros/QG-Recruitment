#include <stdlib.h>
#include<time.h>
#include<stdio.h>
#include<string.h>

#define numa 10000   //10000个字数据 
#define numb 50000   //50000个数据 
#define numc 200000  //200000个数据 


int copy2[200000];  //不知道为啥，在main函数不可以定义，只能放到全局变量 
int num2[200000]; 

void Printsort(int*a, int size){   //输出排序，数据太大，不建议使用 
	int i;
	printf("\n排序后的顺序为：");
	for(i=0;i<size;i++){
		printf(" %d ",a[i]);
	}
}

int findMax(int *a, int size){  //找到数组中的最大值提供给计数排序 
	int max=a[0];
	int i=0;
	for(i=0;i<size;i++){
		if(max<a[i])
			max=a[i];
	}
	return max;
}

int main() {
	clock_t start,finish;   //定义时间变量 
	double Total_time;    //总时间 
	int i,j,number,num[10000];
	//一万个数字的时候 
	srand((unsigned) time(NULL)); //用时间做种，每次产生随机数不一样
	for (i=0; i<10000; i++){   //随机创建10000个数字 
  		number = rand() ;
  		num[i]=number;
	}
	printf("运行10000个数字每个排序所需要的时间：\n");
	int copy[10000];
	//插入排序 
	for (i=0;i<numa;i++)   //为了数组可以循环，并且不因为数据大小影响时间，使用拷贝数组的方法 
		copy[i] = num[i];
	start = clock();    //开始计时 
	insertSort(copy,10000);  //进行排序 
	finish = clock();   //停止计时 
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("插入排序需要的时间为：%f\n",Total_time);
	//归并排序 
	for (i=0;i<numa;i++)    //同理 
		copy[i] = num[i];                    
	int len = sizeof(copy)/sizeof(copy[0]);   //得到长度 
	int *temp=(int*)malloc(sizeof(int)*len);   //建立temp指针 
	start = clock();
	MergeSort(copy , 0, len-1, temp);
	free(temp);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("归并排序需要的时间为：%f\n",Total_time);
	//快速排序（递归版） 
	for (i=0;i<numa;i++)
		copy[i] = num[i];
	start = clock();	
	QuickSort_Recursion(copy, 0, 9999);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("快速排序（递归版）需要的时间为：%f\n",Total_time);
	//快速排序（非递归版）
	for (i=0;i<numa;i++)
		copy[i] = num[i];
	start = clock();
	QuickSort(copy,10000); 
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("快速排序（非递归版）需要的时间为：%f\n",Total_time);
	//计数排序
	for (i=0;i<numa;i++)
		copy[i] = num[i];
	int max;
	max = findMax(copy, 10000);
	start = clock();
	CountSort(copy, 10000 , max);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("计数排序需要的时间为：%f\n",Total_time);
	//基数计数排序
	for (i=0;i<numa;i++)
		copy[i] = num[i];
	start = clock();
	RadixCountSort(copy,10000); 
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("基数计数排序需要的时间为：%f\n",Total_time);
	
	//5000个数据测试 
	int num1[50000];      //定义一个5000个的数据，做法和上面一样 
	for (i=0; i<50000; i++){
  		number = rand() ;
  		num1[i]=number;
	}
	printf("\n运行50000个数字每个排序所需要的时间：\n");
	int copy1[50000];
	//插入排序 
	for (i=0;i<numb;i++)
		copy1[i] = num1[i];
	start = clock();
	insertSort(copy1,50000);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("插入排序需要的时间为：%f\n",Total_time);
	//归并排序 
	for (i=0;i<numb;i++)
		copy1[i] = num1[i];
	int len1 = sizeof(copy1)/sizeof(copy1[0]);
	int *temp1=(int*)malloc(sizeof(int)*len1);
	start = clock();
	MergeSort(copy1 , 0, len1-1, temp1);
	free(temp1);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("归并排序需要的时间为：%f\n",Total_time);
	//快速排序（递归版） 
	for (i=0;i<numb;i++)
		copy1[i] = num1[i];
	start = clock();	
	QuickSort_Recursion(copy1, 0, 49999);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("快速排序（递归版）需要的时间为：%f\n",Total_time);
	//快速排序（非递归版）
	for (i=0;i<numb;i++)
		copy1[i] = num1[i];
	start = clock();
	QuickSort(copy1,50000); 
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("快速排序（非递归版）需要的时间为：%f\n",Total_time);
	//计数排序
	for (i=0;i<numb;i++)
		copy1[i] = num1[i];
	max = findMax(copy1, 50000);
	start = clock();
	CountSort(copy1, 50000 , max);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("计数排序需要的时间为：%f\n",Total_time);
	//基数计数排序
	for (i=0;i<numb;i++)
		copy1[i] = num1[i];
	start = clock();
	RadixCountSort(copy1,50000); 
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("基数计数排序需要的时间为：%f\n",Total_time);
	
	
	//200000个数据测试 
	for (i=0; i<200000; i++){   //做法和上面大同小异 
  		number = rand()%1000 ;
  		num2[i]=number;
	}
	printf("\n运行200000个数字每个排序所需要的时间(时间很长，请耐心等待)：\n");
//	//插入排序 
	for (i=0;i<numc;i++)
		copy2[i] = num2[i];
	start = clock();
	insertSort(copy2,200000);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("插入排序需要的时间为：%f\n",Total_time);
//////	//归并排序 
	for (i=0;i<numc;i++)
		copy2[i] = num2[i];
	int len3 = sizeof(copy2)/sizeof(copy2[0]);
	int *temp3=(int*)malloc(sizeof(int)*len3);
	start = clock();
	MergeSort(copy2 , 0, len3-1, temp3);
	free(temp3);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("归并排序需要的时间为：%f\n",Total_time);
//	//快速排序（递归版） 
	for (i=0;i<numc;i++)
		copy2[i] = num2[i];
	start = clock();	
	QuickSort_Recursion(copy2, 0, 199999);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("快速排序（递归版）需要的时间为：%f\n",Total_time);
//	//快速排序（非递归版）         //非递归的时候，由于栈的影响，程序总是会出错。找不到原因 
//	for (i=0;i<numc;i++)   
//		copy2[i] = num2[i];
//	start = clock();
//	QuickSort(copy2,200000); 
//	finish = clock();
//	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
//	printf("快速排序（非递归版）需要的时间为：%f\n",Total_time);
//	//计数排序
	for (i=0;i<numc;i++)
		copy2[i] = num2[i];
	int max2 = findMax(copy2, 200000);
	start = clock();
	CountSort(copy2, 200000 , max2);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("计数排序需要的时间为：%f\n",Total_time);
//	//基数计数排序
	for (i=0;i<numc;i++)
		copy2[i] = num2[i];
	start = clock();
	RadixCountSort(copy2,200000); 
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("基数计数排序需要的时间为：%f\n",Total_time);

//100数据*100k的排序时间 
	int num3[100]; 
	for (i=0; i<100; i++){  //随机生成100个数据 
  		number = rand() ;
  		num3[i]=number;
	}
	printf("\n运行100数据*100k次的排序时间：\n");
	int copy3[100],m;
	//插入排序 
	start = clock();
	for(i=0;i<100000;i++){   //利用循环，让插入排序做100000次 
		for (m=0;m<100;m++)   //在这里，拷贝数组可能会有影响，但每个函数都是这样，还是可以比较的 
			copy3[m] = num3[m];
		insertSort(copy3,100);
	}
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("插入排序需要的时间为：%f\n",Total_time);
	
	//归并排序
	start = clock();
	for(i=0;i<100000;i++){    //下面的做法跟上面大多相同 
		for (m=0;m<100;m++)
			copy3[m] = num3[m];
		int len2 = sizeof(copy3)/sizeof(copy3[0]);
		int *temp2=(int*)malloc(sizeof(int)*len2);
		MergeSort(copy3 , 0, len2-1, temp2);
		free(temp2);
	}
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("归并排序需要的时间为：%f\n",Total_time); 
	
	// 快速排序（递归版） 
	start = clock();
	for(i=0;i<100000;i++){
		for (m=0;m<100;m++)
			copy3[m] = num3[m];
		QuickSort_Recursion(copy3, 0, 99); 
	}
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("快速排序（递归）需要的时间为：%f\n",Total_time); 
	
	// 快速排序（非递归版）
//	start = clock();
//	for(i=0;i<100000;i++){
//		for (m=0;m<100;m++)
//			copy3[m] = num3[m];
//		QuickSort(copy3,100);
//	}
//	finish = clock();
//	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
//	printf("快速排序（非递归）需要的时间为：%f\n",Total_time); 

	//计数排序
	start = clock();
	for(i=0;i<100000;i++){
		for (m=0;m<100;m++)
			copy3[m] = num3[m];
		int max1 ;
		max1 = findMax(copy3, 100);
		CountSort(copy3, 100 , max);
		}
		finish = clock();
		Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
		printf("计数排序需要的时间为：%f\n",Total_time); 
	 
	//基数计数排序
	start = clock();
	for(i=0;i<100000;i++){
		for (m=0;m<100;m++)
			copy3[m] = num3[m];
		RadixCountSort(copy3,100);
		} 
	 	finish = clock();
		Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
		printf("基数计数排序需要的时间为：%f\n",Total_time); 
		
	system("pause");
	system("cls");
}
