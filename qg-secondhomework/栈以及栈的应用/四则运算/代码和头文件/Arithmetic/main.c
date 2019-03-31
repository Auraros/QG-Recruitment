#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../head/Arithmetic.h"


int StackLen(SqStack s)      //�ж����ȼ����� 
{
    return (s.top - s.base);
}
 
 
 
int main()
{
    SqStack s;
    char c, e;
 
    initStack( &s );     //��ʼ��ջ 
 
    printf("��������׺���ʽ����#��Ϊ������־��");     
    scanf("%c", &c);
 
    while( c != '#' ) { //���ַ���Ϊ��#����ʱ�� 
        while( c>='0' && c<='9' ) {    //�������־����         
            printf("%c", c);
            scanf("%c", &c);
            if( c<'0' || c>'9' ){   //���������1��9�����            
                printf(" ");
            }
        }
 
        if( ')' == c ){        
            Pop(&s, &e);       // ��ջ 
            while( '(' != e ){             //��ջ���ջ��Ԫ�ز�Ϊ�� 
                printf("%c ", e);          //��� 
                Pop(&s, &e);               //������ջ 
            }
        }
        else if( '+'==c || '-'==c )        //���Ϊ+����- 
        {
            if( !StackLen(s) )     //�ж����ȼ� �������ȼ�����ջ��Ԫ�� 
            {
                Push(&s, c);       //��ջ 
            }
            else   // �����ȼ�С��ջ��Ԫ��ʱ 
            {
                do
                {
                    Pop(&s, &e);  //��ջ 
                    if( '(' == e )     //�жϳ�ջԪ���Ƿ�Ϊ�� 
                    {
                        Push(&s, e);  //������ջ 
                    }
                    else
                    {
                        printf("%c ", e);    //���ջ��Ԫ�� 
                    }
                }while( StackLen(s) && '('!=e );   
                Push(&s, c);   //������������ջ�� 
            }
        }
        else if( '*'==c || '/'==c || '('==c )   //*/���ȼ���ߣ�����ֱ����ջ 
        { 
            Push(&s, c);
        }
        else if( '#'== c )  //���Ϊ#���˳� 
        {
            break;
        }
        else
        {
            printf("\n���������ʽ����\n");
            return -1;
        }
 
        scanf("%c", &c);
    }
 
    while( StackLen(s) )
    {
        Pop(&s, &e);
        printf("%c ", e);
    }
 
    return 0;
}

