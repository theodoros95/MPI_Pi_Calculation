#include <mpi.h>
#include <math.h>
#include <stdio.h>

#define N 8400000

int main(int argc, char *argv[]) {
    int rank, nprocs, len;
    char name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(name, &len);

    double sum = 0;

    double windowSize = (double) N / nprocs;

    for (int i = 1 + windowSize * rank; i <= windowSize * (rank + 1); ++i) {

        sum += 1 / (1 + pow((i - 0.5) / N, 2));
    }

    if (rank != 0) {

        MPI_Ssend(&sum, 1, MPI_DOUBLE, 0, NULL, MPI_COMM_WORLD);

    } else {

        MPI_Status status;

        double temp;

        for (int i = 1; i < nprocs; ++i) {

            MPI_Recv(&temp, 1, MPI_DOUBLE, i, NULL, MPI_COMM_WORLD, &status);

            sum += temp;
        }

        printf("%f\n", sum / N * 4);
    }

    MPI_Finalize();

    return 0;
}
