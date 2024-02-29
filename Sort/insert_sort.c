#include <stdio.h>

void inserSort (int, int[]);




int main() {
    int arr[] = { 22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70 };
    int len = (int) sizeof(arr) / sizeof(*arr);
    inserSort(len, arr);
    int i;
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);
    return 0;
}

void inserSort (int num, int ary[]){
    int i, j, temp;
    for (i = 1; i < num; i++){
        temp = ary[i];
        for(j = i; j > 0 && ary[j-1] > temp; j--){
            ary[j] = ary[j - 1];
        }
        ary[j] = temp;
    }


}