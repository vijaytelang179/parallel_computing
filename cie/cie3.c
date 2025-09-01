//modify the prog.  to find the largest prime number less than n.
//2 conditions:if number is 2 print error msg that there is o prime number less than 2

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// Function to check if a number is prime
int isPrime(int num) {
    if (num <= 1)
        return 0;
    if (num == 2)
        return 1;
    if (num % 2 == 0)
        return 0;

    int limit = sqrt(num);
    for (int i = 3; i <= limit; i += 2) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int main() {
    int n;
    int found = 0;
    int result = -1;

    printf("Enter a number: ");
    scanf("%d", &n);

    if (n <= 2) {
        printf("Error: There is no prime number less than 2.\n");
        return 0;
    }

    #pragma omp parallel for shared(found, result)
    for (int i = n - 1; i >= 2; --i) {
    
        if (!found && isPrime(i)) {
            #pragma omp critical
            {
                if (!found) {
                    result = i;
                    found = 1;
                }
            }
        }
    }

    if (found)
        printf("The largest prime number less than %d is: %d\n", n, result);
    else
        printf("No prime number found less than %d.\n", n);

    return 0;
}
