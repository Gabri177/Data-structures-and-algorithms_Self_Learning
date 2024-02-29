#include <stdio.h>

void swap (int*, int*);
void quickSortIteracion (int[], int, int);

int main(){
    int arr[] = { 22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70, 1, 200};
    int len = (int)sizeof(arr)/(int)sizeof(arr[0]);
    quickSortIteracion(arr, 0, len - 1);
    int i;
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);  
    return 0;
}

void quickSortIteracion (int ary[], int front, int tail){
    int len = tail - front;
    if (len <= 1) return;
    len--;
    int left = front, right = tail;
    int midValue = ary[(left + right) / 2];
    while (left <= right)
    {
        while (ary[left] < midValue)left++;
        while (ary[right] > midValue)right--;
        if (left <= right)swap(&ary[left++], &ary[right--]); //别忘了啊啊啊啊
    
    }
    if(front < right)quickSortIteracion(ary, front, right);
    if(left < tail)quickSortIteracion(ary, left, tail);
}

void swap (int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}