#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[])
{
	int rank, size, resultLen;
	char name[MPI_MAX_PROCESSOR_NAME];
	int msg{};
	int root = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(name, &resultLen);

	do
	{
		fflush(stdout);
		if (rank == root)
		{

			printf("MSG: ");
			scanf_s("%d", &msg);
			fflush(stdout);
		}

		MPI_Bcast(&msg, 1, MPI_INT, root, MPI_COMM_WORLD);
		printf("Process %3d on %s: %d\n", rank, name, msg);
		//fflush(stdout);

	} while (msg > 0);

	MPI_Finalize();
	return 0;
}

