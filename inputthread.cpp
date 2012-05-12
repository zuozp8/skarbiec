#include "inputthread.hpp"
#include <mpi/mpi.h>

InputThread::InputThread(QObject *parent) :
    QThread(parent)
{
}

int InputThread::exec()
{
	int bufor[2];
	MPI_Status status;
	forever {
		MPI_Recv(bufor, 3, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		if (status.MPI_TAG == TAG_ZWALNIANIE_ZASOBOW) {
			emit wiadomoscOZwolnieniuZasobow(bufor[0],status.MPI_SOURCE,bufor[1]);
		} else {
			emit wiadomoscOZajeciuZasobow(bufor[0],status.MPI_SOURCE,bufor[1]);
		}
	}
	return 0;
}
