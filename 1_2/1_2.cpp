#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[])
{
	int rank, size, resultLen;
	char name[MPI_MAX_PROCESSOR_NAME];
	int root = 0;
	int msg{};
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(name, &resultLen);
	//printf("%d", size);
	do {

		//fflush(stdout);

		if (rank == root) {
			//printf("Process %3d on %s: %d old msg\n", rank, name, msg);
			//fflush(stdout);
			scanf_s("%d", &msg);
			printf("MSG: %4d\n", msg);
			printf("Process %3d on %s: %d\n", rank, name, msg);
			//fflush(stdout);

		}

		MPI_Bcast(&msg, 1, MPI_INT, root, MPI_COMM_WORLD);

		if (rank != root) {
			printf("Process %3d on %s: %d\n", rank, name, msg);
		}

		fflush(stdout);

	} while (msg > 0);

	MPI_Finalize();
	return 0;
}

