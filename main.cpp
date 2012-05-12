#include <mpi/mpi.h>
#include <iostream>
#include <QtCore/QCoreApplication>

#include "mainobject.hpp"


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	MPI_Init(&argc, &argv);

	MainObject mainObject;

	a.exec();
	MPI_Finalize();
	return 0;
}
