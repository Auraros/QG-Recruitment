#include <stdlib.h>
#include<time.h>
#include<stdio.h>
#include<string.h>

#define numa 10000   //10000�������� 
#define numb 50000   //50000������ 
#define numc 200000  //200000������ 


int copy2[200000];  //��֪��Ϊɶ����main���������Զ��壬ֻ�ܷŵ�ȫ�ֱ��� 
int num2[200000]; 

void Printsort(int*a, int size){   //�����������̫�󣬲�����ʹ�� 
	int i;
	printf("\n������˳��Ϊ��");
	for(i=0;i<size;i++){
		printf(" %d ",a[i]);
	}
}

int findMax(int *a, int size){  //�ҵ������е����ֵ�ṩ���������� 
	int max=a[0];
	int i=0;
	for(i=0;i<size;i++){
		if(max<a[i])
			max=a[i];
	}
	return max;
}

int main() {
	clock_t start,finish;   //����ʱ����� 
	double Total_time;    //��ʱ�� 
	int i,j,number,num[10000];
	//һ������ֵ�ʱ�� 
	srand((unsigned) time(NULL)); //��ʱ�����֣�ÿ�β����������һ��
	for (i=0; i<10000; i++){   //�������10000������ 
  		number = rand() ;
  		num[i]=number;
	}
	printf("����10000������ÿ����������Ҫ��ʱ�䣺\n");
	int copy[10000];
	//�������� 
	for (i=0;i<numa;i++)   //Ϊ���������ѭ�������Ҳ���Ϊ���ݴ�СӰ��ʱ�䣬ʹ�ÿ�������ķ��� 
		copy[i] = num[i];
	start = clock();    //��ʼ��ʱ 
	insertSort(copy,10000);  //�������� 
	finish = clock();   //ֹͣ��ʱ 
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("����������Ҫ��ʱ��Ϊ��%f\n",Total_time);
	//�鲢���� 
	for (i=0;i<numa;i++)    //ͬ�� 
		copy[i] = num[i];                    
	int len = sizeof(copy)/sizeof(copy[0]);   //�õ����� 
	int *temp=(int*)malloc(sizeof(int)*len);   //����tempָ�� 
	start = clock();
	MergeSort(copy , 0, len-1, temp);
	free(temp);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("�鲢������Ҫ��ʱ��Ϊ��%f\n",Total_time);
	//�������򣨵ݹ�棩 
	for (i=0;i<numa;i++)
		copy[i] = num[i];
	start = clock();	
	QuickSort_Recursion(copy, 0, 9999);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("�������򣨵ݹ�棩��Ҫ��ʱ��Ϊ��%f\n",Total_time);
	//�������򣨷ǵݹ�棩
	for (i=0;i<numa;i++)
		copy[i] = num[i];
	start = clock();
	QuickSort(copy,10000); 
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("�������򣨷ǵݹ�棩��Ҫ��ʱ��Ϊ��%f\n",Total_time);
	//��������
	for (i=0;i<numa;i++)
		copy[i] = num[i];
	int max;
	max = findMax(copy, 10000);
	start = clock();
	CountSort(copy, 10000 , max);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("����������Ҫ��ʱ��Ϊ��%f\n",Total_time);
	//������������
	for (i=0;i<numa;i++)
		copy[i] = num[i];
	start = clock();
	RadixCountSort(copy,10000); 
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("��������������Ҫ��ʱ��Ϊ��%f\n",Total_time);
	
	//5000�����ݲ��� 
	int num1[50000];      //����һ��5000�������ݣ�����������һ�� 
	for (i=0; i<50000; i++){
  		number = rand() ;
  		num1[i]=number;
	}
	printf("\n����50000������ÿ����������Ҫ��ʱ�䣺\n");
	int copy1[50000];
	//�������� 
	for (i=0;i<numb;i++)
		copy1[i] = num1[i];
	start = clock();
	insertSort(copy1,50000);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("����������Ҫ��ʱ��Ϊ��%f\n",Total_time);
	//�鲢���� 
	for (i=0;i<numb;i++)
		copy1[i] = num1[i];
	int len1 = sizeof(copy1)/sizeof(copy1[0]);
	int *temp1=(int*)malloc(sizeof(int)*len1);
	start = clock();
	MergeSort(copy1 , 0, len1-1, temp1);
	free(temp1);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("�鲢������Ҫ��ʱ��Ϊ��%f\n",Total_time);
	//�������򣨵ݹ�棩 
	for (i=0;i<numb;i++)
		copy1[i] = num1[i];
	start = clock();	
	QuickSort_Recursion(copy1, 0, 49999);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("�������򣨵ݹ�棩��Ҫ��ʱ��Ϊ��%f\n",Total_time);
	//�������򣨷ǵݹ�棩
	for (i=0;i<numb;i++)
		copy1[i] = num1[i];
	start = clock();
	QuickSort(copy1,50000); 
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("�������򣨷ǵݹ�棩��Ҫ��ʱ��Ϊ��%f\n",Total_time);
	//��������
	for (i=0;i<numb;i++)
		copy1[i] = num1[i];
	max = findMax(copy1, 50000);
	start = clock();
	CountSort(copy1, 50000 , max);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("����������Ҫ��ʱ��Ϊ��%f\n",Total_time);
	//������������
	for (i=0;i<numb;i++)
		copy1[i] = num1[i];
	start = clock();
	RadixCountSort(copy1,50000); 
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("��������������Ҫ��ʱ��Ϊ��%f\n",Total_time);
	
	
	//200000�����ݲ��� 
	for (i=0; i<200000; i++){   //�����������ͬС�� 
  		number = rand()%1000 ;
  		num2[i]=number;
	}
	printf("\n����200000������ÿ����������Ҫ��ʱ��(ʱ��ܳ��������ĵȴ�)��\n");
//	//�������� 
	for (i=0;i<numc;i++)
		copy2[i] = num2[i];
	start = clock();
	insertSort(copy2,200000);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("����������Ҫ��ʱ��Ϊ��%f\n",Total_time);
//////	//�鲢���� 
	for (i=0;i<numc;i++)
		copy2[i] = num2[i];
	int len3 = sizeof(copy2)/sizeof(copy2[0]);
	int *temp3=(int*)malloc(sizeof(int)*len3);
	start = clock();
	MergeSort(copy2 , 0, len3-1, temp3);
	free(temp3);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("�鲢������Ҫ��ʱ��Ϊ��%f\n",Total_time);
//	//�������򣨵ݹ�棩 
	for (i=0;i<numc;i++)
		copy2[i] = num2[i];
	start = clock();	
	QuickSort_Recursion(copy2, 0, 199999);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("�������򣨵ݹ�棩��Ҫ��ʱ��Ϊ��%f\n",Total_time);
//	//�������򣨷ǵݹ�棩         //�ǵݹ��ʱ������ջ��Ӱ�죬�������ǻ�����Ҳ���ԭ�� 
//	for (i=0;i<numc;i++)   
//		copy2[i] = num2[i];
//	start = clock();
//	QuickSort(copy2,200000); 
//	finish = clock();
//	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
//	printf("�������򣨷ǵݹ�棩��Ҫ��ʱ��Ϊ��%f\n",Total_time);
//	//��������
	for (i=0;i<numc;i++)
		copy2[i] = num2[i];
	int max2 = findMax(copy2, 200000);
	start = clock();
	CountSort(copy2, 200000 , max2);
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("����������Ҫ��ʱ��Ϊ��%f\n",Total_time);
//	//������������
	for (i=0;i<numc;i++)
		copy2[i] = num2[i];
	start = clock();
	RadixCountSort(copy2,200000); 
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("��������������Ҫ��ʱ��Ϊ��%f\n",Total_time);

//100����*100k������ʱ�� 
	int num3[100]; 
	for (i=0; i<100; i++){  //�������100������ 
  		number = rand() ;
  		num3[i]=number;
	}
	printf("\n����100����*100k�ε�����ʱ�䣺\n");
	int copy3[100],m;
	//�������� 
	start = clock();
	for(i=0;i<100000;i++){   //����ѭ�����ò���������100000�� 
		for (m=0;m<100;m++)   //���������������ܻ���Ӱ�죬��ÿ�������������������ǿ��ԱȽϵ� 
			copy3[m] = num3[m];
		insertSort(copy3,100);
	}
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("����������Ҫ��ʱ��Ϊ��%f\n",Total_time);
	
	//�鲢����
	start = clock();
	for(i=0;i<100000;i++){    //�������������������ͬ 
		for (m=0;m<100;m++)
			copy3[m] = num3[m];
		int len2 = sizeof(copy3)/sizeof(copy3[0]);
		int *temp2=(int*)malloc(sizeof(int)*len2);
		MergeSort(copy3 , 0, len2-1, temp2);
		free(temp2);
	}
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("�鲢������Ҫ��ʱ��Ϊ��%f\n",Total_time); 
	
	// �������򣨵ݹ�棩 
	start = clock();
	for(i=0;i<100000;i++){
		for (m=0;m<100;m++)
			copy3[m] = num3[m];
		QuickSort_Recursion(copy3, 0, 99); 
	}
	finish = clock();
	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("�������򣨵ݹ飩��Ҫ��ʱ��Ϊ��%f\n",Total_time); 
	
	// �������򣨷ǵݹ�棩
//	start = clock();
//	for(i=0;i<100000;i++){
//		for (m=0;m<100;m++)
//			copy3[m] = num3[m];
//		QuickSort(copy3,100);
//	}
//	finish = clock();
//	Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
//	printf("�������򣨷ǵݹ飩��Ҫ��ʱ��Ϊ��%f\n",Total_time); 

	//��������
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
		printf("����������Ҫ��ʱ��Ϊ��%f\n",Total_time); 
	 
	//������������
	start = clock();
	for(i=0;i<100000;i++){
		for (m=0;m<100;m++)
			copy3[m] = num3[m];
		RadixCountSort(copy3,100);
		} 
	 	finish = clock();
		Total_time = (double)(finish-start)/CLOCKS_PER_SEC;
		printf("��������������Ҫ��ʱ��Ϊ��%f\n",Total_time); 
		
	system("pause");
	system("cls");
}
