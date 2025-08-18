//write an open mp prog,  to transform each element with a[i]=3*a[i]+2.
//Using #pragma omp parallel for scheduke (dynamic,2),Then switch to static,2.
//int a1[6]={1,2,3,4,5,6};//dynamic.2
//int a2[6]={1,2,3,4,5,6};//static,2

#include <stdio.h>
#include <omp.h>

int main() {
    int a1[6] = {1, 2, 3, 4, 5, 6};  
    int a2[6] = {1, 2, 3, 4, 5, 6};  

    int i;
    #pragma omp parallel for schedule(dynamic, 2)
    for (i = 0; i < 6; i++) {
        a1[i] = 3 * a1[i] + 2;
    }

   
    #pragma omp parallel for schedule(static, 2)
    for (i = 0; i < 6; i++) {
        a2[i] = 3 * a2[i] + 2;
    }

  
    printf("Array a1 after dynamic schedule:\n");
    for (i = 0; i < 6; i++) {
        printf("%d ", a1[i]);
    }
    printf("\n");

   
    printf("Array a2 after static schedule:\n");
    for (i = 0; i < 6; i++) {
        printf("%d ", a2[i]);
    }
    printf("\n");

    return 0;
}
