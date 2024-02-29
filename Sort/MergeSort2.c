#include <unistd.h>
#include <stdio.h>

void PutChar_ (char c){
    write(STDOUT_FILENO, &c, 1);
}

char NumtoChar (int num){
    return (char)(num + '0');
}

void putnums (int num){
    if(num < 10){
        PutChar_(NumtoChar(num));
    }else{
        int a1 = num % 10;
        int a10 = num / 10;
        PutChar_(NumtoChar(a10));
        PutChar_(NumtoChar(a1));
    }
    PutChar_(' ');
    PutChar_(' ');
}

void MergeSort (int ary[],int start, int end){
    if (start >= end) return;
    int mid = start + (end - start) / 2;
    int start1 = start;
    int start2 = mid + 1;
    int temp[end - start + 1], p = 0;
    MergeSort(ary, start1, mid);
    MergeSort(ary, start2, end);
    while (start1 <= mid && start2 <= end){
        temp[p++] = ary[start1] < ary[start2] ? ary[start1++] : ary[start2++];
    }
    while (start1 <= mid)temp[p++] = ary[start1++];
    while (start2 <= end)temp[p++] = ary[start2++];
    for (int i = 0; i < p; i ++)ary[i + start] = temp[i];
}

int main (){
    printf("Starting main function\n");

    int arr[] = { 22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70, 1, 20};
    int len = (int)sizeof(arr)/(int)sizeof(arr[0]);
    MergeSort(arr, 0, len - 1);
    int i;
    for (i = 0; i < len; i++)
        putnums(arr[i]);
    return 0;
}