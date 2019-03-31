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
    GetMidStack(&sk, str); //���ַ��� �е���׺���ʽ�ָת��Ϊ��׺���ʽ�����ջ��'1+2+3'--->3.0 + 2.0 + 1.0ÿһ������һ��ջ�ռ�����
    RotateStack(&sk);//���������׺ ���ʽ��ת����Ϊ������
    GetBackStack(&sk);//���� ����׺���ʽת��׺���ʽ
	RotateStack(&sk);//������ �ĺ�׺���ʽ��ת����Ϊ������
    PrintStack(sk);
    GetBackValue(&sk, &value);//��ȡ�� ׺���ʽ���
    printf("�����ֵΪ:", value);
    PrintStack(sk);
    DestroyStack(&sk);
    system("pause");
    return 0;
}

