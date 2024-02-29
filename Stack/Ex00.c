#include <stdio.h>
#include <stdlib.h>

// 基于链表的栈实现

typedef struct Stack
{
    int data;
    int len;
    struct Stack* node;
}Stack;

int InitStack (Stack** s){ //初始化栈底元素值
    *s = (Stack* )malloc(sizeof(Stack));
    if(!*s)return 0;
    (*s)->data = 0;
    (*s)->node = NULL;
    (*s)->len = 0;
    return 1;
}

Stack* Push (Stack* s, int Value){ //返回添加完元素后的栈指针
    Stack* temp = (Stack* )malloc(sizeof(Stack));
    if(!temp) return NULL;
    temp->node = s;
    temp->data = Value;
    temp->len = s->len + 1;
    return temp;
}

Stack* Pop (Stack* s){
    if(s->node == NULL && s->data == 0){
        printf("目前无元素!\n");
        return s;
    }
    else {
        Stack* temp = s;
        int Value = s->data;
        s = s->node;
        free(temp);
        printf("弹出元素为%d\n", Value);
        return s;
    }
}

void LenStack (Stack* s){
    printf("当前存储的元素数量为:%d\n", s->len);
}

void Peek (Stack* s){
    if (s->node != NULL) printf("栈顶部元素为: %d\n",s->data);
    else printf ("目标为空\n");
}

void BreakStack (Stack* s){
    Stack* temp;
    while (s){
        temp = s;
        s = s->node;
        free(temp);
    }
    printf("Stack已经销毁!!!\n");
    
}

int main (){
    Stack* Top;
    InitStack (&Top);
    Top = Push(Top, 10);
    LenStack(Top);
    Top = Push(Top, 4);
    LenStack(Top);
    Top = Push(Top, 1);
    LenStack(Top);
    Top = Pop(Top);
    LenStack(Top);
    Top = Pop(Top);
    LenStack(Top);
    Top = Pop(Top);
    LenStack(Top);
    Top = Pop(Top);
    Peek(Top);
    BreakStack(Top);
    return 0;
}