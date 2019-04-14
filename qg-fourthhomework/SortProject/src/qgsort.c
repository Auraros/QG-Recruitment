#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <assert.h>
#include "../inc/qgsort.h" 

//交换两个数字 
void Swap(int *p, int *q){
    int buf;
    buf = *p;
    *p = *q;
    *q = buf;
    return;
}

/* 插入排序：
时间复杂度： O（n^2）
空间复杂度： O（1）*/ 
void insertSort(int *a,int n){   //插入排序
	int i, j, tmp;
	for (i=1; i<n; i++){    //循环遍历数组 
		if(a[i]<a[i-1]){   //找到比左边小的数 
			tmp=a[i];          
			for (j=i-1;j>=0&&a[j]>tmp;j--){  //与右边进行判断 
				a[j+1] = a[j];  //交换 
			}
			a[j+1] = tmp;
		}
	}  	 
}

/*归并排序：
时间复杂度：O（NlogN）
空间复杂度：O（N）*/ 
void MergeAdd(int *a,int begin,int mid,int end,int *temp){ //归并排序
	int i = begin;
	int j = mid + 1;
	int k = begin;//临时下标
	while (i <= mid&&j <= end){  //当i<中间值和j小于最后时 
		if (a[i] < a[j]){    //判断大小 
			temp[k++] = a[i++];   //交换 
		}
		else{
			temp[k++] = a[j++]; //交换 
		}
	}
	while (i <= mid){
		temp[k++] = a[i++];  //将i以后的数字都拷贝到temp 
	}
	while (j <= end){
		temp[k++] = a[j++];  //将j以后的数字都拷贝到temp 
	}  
	memcpy(a + begin, temp + begin, sizeof(int)*(end - begin+1)); //把temp内容拷贝给a 
}

//递归实现 归并排序 
void MergeSort(int *a ,int begin,int end,int *temp){//实现“分”
	int mid = 0;
	if (begin < end){
		mid = begin + (end - begin) / 2;  //得到中间索引值 
		MergeSort(a, begin, mid, temp);   //对前面一部分进行排序 
		MergeSort(a, mid + 1, end, temp);  //对后面一部分进行排序 
		MergeAdd(a, begin, mid, end, temp);  //合起来 
	}
}	

/*快速排序
时间复杂度： O（n log n）
空间负责度： O（log n）*/ 
void QuickSort_Recursion(int *a, int begin, int end){ //快速排序（递归版）
	int i = begin;
    int j = end;
    int key = a[begin];
    if (begin >= end){  //如果low >= high说明排序结束了
        return ;
    }
    while (begin < end) {  //该while循环结束一次表示比较了一轮
        while (begin < end && key <= a[end]) {
            --end;  //向前寻找
        }
        if (key > a[end]){
            Swap(&a[begin], &a[end]);
            ++begin;
        }
        while (begin < end && key >= a[begin]){
            ++begin;  //向后寻找
        }
        if (key < a[begin]){
            Swap(&a[begin], &a[end]);
            --end;
        }
    }
    QuickSort_Recursion(a, i, begin-1); //对左边进行排序 
    QuickSort_Recursion(a, begin+1, j);  //对右边进行排序 
}


