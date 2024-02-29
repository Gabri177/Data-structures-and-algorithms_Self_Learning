#include <stdio.h>

typedef struct _Range{
    int front;
    int tail;
}Range;


void swap (int*, int*);
void qikSort (int[], int);
Range buildRange (int, int);

int main (){
    int arr[] = { 22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70, 1, 200};
    int len = (int) sizeof(arr) / sizeof(*arr);
    qikSort(arr, len);
    int i;
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);  
    return 0;
}

void swap (int* num1, int* num2){
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

Range buildRange (int start, int end){
    Range sample;
    sample.front = start;
    sample.tail = end;
    return sample;
}

void qikSort (int ary[], int len){
    if (len <= 0) return;
    Range block[len];
    int times = 0;
    block[times++] = buildRange (0, len - 1);
    while (times)
    {
        int left, right, midValue;
        Range temBlock = block[--times];
        if (temBlock.front <= temBlock.tail){
            left = temBlock.front;
            right = temBlock.tail;
            midValue = ary[(temBlock.front + temBlock.tail) / 2];
        }
        while (left <= right){
            while (ary[left] < midValue)++left;
            while (ary[right] > midValue)--right;
            if (left <= right){
                swap (&ary[left], &ary[right]);
                left++;
                right--;
            }
        }
        
        if (temBlock.front < right) block[times++] = buildRange(temBlock.front, right);
        if (temBlock.tail > left) block[times++] = buildRange(left, temBlock.tail);

    }
 
}