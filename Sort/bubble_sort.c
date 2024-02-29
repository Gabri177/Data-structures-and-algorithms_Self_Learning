#include <stdio.h>

void bubbleSort (int, int[]);
void swi (int*, int*);

int main() {
    int arr[] = { 22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70 };
    int len = (int) sizeof(arr) / sizeof(*arr);
    bubbleSort(len, arr);
    int i;
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);
    return 0;
}

void bubbleSort (int num, int ary[]){
    int i, j = 0, a;
    a = num;
    num--;
    while(num != 0){
        for(i = 0;i < num;i++){
            if (ary[i] > ary[i + 1]){
                swi(&ary[i], &ary[i + 1]);
            }
        }
        num--;
    }
}

void swi (int *a, int *b){
    int mid;
    mid = *a;
    *a = *b;
    *b = mid;

}
