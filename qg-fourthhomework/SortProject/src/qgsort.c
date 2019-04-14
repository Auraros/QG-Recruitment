#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <assert.h>
#include "../inc/qgsort.h" 

//������������ 
void Swap(int *p, int *q){
    int buf;
    buf = *p;
    *p = *q;
    *q = buf;
    return;
}

/* ��������
ʱ�临�Ӷȣ� O��n^2��
�ռ临�Ӷȣ� O��1��*/ 
void insertSort(int *a,int n){   //��������
	int i, j, tmp;
	for (i=1; i<n; i++){    //ѭ���������� 
		if(a[i]<a[i-1]){   //�ҵ������С���� 
			tmp=a[i];          
			for (j=i-1;j>=0&&a[j]>tmp;j--){  //���ұ߽����ж� 
				a[j+1] = a[j];  //���� 
			}
			a[j+1] = tmp;
		}
	}  	 
}

/*�鲢����
ʱ�临�Ӷȣ�O��NlogN��
�ռ临�Ӷȣ�O��N��*/ 
void MergeAdd(int *a,int begin,int mid,int end,int *temp){ //�鲢����
	int i = begin;
	int j = mid + 1;
	int k = begin;//��ʱ�±�
	while (i <= mid&&j <= end){  //��i<�м�ֵ��jС�����ʱ 
		if (a[i] < a[j]){    //�жϴ�С 
			temp[k++] = a[i++];   //���� 
		}
		else{
			temp[k++] = a[j++]; //���� 
		}
	}
	while (i <= mid){
		temp[k++] = a[i++];  //��i�Ժ�����ֶ�������temp 
	}
	while (j <= end){
		temp[k++] = a[j++];  //��j�Ժ�����ֶ�������temp 
	}  
	memcpy(a + begin, temp + begin, sizeof(int)*(end - begin+1)); //��temp���ݿ�����a 
}

//�ݹ�ʵ�� �鲢���� 
void MergeSort(int *a ,int begin,int end,int *temp){//ʵ�֡��֡�
	int mid = 0;
	if (begin < end){
		mid = begin + (end - begin) / 2;  //�õ��м�����ֵ 
		MergeSort(a, begin, mid, temp);   //��ǰ��һ���ֽ������� 
		MergeSort(a, mid + 1, end, temp);  //�Ժ���һ���ֽ������� 
		MergeAdd(a, begin, mid, end, temp);  //������ 
	}
}	

/*��������
ʱ�临�Ӷȣ� O��n log n��
�ռ为��ȣ� O��log n��*/ 
void QuickSort_Recursion(int *a, int begin, int end){ //�������򣨵ݹ�棩
	int i = begin;
    int j = end;
    int key = a[begin];
    if (begin >= end){  //���low >= high˵�����������
        return ;
    }
    while (begin < end) {  //��whileѭ������һ�α�ʾ�Ƚ���һ��
        while (begin < end && key <= a[end]) {
            --end;  //��ǰѰ��
        }
        if (key > a[end]){
            Swap(&a[begin], &a[end]);
            ++begin;
        }
        while (begin < end && key >= a[begin]){
            ++begin;  //���Ѱ��
        }
        if (key < a[begin]){
            Swap(&a[begin], &a[end]);
            --end;
        }
    }
    QuickSort_Recursion(a, i, begin-1); //����߽������� 
    QuickSort_Recursion(a, begin+1, j);  //���ұ߽������� 
}


void QuickSort(int *a,int size){ //��ͨ�ݹ�
	stack s;   //ʹ��ջ 
	int position;  //�����ŵ�ֵ 
	int left = 0;  
	int right = 0;
	InitStack(&s);  //��ʼ��ջ 
	PushStack(&s, 0);   //��0��ջ 
	PushStack(&s, size);   //��size��С��ջ 
	while (!EmptyStack(&s))  //��Ϊ�� 
	{
		right = TopStack(&s);  //���ұߵ�����Ϊsize 
		PopStack(&s);    //��ջ 
		left=TopStack(&s);  //�����Ϊ0 
		PopStack(&s);  //��ջ 
		position = Partition(a, left, right - 1);  //�õ� ������
		//�� ���Ż�׼��࣬���Ƚ������±���ջ
		if ((right - left) > position + 1)   
		{
			PushStack(&s, position + 1);    
			PushStack(&s, right - left);
		}
		if (position > 0)
		{
			PushStack(&s, 0);
			PushStack(&s, position);
		}
	}
}

int Partition(int *a, int begin, int end){//�������������ţ�
	int index = MiddleNumber(a, begin, end);  //�õ��м�ֵ������ 
	if(index != end){
		swap(&a[index], &a[end]);  //����������λ�� 
	}
	int key = a[end];  //key��Ϊ��׼ 
	int k=end;
	while(begin!=end){
		while(a[begin]<=key && begin<end){  //����һ���Ƚϴ�С 
			begin++;  //������ 
		}
		if(begin!=end){  //�������� 
			a[end] = a[begin];
			end--;
		}
		while(a[end] >= key && begin<end){   
			end--;  //��ǰ���� 
		}
		if(begin != end){  
			a[begin]=a[end];
			begin++;
		}
	}
	if(begin!=k){   
		a[begin] = key;  //�ѵ�һ������key 
	}
	return begin;
}

