#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//还是一个由链表实现的栈结构, 自己改进了一下, 然后优化了一下结构和逻辑思路.
//这和EX00 用了同样的实现方式, 链表都是用了哨兵节点, 可以方便的判断是否为空栈;

#define ERROR 0
#define OK 1

typedef struct Elem
{
    int Value;
    char Name[30];
}_Elem;

typedef struct _Stack{
    _Elem Element;
    struct _Stack* dote;
}Stack;

int InitStack (Stack** s){
    *s = (Stack* )malloc(sizeof(Stack)); 
    if(!(*s)) return ERROR;
    (*s)->dote = NULL;
    strcpy((*s)->Element.Name,"");
    (*s)->Element.Value = 0;
    return OK;
}

int Push (Stack** s, int Num, char Nams[]){
    Stack* temp;
    temp = (Stack* )malloc(sizeof(Stack));
    if(!temp) return ERROR;
    temp->dote = *s;
    temp->Element.Value = Num;
    strcpy(temp->Element.Name, Nams);
    *s = temp;
    return OK;
}

int Pop (Stack** s){
    if(!(*s)->dote){
        printf("栈中并未存储任何信息.\n");
        return ERROR;
    }
    Stack* temp = *s;
    *s = (*s)->dote;
    printf("当前存储的 %s 的分数为: %d\n", temp->Element.Name, temp->Element.Value);
    free(temp);
    return OK;
}

int DestoryStack(Stack* s){
    Stack* temp;
    while(s){
        temp = s;
        s = s->dote;
        free(temp);
    }
    return OK;
    
}

int Peek (Stack s){
    if(!s.dote){
        printf("PEEK: 当前并无存储任何信息 !!! \n");
        return ERROR;
    }
    printf("PEEK:当前存储的 %s 的分数为: %d\n", s.Element.Name, s.Element.Value);
    return OK;
}

int main(){
    Stack* Top;
    InitStack(&Top);
    Push(&Top, 100, "Gabriel");
    Push(&Top, 60, "XiaoMing");
    Pop(&Top);
    Pop(&Top);
    Pop(&Top);
    Pop(&Top);
    DestoryStack(Top);
    return 0;
}
