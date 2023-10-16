#include <iostream>
#include "mpi.h"

int main(int argc, char* argv[])
{
    int processesCount, processRank, receivedRank;
    double start, end;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &processesCount);
    int numsCount = processesCount + 5;
    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);

    int* nums = (int*)calloc(numsCount, sizeof(int));
    int* minValues = (int*)calloc(numsCount, sizeof(int));

    if (!nums || !minValues) {
        printf("Memory Error!\n");
        exit(-1);
    }

    srand(time(NULL) + processRank * processesCount);

    for (int i = 0; i < numsCount; ++i) {
        nums[i] = rand();
    }

    MPI_Reduce(nums, minValues, numsCount, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    if (processRank == 0) {
        for (int i = 0; i < numsCount; ++i) {
            printf("Min Value at %d Position: %d\n", i, minValues[i]);
        }
    }

    MPI_Finalize();

    free(nums);
    free(minValues);
}