void QuickSort(int *a,int size){ //普通递归
	stack s;   //使用栈 
	int position;  //枢轴存放的值 
	int left = 0;  
	int right = 0;
	InitStack(&s);  //初始化栈 
	PushStack(&s, 0);   //将0入栈 
	PushStack(&s, size);   //将size大小入栈 
	while (!EmptyStack(&s))  //不为空 
	{
		right = TopStack(&s);  //最右边的数字为size 
		PopStack(&s);    //出栈 
		left=TopStack(&s);  //最左边为0 
		PopStack(&s);  //出栈 
		position = Partition(a, left, right - 1);  //得到 枢轴存放
		//先 快排基准左侧，则先将后侧的下标入栈
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

int Partition(int *a, int begin, int end){//快速排序（枢轴存放）
	int index = MiddleNumber(a, begin, end);  //得到中间值的索引 
	if(index != end){
		swap(&a[index], &a[end]);  //交换到最后个位置 
	}
	int key = a[end];  //key作为基准 
	int k=end;
	while(begin!=end){
		while(a[begin]<=key && begin<end){  //跟第一个比较大小 
			begin++;  //向后遍历 
		}
		if(begin!=end){  //如果不相等 
			a[end] = a[begin];
			end--;
		}
		while(a[end] >= key && begin<end){   
			end--;  //向前遍历 
		}
		if(begin != end){  
			a[begin]=a[end];
			begin++;
		}
	}
	if(begin!=k){   
		a[begin] = key;  //把第一个换成key 
	}
	return begin;
}

/*计数排序
时间复杂度： O（n）
空间复杂度：O（k）*/ 
void CountSort(int *a, int size , int max){ //计数排序
	int k=max+1;
	int *counts, *temp;
	int i,j;
	if((counts = (int*)malloc(k*sizeof(int)))==NULL)	//为计数器分配内存
		return ;
	if((temp = (int*)malloc(size * sizeof(int)))==NULL)	//为已排序元素临时存放数组分配内存 
		return ;
	for(i=0; i<k; i++){ //初始化计数器数组 
		counts[i] = 0;
	} 
	for (j=0; j<size;j++)//统计每个元素出现的个数 
		counts[a[j]] = counts[a[j]] +1;
	for (i=1;i<k;i++)
		counts[i] = counts[i] + counts[i-1];	//将元素本身的次数加上它前一个元素的次数
	for(j = size -1; j>=0; j--){	//放置数字 
		temp[counts[a[j]]-1] = a[j];
		counts[a[j]] = counts[a[j]]-1;
	}
	memcpy(a, temp, size*sizeof(int));	//将排序好的数组拷回data 
	free(counts);
	free(temp);
}

/*基数计数排序：
时间复杂度： O（n）
空间复杂度： O(n) */ 
void RadixCountSort(int *a,int size){  //基数计数排序
	int *radixArray[10];   //分为0-9个空间 
	int i;
	for(i=0; i<10; i++){
		radixArray[i] = (int*)malloc(sizeof(int)*(size+1));
		radixArray[i][0] = 0;   //index=0处记录这个数组的个数 
	}
	int pos;
	for (pos=1; pos<=10; pos++){  //从个位到10位 
		for(i=0;i<size;i++){  //分配 
			int temp= 1,j,num;
			for(j=0; j<pos-1;j++)
				temp*=10;
			num = (a[i]/temp)%10;
			int index = ++radixArray[num][0];
			radixArray[num][index]=a[i];
		}
		int k,l;
		for(i=0, k=0; i<10;i++){  //收集 
			for(l=1; l<= radixArray[i][0];l++)
				a[k++] = radixArray[i][l];
			radixArray[i][0]= 0;
		}
	}
}


void ColorSort(int *a,int size){  //颜色排序 
	int i=0,j=0,k=size-1,left=0,right=size-1,index=0; //用四个指针来标记 
	while(left<right){      //判断左边与右边的大小 
		for(i=left;i<=right;i++){   //遍历到右边 
			if(a[i] == 2){       //如果a[i]=2 
				int t = a[i];   //a[i]与a[j]交换 
				a[i] = a[k];
				a[k] = t;
				k--;
				break;
			}
			else if(a[i]==0 && i>j){  //如果a[i]=0 
				int t = a[i];   //交换 
				a[i] = a[j];
				a[j] = t;
				j++;
				break;
			}
		}
		left = i;   //将左边的值等于i 
		for(i = right;i>=left;i--){   //反向进行排序 
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




//找到第k个大的值 
int findNum(int *a, int begin, int end, int k){
	int low = begin;   
	int hight = end;
	int temp = a[low];
	int flag = 0;
	while(low<hight){  //遍历 
		if(0==flag){ //hight指针往low移动
 			if(a[hight]>temp)  //跟第一个数字比较 
			 	hight--;  //向后遍历 
			else{ 
				a[low++] = a[hight]; //否则low=hight 
				flag = 1;
			} 
		}
		else{   //flag=1时 
			if(a[low]<temp)  
				low++;  
			else{
				a[hight--] = a[low];
				flag=0;
			}
		}
	}
	if(k == low){
		return temp;  //返回需要找的值 
	}
	else if(k>low){
		return findNum(a, low+1, end,k); //递归 
	}
	else{
		return findNum(a, begin, low-1,k);  //递归 
	}
}


//栈的基本应用 
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


//打印函数
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

int MiddleNumber(int *a, int begin, int end){  //找到中间数 
	int mid = begin + ((end - begin) >> 1);  //位运算符 
	if (a[begin] > a[mid]){     //判断第一个数和最后一个数的大小 
		if (a[begin] > a[end]){   //如果第一个数大于最后一个 
			if (a[mid] > a[end]){  //如果中间的数大于最后一个 
				return mid;  //返回中间 
			}
			else
				return end;  //返回最后的值 
		}
		else
			return begin;  //返回第一个值 
	}
	else{
		if (a[mid] > a[end]){   //如果中间值大于最后的值 
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


