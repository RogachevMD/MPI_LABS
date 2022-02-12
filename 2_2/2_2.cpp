#include <mpi.h>
#include <iostream>

#define NUM_DIMS 1

int main(int argc, char* argv[])
{
	int rank, size;
	int A, B;
	int dims[NUM_DIMS], periods[NUM_DIMS], newPos[NUM_DIMS];
	int sb, db, sm, dm;
	int reorder = 0;

	MPI_Comm commCart;
	MPI_Status status;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	for (int i = 0; i < NUM_DIMS; i++) { //������� ��������� �������
		dims[i] = 0;
		periods[i] = 0;
	}

	MPI_Dims_create(size, NUM_DIMS, dims); //������� ���������
	MPI_Cart_create(MPI_COMM_WORLD, NUM_DIMS, dims, periods, reorder, &commCart); //�������� ���������
	MPI_Cart_coords(commCart, rank, NUM_DIMS, newPos); //�����

	A = newPos[0];
	B = -1;
	int tag = 1, count = 1;

	//�������� �� ����������� ��������
	if (newPos[0] == 0)
		sm = dm = MPI_PROC_NULL;
	else
		sm = dm = (newPos[0] - 1);

	if (newPos[0] == (dims[0] - 1))
		db = sb = MPI_PROC_NULL;
	else
		db = sb = (newPos[0] + 1);

	//�������� � ���� �������
	MPI_Sendrecv(	&A, count, MPI_INT, db, tag, //���������� ����������
					&B, count, MPI_INT, sm, tag, //�������� �� �����������
					commCart, &status);
	printf("newPos[0]=%3d; B=%3d\n", newPos[0], B);

	//�������� � ������ �������
	MPI_Sendrecv(	&A, count, MPI_INT, dm, tag, //���������� ����������
					&B, count, MPI_INT, sb, tag, //�������� �� �����������
					commCart, &status);
	printf("newPos[0]=%3d; B=%3d\n", newPos[0], B);

	MPI_Comm_free(&commCart);
	MPI_Finalize();
	return 0;
}

