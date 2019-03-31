#include"../head/Arithmetic1.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*ƥ������*/ 
//���ã��ж�������ַ������Ƿ����˫˫ƥ������š��������1������զ���0 
Status MatchBrack(char* str){
    char *cur = str;          //ָ��str��ָ�� 
    sqStack BrkSK;   //��ջ�����ַ� 
    data d;    //����ջ������ 
    char ch;   //���ڱ������ַ� 
    Status sta = OK;;

    if (!str || !InitStack(&BrkSK))  //��ջ������ַ� 
        return ERROR;

    while (*cur!='\0'){  //�ж��Ƿ���������    
        if (*cur=='('){  //�ж��Ƿ�Ϊ����  
            d.flag = 1;   //��flag�����Ϊ1����ʾ��һ���ַ� 
            d.number.sign = *cur;   //�����ַ�����d�� 
            Push(&BrkSK,d);    //��d����ջ�� 
        }
        else if (*cur == ')') {   //�ж��ַ��Ƿ�Ϊ������        
            if (!GetTop(BrkSK, &d)){  //ջ��û��Ԫ�� 
                sta = ERROR;
                break;
            }
            ch = d.number.sign;   //d�е��ַ���ȡ���� 
            if (*cur == ')'&&ch == '(' )  //�ж�ch�Ƿ�Ϊ�� 
                Pop(&BrkSK, &d);  //��ջ 
            else{
                sta = ERROR; 
                break;
            }
        }
        cur++;  //ָ����һ���ַ� 
    }
    DestroyStack(&BrkSK);  //�ݻٵ���һ������ 
    return sta;  
}

/*�õ���׺���ʽ*/ 
Status GetMidStack(sqStack *s, char* str){
    char* cur, *start, *end;   //cur��ָ��str��ָ�룬startָ���λ����ǰ���ָ�룬endָ�����һλ��ָ�� 
    cur = start = end = str;
    char fnum[10] = { 0 };   //������ֵ��λ�������� 
    data d;   //�������ֵĽṹ�� 

    if (!s || !str)
        return ERROR;

    while (*cur != '\0'){    
        if (!isdigit(*cur) && *cur != '.'){  //�ж�cur��Ϊ���֣��Ҳ��ǵ� 
            if (cur > str&&isdigit(*(cur - 1))){  //�ж�curǰһλ��Ϊ���� 
                end = cur;      //��endָ��cur 
                memset(fnum, 0, 10);  //���fnumΪ0 
                memcpy(fnum, start, (end - start)); //��start��ʼ���� 
                d.flag = 2;   //��flag��Ϊ2 
                d.number.num = atof(fnum);  //atof���ַ���ת��Ϊ�������� 
                Push(s, d);  //d����ջ�� 
            }
            d.flag = 1;   //��ΪcurΪ�ַ� 
            d.number.sign = *cur;  //��cur����ջ�� 
            if (isdigit(*(cur + 1)))  //���cur��һ�������֣��ͽ�startָ���� 
                start = cur + 1;
            Push(s, d);
        }
        cur++;
    }
    if (start > end){    //���Ϊ���� 
        end = cur;        
        memset(fnum, 0, 10);
        memcpy(fnum, start, (end - start));
        d.flag = 2;
        d.number.num = atof(fnum);
        Push(s, d);
    }
    return OK;
}

//��תջ 
Status RotateStack(sqStack* s){
    sqStack tempSk, *freeSk;  //����һ����ջ 
    if (!InitStack(&tempSk) || !s)
        return ERROR;
    data d; 
    int length = StackLength(*s);
    int i;
    for ( i = 0; i < length; i++){  //�ͽ�һ��ջ��ջ��ȡ�����浽��һ��ջ��ջβ�ͺ��� 
        Pop(s, &d);
        Push(&tempSk, d);
    }
    freeSk = s;  
    *s = tempSk;
    DestroyStack(freeSk);
}

