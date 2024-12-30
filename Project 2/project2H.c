#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int *AllocateArray(int N)
{
    /* Allocate an array with N integers.    
     * The value of each element of the array should be a
     * random number between 0 and 10N.    
     * Hint: use the rand() function and a modulo operator.    
     */
    int *outp = malloc(N*sizeof(int));
    for (int i=0; i<N; i++)
    {
        outp[i] = rand()%(10*N);
    }
    return outp;
}

void SortArray(int N, int *A)
{
    int i;
    for (i=0; i<N; i++)
    {
        int j;
        for (j=i+1; j<N; j++)
        {
            if (A[j] < A[i])
            {
                int tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
            }
        }
    }
}

void DeallocateArray(int *A)
{
    free(A);
}

int MyEq(const void *a, const void *b)
    {
        return *(int*)a - *(int*)b;
    }

void MyQsort(int N, int *A)
{
    qsort(A, N, sizeof(int), MyEq);
}

int main()
{
    int sizes[8] = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000 };

/* For fun:
 *  int sizes[11] = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000,
 *                    256000, 512000, 1024000 }; 
 */

    for (int i = 0 ; i < 8 ; i++)
    {
        double alloc_time = 0., sort_time = 0., dealloc_time = 0.;
        struct timeval startTime;
        struct timeval endTime;

        /* Call the three functions in a sequence. Also use
         * gettimeofday calls surrounding each function and set the 
         * corresponding variable (alloc_time, sort_time, dealloc_time).
         */
        gettimeofday(&startTime,0);
        int *array = AllocateArray(sizes[i]);
        gettimeofday(&endTime,0);
        alloc_time = (double)(endTime.tv_sec-startTime.tv_sec) + 
                     (double)(endTime.tv_usec-startTime.tv_usec) / 1000000.;

        gettimeofday(&startTime,0);
        MyQsort(sizes[i], array);
        gettimeofday(&endTime,0);
        sort_time = (double)(endTime.tv_sec-startTime.tv_sec) + 
                     (double)(endTime.tv_usec-startTime.tv_usec) / 1000000.;
        
        gettimeofday(&startTime,0);
        DeallocateArray(array);
        gettimeofday(&endTime,0);
        dealloc_time = (double)(endTime.tv_sec-startTime.tv_sec) + 
                     (double)(endTime.tv_usec-startTime.tv_usec) / 1000000.;

        printf("Timings for array of size %d\n", sizes[i]);
        printf("\tTime for allocation is %g, time per element = %g\n", alloc_time, alloc_time/sizes[i]);
        printf("\tTime for sort_time is %g, time per element = %g\n", sort_time, sort_time/sizes[i]);
        printf("\tTime for deallocation is %g\n", dealloc_time);
    }
}