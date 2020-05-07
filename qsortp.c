#include<stdio.h> 
#include<omp.h>

void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high]; 
    int i = (low - 1);
  
    for (int j = low; j <= high- 1; j++) 
    { 
        if (arr[j] < pivot) 
        { 
            i++;  
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(arr, low, high);  
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 
void printArray(int arr[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("n\n"); 
} 
  
int main() 
{ 
    int arr[100000];
    int index = 0;
    for(int i=100000;i>=0;i--){
       arr[index++]=i;
    }
    double wtime = omp_get_wtime(); 
    int n = sizeof(arr)/sizeof(arr[0]);
    int j = partition(arr,0,n-1); 
    #pragma omp sections
    {
      #pragma omp section
      {
        quickSort(arr, 0, j-1);
      }
      #pragma omp section
      {
        quickSort(arr,j+1, n-1);
      }
    } 
    wtime = omp_get_wtime()-wtime;
    printf("Sorted array: n"); 
    printArray(arr, n); 
    printf("------------------------------------\n");
    printf("Execution time of sequential Quick sort is : %lf\n",wtime);
    return 0; 
} 
