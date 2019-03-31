#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#define MAXSIZE 100  //��׺���ʽ�ĳ��� 
#define STACK_INIT_SIZE 100      //����ջ�ĳ�ʼ��С 
#define STACK_INCR_SIZE 10 

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef struct Data{
	int flag;    //1Ϊ�ַ���2Ϊ������ 
	union{
		double num;  //���渡���� 
		char sign;   //�����ַ� 
	}number;
}data;

typedef int Status;
typedef data ElemType;

typedef struct
{
    ElemType *base;    //ջ��ָ��
    ElemType *top;    //ջ��ָ��
    int stackSize;    //������������ǿ��޸ĵ�
}sqStack;


//��������(���������)�Ļ������� 
Status InitStack(sqStack *s);    //��ʼ������������һ����ջ
Status ClearStack(sqStack *s);    //��ջ���
Status StackEmpty(sqStack s);    //��ջ���ڣ�����true�����򷵻�false
int StackLength(sqStack s);        //����ջS��Ԫ�ظ���

Status GetTop(sqStack s, ElemType *e);    //����ջ�����ҷǿգ���e����S��ջ��Ԫ��
Status Push(sqStack *s, ElemType e);    // ����ջ���ڣ�������µ�Ԫ��e��ջS�в���Ϊջ��Ԫ��
Status Pop(sqStack *s, ElemType *e);    //����ջ�����ҷǿգ�ɾ��ջ��Ԫ�أ�����e������ֵ
Status DestroyStack(sqStack *s);        //����ջ���ڣ���������

void PrintStack(sqStack s);

//������������Ҫ�ĺ��� 
Status MatchBrack(char* str);    //ƥ�������Ƿ���ȷ
Status RotateStack(sqStack* s);    //��ջ�е����ݷ�ת
Status GetMidStack(sqStack *s, char* str);    //��ȡ��׺���ʽ,���ַ���ת����ջ��
Status GetBackStack(sqStack *s);     //��ȡ��׺���ʽ
Status norGetBackStack(char *s); //��ȡ��ȷ�ĺ�׺���ʽ 
Status GetBackValue(sqStack *s, double* val);//��ȡ��׺���ʽ��������Ľ�� 


#endif  //STACK_H_INCLUDED
