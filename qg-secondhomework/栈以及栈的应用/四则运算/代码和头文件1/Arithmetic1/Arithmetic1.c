#include"../head/Arithmetic1.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*匹配括号*/ 
//作用：判断输入的字符串中是否存在双双匹配的括号。存在输出1；不存咋输出0 
Status MatchBrack(char* str){
    char *cur = str;          //指向str的指针 
    sqStack BrkSK;   //新栈储存字符 
    data d;    //存入栈的数据 
    char ch;   //用于遍历的字符 
    Status sta = OK;;

    if (!str || !InitStack(&BrkSK))  //空栈，或空字符 
        return ERROR;

    while (*cur!='\0'){  //判断是否遍历到最后    
        if (*cur=='('){  //判断是否为括号  
            d.flag = 1;   //将flag，标记为1，表示是一个字符 
            d.number.sign = *cur;   //将该字符存入d中 
            Push(&BrkSK,d);    //将d存入栈中 
        }
        else if (*cur == ')') {   //判断字符是否为右括号        
            if (!GetTop(BrkSK, &d)){  //栈顶没有元素 
                sta = ERROR;
                break;
            }
            ch = d.number.sign;   //d中的字符提取出来 
            if (*cur == ')'&&ch == '(' )  //判断ch是否为（ 
                Pop(&BrkSK, &d);  //出栈 
            else{
                sta = ERROR; 
                break;
            }
        }
        cur++;  //指向下一个字符 
    }
    DestroyStack(&BrkSK);  //摧毁掉下一个链表 
    return sta;  
}

/*得到中缀表达式*/ 
Status GetMidStack(sqStack *s, char* str){
    char* cur, *start, *end;   //cur：指向str的指针，start指向多位数最前面的指针，end指向最后一位的指针 
    cur = start = end = str;
    char fnum[10] = { 0 };   //用来赋值多位数的数组 
    data d;   //储存数字的结构体 

    if (!s || !str)
        return ERROR;

    while (*cur != '\0'){    
        if (!isdigit(*cur) && *cur != '.'){  //判断cur不为数字，且不是点 
            if (cur > str&&isdigit(*(cur - 1))){  //判断cur前一位数为数字 
                end = cur;      //将end指向cur 
                memset(fnum, 0, 10);  //清空fnum为0 
                memcpy(fnum, start, (end - start)); //从start开始复制 
                d.flag = 2;   //将flag设为2 
                d.number.num = atof(fnum);  //atof将字符串转化为浮点类型 
                Push(s, d);  //d存入栈中 
            }
            d.flag = 1;   //因为cur为字符 
            d.number.sign = *cur;  //将cur存入栈中 
            if (isdigit(*(cur + 1)))  //如果cur下一个是数字，就将start指向它 
                start = cur + 1;
            Push(s, d);
        }
        cur++;
    }
    if (start > end){    //最后为数字 
        end = cur;        
        memset(fnum, 0, 10);
        memcpy(fnum, start, (end - start));
        d.flag = 2;
        d.number.num = atof(fnum);
        Push(s, d);
    }
    return OK;
}

//反转栈 
Status RotateStack(sqStack* s){
    sqStack tempSk, *freeSk;  //建立一个新栈 
    if (!InitStack(&tempSk) || !s)
        return ERROR;
    data d; 
    int length = StackLength(*s);
    int i;
    for ( i = 0; i < length; i++){  //就将一个栈的栈顶取出，存到另一个栈的栈尾就好了 
        Pop(s, &d);
        Push(&tempSk, d);
    }
    freeSk = s;  
    *s = tempSk;
    DestroyStack(freeSk);
}

