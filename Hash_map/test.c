#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct nums{
    int index;
    int* val;
}Num;

Num* InitNum (){
    Num* temp;
    temp = (Num* )malloc(sizeof(Num));
    temp->val = (int* )malloc(sizeof(int) * 10);
    temp->val[0] = 1;
    return temp;
}

void GetNext (char* ary, int size, int *next){
    int index = 1;
    int len = 0;
    next[0] = 0;
    while (index < size){
        if(ary[index] == ary[len]){
            len ++;
            next[index] = len;
            index ++;
        }else{
            if(len != 0){
                len = 0;
            }
            else {
                next[index] = 0;
                index++;
            }
        }
    }
    
    
}

void printNum (int num){
    printf("%d\n", num);
}

void test (int val, void (*Function)(int)){
    Function(val);
}

int main() {
    // char pattern[] = "ABABCABAB";
    // int m = strlen(pattern);
    // int next[m];
    
    // GetNext(pattern, m, next);
    
    // for(int i = 0; i < m; i++) {
    //     printf("%d ", next[i]);
    // }
    // return 0;
    test (5, printNum);
    return 0;
}