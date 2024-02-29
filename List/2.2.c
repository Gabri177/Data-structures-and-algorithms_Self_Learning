#include <stdlib.h>


#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFERASIBLE -1
#define OVERFLOW -2
// Status 是函数的类型, 其值是函数结果状态代码
typedef int Status;
typedef int ElemType;


// 一一一一线性表的动态分配顺序存储结构 -----
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef struct
{
    ElemType* elem;
    int length;
    int listsize;
}SqList;

Status InitList_Sq (SqList* L){
    //构造一个空的线性表L
    L->elem = (ElemType* )malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L->elem) exit(OVERFLOW); // 存储分配失败
    L->length = 0; //空表长度为0
    L->listsize = LIST_INIT_SIZE; // 初始存储容量
    return OK;
}

Status ListInsert_Sq (SqList* L, int i, ElemType e){
    // 在顺序线性表L中第i哥位置之前插入新的元素e,
    // i的合法值为 1 <= i <= ListLength_Sq (L) + 1
    if (i < 1 || i > L->length + 1) return ERROR;
    if (L->length >= L->listsize){
        ElemType* newbase;
        newbase = (ElemType* )realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)exit(OVERFLOW);
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }
    ElemType* q = L->elem[i - 1];
    ElemType* p;
    for (p = L->elem[L->length - 1]; p >= q; --p){
        *(p + 1) = *p;
    }
    *q = e;
    ++ L->length;
    return OK;
}

Status ListDelete_Sq (SqList* L, int i, ElemType* e){
    // 在顺序线性表L中删除第i个元素, 并用e返回其值
    if((i < 1) || (i > L->length))return ERROR;
    ElemType* p, q;
    p = L->elem[i - 1];
    e = *p;
    q = L->elem+ L->length - 1;
    for (++p; p <= q; ++p) *(p-1) = *p;
    L->length--;
    return OK;
}