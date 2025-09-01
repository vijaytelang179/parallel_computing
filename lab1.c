#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define min_size 1000

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *l = (int *)malloc(n1 * sizeof(int));
    int *r = (int *)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++) l[i] = arr[left + i];
    for (j = 0; j < n2; j++) r[j] = arr[mid + 1 + j];

    i = 0; j = 0; k = left;
    while (i < n1 && j < n2) {
        if (l[i] <= r[j]) arr[k++] = l[i++];
        else arr[k++] = r[j++];
    }
    while (i < n1) arr[k++] = l[i++];
    while (j < n2) arr[k++] = r[j++];
    free(l);
    free;
}

void mergesortsequential(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergesortsequential(arr, left, mid);
        mergesortsequential(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergesortparallel(int arr[], int left, int right) {
    if ((right - left + 1) <= min_size) {
        mergesortsequential(arr, left, right);
        return;
    }
    if (left < right) {
        int mid = left + (right - left) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            { mergesortparallel(arr, left, mid); }
            #pragma omp section
            { mergesortparallel(arr, mid + 1, right); }
        }
        merge(arr, left, mid, right);
    }
}

int main() {
    int n = 100000;
    int *arr_seq = (int *)malloc(n * sizeof(int));
    int *arr_par = (int *)malloc(n * sizeof(int));

    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr_par[i] = arr_seq[i] = rand() % 10000;
    }

    printf("sorting %d elements…\n\n", n);

    double start_time = omp_get_wtime();
    mergesortsequential(arr_seq, 0, n - 1);
    double time_seq = omp_get_wtime() - start_time;
    printf("sequential merge sort time: %f seconds\n", time_seq);

    start_time = omp_get_wtime();
    mergesortparallel(arr_par, 0, n - 1);
    double time_par = omp_get_wtime() - start_time;
    printf("parallel merge sort time:   %f seconds\n", time_par);

    printf("\n difference (sequential - parallel): %f seconds\n", time_seq - time_par);
    if (time_par > 0) printf("speedup: %.2fx\n", time_seq / time_par);

    printf("\n verification: first 20 elements of the sorted array:\n");
    for (int i = 0; i < (n < 20 ? n : 20); i++)
        printf("%d ", arr_par[i]);
    printf("\n");

    free(arr_seq);
    free(arr_par);
    return 0;
}