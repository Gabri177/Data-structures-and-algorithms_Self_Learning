#include <stdio.h>
#include <stdlib.h>

// 变相测试 c能不能用面向对象.

typedef struct dato{
    int *nums;
    int len, front, tail;
    void (*push)(struct dato* d, int nums);
    void (*pop)(struct dato* d);
}dato;

void Push (dato* d, int nums){
    d->nums[++d->tail] = nums;
}

void Pop (dato* d){
    printf("%d\n", d->nums[++d->front]);
}



dato* InitDato (int len){
    dato* new = (dato* )malloc(sizeof(dato));
    new->nums = (int* )malloc(sizeof(int) * len);
    new->push = Push;
    new->pop = Pop;
    new->front = 0;
    new->tail = 0;
    new->len = len;
    return new;
}

int main(){
    dato* test = InitDato(5);
    test->push(test, 3);
    test->pop(test);
    free(test->nums);
    free(test);
    return 0;
}