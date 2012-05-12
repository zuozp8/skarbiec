#include "inputthread.hpp"
#include <mpi/mpi.h>
#include <iostream>

int size, rank;

InputThread::InputThread(QObject *parent) :
    QThread(parent)
{
	moveToThread(this);
}

void InputThread::listen()
{
	MPI_Recv(bufor, 2, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	quit();
}

void InputThread::run()
{
	QMetaObject::invokeMethod(this, "listen", Qt::QueuedConnection);

	exec();
}