/*�õ���׺���ʽ*/ 
Status GetBackStack(sqStack *s){
    sqStack OperaSk, ResSk, *tempSk;  // ��������ջ 
    OperaSk.base = ResSk.base = NULL;
    data d, top;   
    char pc;    //�洢���������
    int length = StackLength(*s);
    if (!s)
        return ERROR;
    if (!InitStack(&OperaSk) || !InitStack(&ResSk)){  //�жϳ�ʼ���Ƿ�ɹ� 
        DestroyStack(&OperaSk);
        DestroyStack(&ResSk);
        return ERROR;
    }
    int i;
    for (i = 0; i < length; i++){
        Pop(s, &d);   //��ջ 
        if (d.flag == 2)  //����Ǹ����� ������� 
            Push(&ResSk, d);
        if (d.flag == 1){  //������ַ� 
            if (GetTop(OperaSk, &top))  //���Op��ջջ��Ԫ�ش��� 
                pc = top.number.sign;  //��topԪ�صĶ�Ԫ�ظ�ֵ��pc 

            if (d.number.sign == ')'){  //���d�е��ַ�Ϊ�� 
                while (pc != '('){   //���pc�����ڣ� 
                    Pop(&OperaSk, &d);   //��ջ 
                    Push(&ResSk, d);     //��ջ 
                    GetTop(OperaSk, &top);  //��Op��ȡ��Ԫ�� 
                    pc = top.number.sign;   //pc��ֵ 
                }
                Pop(&OperaSk, &d);    //��(һ�𵯳�
                continue;
            }

            if (StackEmpty(OperaSk) || pc == '(' || d.number.sign == '(')    //����OperaSkΪ�ջ���ջ��Ϊ(���߻�ȡ�������Ϊ(,����ֱ�ӽ���������ѹջ
                Push(&OperaSk, d);
            else if ((pc == '-' || pc == '+') && (d.number.sign == '*' || d.number.sign == '/'))    //����ջ�������ȼ��ͣ�Ҳѹջ������Ҫ�Ƚ�ջ����
                Push(&OperaSk, d);
            else if (pc == d.number.sign || (pc == '-'&&d.number.sign == '+') || (pc == '+'&&d.number.sign == '-') || (pc == '*'&&d.number.sign == '/') || (pc == '/'&&d.number.sign == '*'))    //��ջ�����ȼ��͵�ǰ�����һ�£��ȵ�����ResSk���ڽ���ѹջ
            {
                Pop(&OperaSk, &top);
                Push(&ResSk, top);
                Push(&OperaSk, d);
            }
            else  //�� ��ȡ����������ȼ�����ջ�����ȼ����Ƚ�ջ���������ջ��ResSk��Ȼ���ٽ���ǰ���������һ�ν��бȽϣ�ѹջ��OperaSKջ
            {
                Pop(&OperaSk, &top);    //��ȡOperaSKջ������
                Push(&ResSk, top);        //�����ݷ���ResSKջ

                Push(s, d);    //���ڵ�ǰ����û�������ջ�����ǽ����Ż�ԭ��ջ�У��ٴν��бȽ�
                length++;
            }
        }
    }
    while (!StackEmpty(OperaSk))    //�������ջ�е�ʣ�������ȫ���Ƶ����ջ
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

//�õ��������� 
Status GetBackValue(sqStack *s, double* val)
{
    sqStack OpValSk;    //��ȡ��������ջ
    int length = StackLength(*s);
    double op1, op2, value = 0;
    data d, top;

    if (!s || !InitStack(&OpValSk))
        return ERROR;
	int i;
    for ( i = 0; i < length; i++)
    {
        Pop(s, &d);
        if (d.flag == 2)    //����
            Push(&OpValSk, d);
        else   //�����,ȡ����������󣬷Ż�ջ��
        {
            Pop(&OpValSk, &top);  //��ջ 
            op2 = top.number.num;  
            Pop(&OpValSk, &top);
            op1 = top.number.num;
            switch (d.number.sign)  //�ж�ȡ��ջ������ 
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
            d.flag = 2;   //��ֵ��Ϊ2 
            d.number.num = value; //���ջ�� 
            Push(&OpValSk, d);
        }
    }
    *val = value;
    DestroyStack(&OpValSk);
    return OK;
}
