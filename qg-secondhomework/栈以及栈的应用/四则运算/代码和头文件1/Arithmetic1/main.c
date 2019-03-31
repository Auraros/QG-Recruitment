#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>
#include"../head/Arithmetic1.h"

int main()
{
    sqStack sk;
    double value;
    ElemType e;
    char str[MAXSIZE] = { 0 };
    sk.base = sk.top = NULL;    //�����ж��Ƿ����
    InitStack(&sk);//��ʼ��ջ 
    printf("��������Ҫ�������׺���ʽ:");
    scanf("%s", str);
    if (!MatchBrack(str)) //��������ƥ�� 
        return 0;
	//norGetBackStack(str);  //ûд���� 
    GetMidStack(&sk, str); //���ַ��� �е���׺���ʽ�ָ�
    RotateStack(&sk);//���������׺ ���ʽ��ת����Ϊ������
    GetBackStack(&sk);//���� ����׺���ʽת��׺���ʽ
	RotateStack(&sk);//������ �ĺ�׺���ʽ��ת����Ϊ������
    GetBackValue(&sk, &value);//��ȡ�� ׺���ʽ���
    printf("�����ֵΪ:", value);
    PrintStack(sk);
    DestroyStack(&sk);
    system("pause");
    return 0;
}

