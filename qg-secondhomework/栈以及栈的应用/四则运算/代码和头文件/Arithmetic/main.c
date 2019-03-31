#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../head/Arithmetic.h"


int StackLen(SqStack s)      //判断优先级函数 
{
    return (s.top - s.base);
}
 
 
 
int main()
{
    SqStack s;
    char c, e;
 
    initStack( &s );     //初始化栈 
 
    printf("请输入中缀表达式，以#作为结束标志：");     
    scanf("%c", &c);
 
    while( c != '#' ) { //当字符不为‘#’的时候 
        while( c>='0' && c<='9' ) {    //遇到数字就输出         
            printf("%c", c);
            scanf("%c", &c);
            if( c<'0' || c>'9' ){   //如果数字是1到9则输出            
                printf(" ");
            }
        }
 
        if( ')' == c ){        
            Pop(&s, &e);       // 出栈 
            while( '(' != e ){             //出栈后的栈顶元素不为） 
                printf("%c ", e);          //输出 
                Pop(&s, &e);               //继续出栈 
            }
        }
        else if( '+'==c || '-'==c )        //如果为+或者- 
        {
            if( !StackLen(s) )     //判断优先级 ，当优先级大于栈顶元素 
            {
                Push(&s, c);       //入栈 
            }
            else   // 当优先级小于栈顶元素时 
            {
                do
                {
                    Pop(&s, &e);  //出栈 
                    if( '(' == e )     //判断出栈元素是否为（ 
                    {
                        Push(&s, e);  //继续入栈 
                    }
                    else
                    {
                        printf("%c ", e);    //输出栈顶元素 
                    }
                }while( StackLen(s) && '('!=e );   
                Push(&s, c);   //最后将运算符放入栈中 
            }
        }
        else if( '*'==c || '/'==c || '('==c )   //*/优先级最高，所以直接入栈 
        { 
            Push(&s, c);
        }
        else if( '#'== c )  //如果为#则退出 
        {
            break;
        }
        else
        {
            printf("\n出错：输入格式错误！\n");
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

