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
	printf("��������Ҫ������ֵĸ�����");
	while(scanf("%d",&num)==0){
		printf("��������ȷ�����֣�");
		getchar(); 
	}
	//getchar();
	fprintf(fpWrite,"%d ",num);
	int flag=0;
	char ch;
	do{
		printf("������Ҫ�������ݵ���Сֵ��");
		scanf("%d",&lowborder);
		printf("��������Ҫ�������ݵ����ֵ��");
		scanf("%d",&upborder);
		if(lowborder>=upborder){
			flag==1;
		}
	}while(flag==1);
	//printf("%d %d",lowborder,upborder);
	srand((unsigned int)time(NULL));
	int a;
	printf("д���ļ�������Ϊ��");
	for(a=0;a<num;a++){
		randNum = (rand()%(upborder-lowborder)) + lowborder;
		printf(" %d ",randNum);
		fprintf(fpWrite,"%d ",randNum);}
	fclose(fpWrite);
	system("pause");
	system("cls");
}
