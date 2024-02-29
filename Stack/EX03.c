#include <stdio.h>
#include <stdlib.h>

#define SIZE_ARRAY 100
#define ERROR 0
#define OK 1
typedef int Elem;

typedef struct _Stack
{
    Elem* Value;
    int size;
}Stack;



int InitStack (Stack* s){
    if(!s->size) return ERROR;
    s->Value = (int* )malloc(SIZE_ARRAY * sizeof(Elem));
    s->size = 0;
    return OK;
}

int Push (Stack* s, Elem v){
    if(s->size == SIZE_ARRAY) return ERROR;
    s->Value[++s->size] = v;
    return OK;
}

int Pop (Stack* s){
    if(!s->size) return ERROR;
    printf("POP:  %d\n", s->Value[s->size--]);
    return OK; 
}

int DestroyStack (Stack s){
    if(!s.Value) return ERROR;
    free(s.Value);
    return OK;
}

int Peek(Stack s){
    if(!s.size){
        printf("PEEK: 顶部元素为空");
        return ERROR;
    }
    printf("PEEK:  %d\n", s.Value[s.size]);
    return OK;
}


int main (){
    Stack A;
    InitStack(&A);
    Push(&A, 10);
    Push(&A, 9);
    Push(&A, 8);
    Push(&A, 7);
    Push(&A, 6);
    Pop(&A);
    Peek(A);
    DestroyStack(A);
    return 0;
}
