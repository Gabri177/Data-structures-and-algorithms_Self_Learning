#include <stdio.h>

// 归并排序  递归算法
void MergeSort (int[], int); //归并排序函数
void MergeSortIteracion (int[], int[], int, int); //切片递归排序函数

int main (){
    int arr[] = { 22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70, 1, 200};
    int len = (int) sizeof(arr) / sizeof(*arr);
    MergeSort(arr, len);
    int i;
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);
    return 0;

}

void MergeSort (int ary[], int len){
    int temp[len];
    MergeSortIteracion(ary, temp, 0, len - 1);
}

void MergeSortIteracion (int ary[], int tem[], int start, int end){
    if (start >= end){ //递归中要注意递归终止条件 
        return;
    }
    int k = start; // 辅助数组的下标值
    int len = end - start;
    int mid = (len >> 1) + start; //算切片的中间值 
    
    int start1 = start, end1 = mid; //第一个切片
    int start2 = mid + 1, end2 = end; //第二个切片

    MergeSortIteracion (ary, tem, start1, end1); //对第一个切片进行再切片递归
    MergeSortIteracion (ary, tem ,start2, end2); //对第二个切片进行再切片递归


    while (start1 <= end1 && start2 <= end2){
       tem[k++] = ary[start1] < ary[start2] ? ary[start1++] : ary[start2++];
    }
    while (start1 <= end1){
        tem[k++] = ary[start1++]; //别忘了对start1进行++运算
    }
    while (start2 <= end2){
        tem[k++] = ary[start2++]; //此处注意的问题同上
    }
    for (k = start; k <= end; k++){ //注意将已经对切片两个切片排好顺序的辅助数组放到原数组中
        ary[k] = tem[k];
    }
}