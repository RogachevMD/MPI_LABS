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
	root = size / 2;

	int fromTgt = ((rank == 0 ? size : rank)) - 1;
	int toTgt = (rank == (size - 1)) ? 0 : (rank + 1);

	int bufferSize = 10;
	int msgTag = 10;

	if (rank == root)
	{
		msg = 1000;

		MPI_Send(&msg, bufferSize, MPI_INT, toTgt, msgTag,
			MPI_COMM_WORLD);

		MPI_Recv(&msg, bufferSize, MPI_INT, fromTgt, msgTag,
			MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

		printf("msg from %3d to %3d: %d", fromTgt, rank, msg);
		fflush(stdout);

	}
	else
	{
		MPI_Recv(&msg, bufferSize, MPI_INT, fromTgt, msgTag,
			MPI_COMM_WORLD, MPI_STATUSES_IGNORE);

		printf("msg from %3d to %3d: %d", fromTgt, rank, msg);
		fflush(stdout);
		msg++; //для наглядности
		MPI_Send(&msg, bufferSize, MPI_INT, toTgt, msgTag,
			MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}