/*得到后缀表达式*/ 
Status GetBackStack(sqStack *s){
    sqStack OperaSk, ResSk, *tempSk;  // 建立两个栈 
    OperaSk.base = ResSk.base = NULL;
    data d, top;   
    char pc;    //存储单个运算符
    int length = StackLength(*s);
    if (!s)
        return ERROR;
    if (!InitStack(&OperaSk) || !InitStack(&ResSk)){  //判断初始化是否成功 
        DestroyStack(&OperaSk);
        DestroyStack(&ResSk);
        return ERROR;
    }
    int i;
    for (i = 0; i < length; i++){
        Pop(s, &d);   //出栈 
        if (d.flag == 2)  //如果是浮点数 ，则输出 
            Push(&ResSk, d);
        if (d.flag == 1){  //如果是字符 
            if (GetTop(OperaSk, &top))  //如果Op的栈栈顶元素存在 
                pc = top.number.sign;  //将top元素的顶元素赋值给pc 

            if (d.number.sign == ')'){  //如果d中的字符为） 
                while (pc != '('){   //如果pc不等于（ 
                    Pop(&OperaSk, &d);   //出栈 
                    Push(&ResSk, d);     //入栈 
                    GetTop(OperaSk, &top);  //从Op中取顶元素 
                    pc = top.number.sign;   //pc赋值 
                }
                Pop(&OperaSk, &d);    //将(一起弹出
                continue;
            }

            if (StackEmpty(OperaSk) || pc == '(' || d.number.sign == '(')    //若是OperaSk为空或者栈顶为(或者获取的运算符为(,我们直接将这个运算符压栈
                Push(&OperaSk, d);
            else if ((pc == '-' || pc == '+') && (d.number.sign == '*' || d.number.sign == '/'))    //若是栈顶的优先级低，也压栈，但是要先将栈顶的
                Push(&OperaSk, d);
            else if (pc == d.number.sign || (pc == '-'&&d.number.sign == '+') || (pc == '+'&&d.number.sign == '-') || (pc == '*'&&d.number.sign == '/') || (pc == '/'&&d.number.sign == '*'))    //当栈顶优先级和当前运算符一致，先弹出到ResSk，在进行压栈
            {
                Pop(&OperaSk, &top);
                Push(&ResSk, top);
                Push(&OperaSk, d);
            }
            else  //当 获取的运算符优先级低于栈顶优先级，先将栈顶运算符移栈到ResSk，然后再将当前运算符与下一次进行比较，压栈到OperaSK栈
            {
                Pop(&OperaSk, &top);    //获取OperaSK栈顶数据
                Push(&ResSk, top);        //将数据放入ResSK栈

                Push(s, d);    //由于当前数据没有完成入栈，我们将它放回原来栈中，再次进行比较
                length++;
            }
        }
    }
    while (!StackEmpty(OperaSk))    //将运算符栈中的剩余的数据全部移到结果栈
    {
        Pop(&OperaSk, &d);
        Push(&ResSk, d);
    }
    tempSk = s;
    *s = ResSk;
    DestroyStack(tempSk);
    DestroyStack(&OperaSk);
    return OK;
}

//得到最终数据 
Status GetBackValue(sqStack *s, double* val)
{
    sqStack OpValSk;    //获取运算结果的栈
    int length = StackLength(*s);
    double op1, op2, value = 0;
    data d, top;

    if (!s || !InitStack(&OpValSk))
        return ERROR;
	int i;
    for ( i = 0; i < length; i++)
    {
        Pop(s, &d);
        if (d.flag == 2)    //数字
            Push(&OpValSk, d);
        else   //运算符,取两个数运算后，放回栈中
        {
            Pop(&OpValSk, &top);  //出栈 
            op2 = top.number.num;  
            Pop(&OpValSk, &top);
            op1 = top.number.num;
            switch (d.number.sign)  //判断取出栈的类型 
            {
            case '+':
                value = op1 + op2;
                break;
            case '-':
                value = op1 - op2;
                break;
            case '*':
                value = op1 * op2;
                break;
            case '/':
                value = op1 / op2;
                break;
            default:
                break;
            }
            d.flag = 2;   //将值定为2 
            d.number.num = value; //存回栈中 
            Push(&OpValSk, d);
        }
    }
    *val = value;
    DestroyStack(&OpValSk);
    return OK;
}
