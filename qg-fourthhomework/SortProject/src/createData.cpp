#include <stdlib.h>
#include<time.h>
#include<stdio.h>

int main() {
	int num,upborder=0,lowborder=0;
	int temp;
	int randNum;
	FILE *fpWrite=fopen("data.txt","w");
	if(fpWrite==NULL)
		return 0;
	printf("输入你想要添加数字的个数：");
	while(scanf("%d",&num)==0){
		printf("请输入正确的数字：");
		getchar(); 
	}
	//getchar();
	fprintf(fpWrite,"%d ",num);
	int flag=0;
	char ch;
	do{
		printf("输入你要生成数据的最小值：");
		scanf("%d",&lowborder);
		printf("请输入你要生成数据的最大值：");
		scanf("%d",&upborder);
		if(lowborder>=upborder){
			flag==1;
		}
	}while(flag==1);
	//printf("%d %d",lowborder,upborder);
	srand((unsigned int)time(NULL));
	int a;
	printf("写入文件的数据为：");
	for(a=0;a<num;a++){
		randNum = (rand()%(upborder-lowborder)) + lowborder;
		printf(" %d ",randNum);
		fprintf(fpWrite,"%d ",randNum);}
	fclose(fpWrite);
	system("pause");
	system("cls");
}
