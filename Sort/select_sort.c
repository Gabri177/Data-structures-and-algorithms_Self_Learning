#include <stdio.h>

void swnums (int*, int*);
void slec_sort(int, int[]);

int main (){
    int arr[] = { 22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70 };
    int len = (int) sizeof(arr) / sizeof(*arr); 
    slec_sort(len, arr);
    for(int i = 0; i < len; i++){
        printf("%d  ", arr[i]);
    }
    return 0;
}

void swnums (int* a, int* b){
    int c;
    c = *a;
    *a = *b;
    *b = c;
}

void slec_sort(int num, int ary[]){
    num--;
    int max = ary[0], i, po = 0;
    while (num != 0){
        for (i = 0; i <= num; i++){
            if(max < ary[i]){
                max = ary[i];
                po = i;
                //printf("arry[%d] = %d\n", po, ary[po]);
            }
        }
        swnums(&ary[num], &ary[po]);
        max = ary[0];
        po = 0;
        num--;
    }
}