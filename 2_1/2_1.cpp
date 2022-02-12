#include <mpi.h>
#include <iostream>

#define NUM_DIMS 1

int main(int argc, char* argv[])
{
	int rank, size, A, B, dims[NUM_DIMS];
	int periods[NUM_DIMS], source, dest;
	int reorder = 0;

	MPI_Comm commCart;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	A = rank;
	B = -1;
	int tag = 1, count = 1;

	for (int i = 0; i < NUM_DIMS; i++) //задаие топологии кольцо
	{
		dims[i] = 0;
		periods[i] = 1;
	}
	MPI_Dims_create(size, NUM_DIMS, dims); //задание топологии
	MPI_Cart_create(MPI_COMM_WORLD, NUM_DIMS, dims, periods, reorder, &commCart); //описание структуры
	MPI_Cart_shift(commCart, 0, 1, &source, &dest); //сдвиг

	MPI_Sendrecv(	&A, count, MPI_INT, dest, tag, //отправляет следующему
					&B, count, MPI_INT, source, tag, //получает от предыдущего
					commCart, &status);

	printf("current rank: %3d, previous rank: %3d\n", rank, B);

	MPI_Comm_free(&commCart);
	MPI_Finalize();
	return 0;
}

