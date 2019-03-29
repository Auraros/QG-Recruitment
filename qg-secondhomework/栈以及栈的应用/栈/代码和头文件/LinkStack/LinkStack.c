

//链栈(基于链表的)
Status initLStack(LinkStack *s)   //初始化

bool isEmptyLStack(LinkStack *s)  //判断链栈是否为空

Status getTopLStack(LinkStack *s,ElemType *e)  //得到栈顶元素

Status clearLStack(LinkStack *s)   //清空栈

Status destroyLStack(LinkStack *s)   //销毁栈

Status LStackLength(LinkStack *s,int *length)    //检测栈长度

Status pushLStack(LinkStack *s,ElemType data)   //入栈

Status popLStack(LinkStack *s,ElemType *data)   //出栈
