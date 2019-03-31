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
    sk.base = sk.top = NULL;    //用于判断是否存在
    InitStack(&sk);//初始化栈 
    printf("请输入你要计算的中缀表达式:");
    scanf("%s", str);
    if (!MatchBrack(str)) //进行括号匹配 
        return 0;
	//norGetBackStack(str);  //没写出来 
    GetMidStack(&sk, str); //将字符串 中的中缀表达式分割
    RotateStack(&sk);//将上面的中缀 表达式翻转，变为正常的
    GetBackStack(&sk);//下面 将中缀表达式转后缀表达式
	RotateStack(&sk);//将上面 的后缀表达式翻转，变为正常的
    GetBackValue(&sk, &value);//获取后 缀表达式结果
    printf("输出的值为:", value);
    PrintStack(sk);
    DestroyStack(&sk);
    system("pause");
    return 0;
}

