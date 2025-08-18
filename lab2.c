#include<stdio.h>
#include <omp.h>

int main(){
    int num_iterations;
    printf("ENTER THE NUMBER OF ITERATIONS");
    scanf("%d",&num_iterations);
    #pragma omp parallel

    {
        #pragma omp for schedule(static,2)
        for(int i=0;i<num_iterations;i++){
            #pragma omp ordered
            printf("Thread %d:Iteration %d\n ",omp_get_thread_num(),i);
        }
    }
    return 0;
}