/*��������
ʱ�临�Ӷȣ� O��n��
�ռ临�Ӷȣ�O��k��*/ 
void CountSort(int *a, int size , int max){ //��������
	int k=max+1;
	int *counts, *temp;
	int i,j;
	if((counts = (int*)malloc(k*sizeof(int)))==NULL)	//Ϊ�����������ڴ�
		return ;
	if((temp = (int*)malloc(size * sizeof(int)))==NULL)	//Ϊ������Ԫ����ʱ�����������ڴ� 
		return ;
	for(i=0; i<k; i++){ //��ʼ������������ 
		counts[i] = 0;
	} 
	for (j=0; j<size;j++)//ͳ��ÿ��Ԫ�س��ֵĸ��� 
		counts[a[j]] = counts[a[j]] +1;
	for (i=1;i<k;i++)
		counts[i] = counts[i] + counts[i-1];	//��Ԫ�ر���Ĵ���������ǰһ��Ԫ�صĴ���
	for(j = size -1; j>=0; j--){	//�������� 
		temp[counts[a[j]]-1] = a[j];
		counts[a[j]] = counts[a[j]]-1;
	}
	memcpy(a, temp, size*sizeof(int));	//������õ����鿽��data 
	free(counts);
	free(temp);
}

/*������������
ʱ�临�Ӷȣ� O��n��
�ռ临�Ӷȣ� O(n) */ 
void RadixCountSort(int *a,int size){  //������������
	int *radixArray[10];   //��Ϊ0-9���ռ� 
	int i;
	for(i=0; i<10; i++){
		radixArray[i] = (int*)malloc(sizeof(int)*(size+1));
		radixArray[i][0] = 0;   //index=0����¼�������ĸ��� 
	}
	int pos;
	for (pos=1; pos<=10; pos++){  //�Ӹ�λ��10λ 
		for(i=0;i<size;i++){  //���� 
			int temp= 1,j,num;
			for(j=0; j<pos-1;j++)
				temp*=10;
			num = (a[i]/temp)%10;
			int index = ++radixArray[num][0];
			radixArray[num][index]=a[i];
		}
		int k,l;
		for(i=0, k=0; i<10;i++){  //�ռ� 
			for(l=1; l<= radixArray[i][0];l++)
				a[k++] = radixArray[i][l];
			radixArray[i][0]= 0;
		}
	}
}


void ColorSort(int *a,int size){  //��ɫ���� 
	int i=0,j=0,k=size-1,left=0,right=size-1,index=0; //���ĸ�ָ������� 
	while(left<right){      //�ж�������ұߵĴ�С 
		for(i=left;i<=right;i++){   //�������ұ� 
			if(a[i] == 2){       //���a[i]=2 
				int t = a[i];   //a[i]��a[j]���� 
				a[i] = a[k];
				a[k] = t;
				k--;
				break;
			}
			else if(a[i]==0 && i>j){  //���a[i]=0 
				int t = a[i];   //���� 
				a[i] = a[j];
				a[j] = t;
				j++;
				break;
			}
		}
		left = i;   //����ߵ�ֵ����i 
		for(i = right;i>=left;i--){   //����������� 
			if(a[i]==0){
				int t = a[i];
				a[i] = a[j];
				a[j] = t;
				j++;
				break;
			}
			else if(a[i]==2 && i<k){
				int t = a[i];
				a[i] = a[k];
				a[k] = t;
				k--;
				break;
			}
		}
		right = i;
	}
}




//�ҵ���k�����ֵ 
int findNum(int *a, int begin, int end, int k){
	int low = begin;   
	int hight = end;
	int temp = a[low];
	int flag = 0;
	while(low<hight){  //���� 
		if(0==flag){ //hightָ����low�ƶ�
 			if(a[hight]>temp)  //����һ�����ֱȽ� 
			 	hight--;  //������ 
			else{ 
				a[low++] = a[hight]; //����low=hight 
				flag = 1;
			} 
		}
		else{   //flag=1ʱ 
			if(a[low]<temp)  
				low++;  
			else{
				a[hight--] = a[low];
				flag=0;
			}
		}
	}
	if(k == low){
		return temp;  //������Ҫ�ҵ�ֵ 
	}
	else if(k>low){
		return findNum(a, low+1, end,k); //�ݹ� 
	}
	else{
		return findNum(a, begin, low-1,k);  //�ݹ� 
	}
}


//ջ�Ļ���Ӧ�� 
void  InitStack(stack *s)
{
	int *data = (int*)malloc(200000 * sizeof(int));
	if (data == NULL)
	{
		assert(0);
		return;
	}
	s->data = data;
	s->size = 0;
}

void PushStack(stack *s,int d)
{
	if (s->size > 200000)
	{
		return;
	}
	else
		s->data[s->size++] = d;
}


void PopStack(stack *s)
{
	if (s->size == 0)
	{
		return;
	}
	else
		s->size--;
}


int TopStack(stack *s)
{
	return s->data[s->size-1];
		
}
int EmptyStack(stack *s)
{
	return s->size == 0;
}


//��ӡ����
void Print(int *arr, int size)
{
	int i = 0;
	for (i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void swap(int *x, int *y)

{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

int MiddleNumber(int *a, int begin, int end){  //�ҵ��м��� 
	int mid = begin + ((end - begin) >> 1);  //λ����� 
	if (a[begin] > a[mid]){     //�жϵ�һ���������һ�����Ĵ�С 
		if (a[begin] > a[end]){   //�����һ�����������һ�� 
			if (a[mid] > a[end]){  //����м�����������һ�� 
				return mid;  //�����м� 
			}
			else
				return end;  //��������ֵ 
		}
		else
			return begin;  //���ص�һ��ֵ 
	}
	else{
		if (a[mid] > a[end]){   //����м�ֵ��������ֵ 
			if (a[begin] > a[end]){   
				return begin;
			}
			else{
				return end;
			}
		}
		else
			return mid;
	}
	
}


