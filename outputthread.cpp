#include "outputthread.hpp"
#include "inputthread.hpp"
#include <mpi/mpi.h>
#include <iostream>

OutputThread::OutputThread(QObject *parent) :
    QThread(parent)
{
	moveToThread(this);
	czyRabuje=false;
}

void OutputThread::wyslij(int czas,int ileW, int odbiorca, int tag)
{
	std::cout<<rank<<'|'<<"Wysylam:\tczas="<<czas<<"\tile="<<ileW<<"\tdo="<<odbiorca<<"\ttag="<<TAG_TO_STRING(tag)<<std::endl;
	int bufor[2];
	bufor[0] = czas;
	bufor[1] = ileW;
	if(odbiorca >= 0) {
		MPI_Send(bufor, 2, MPI_INT, odbiorca, tag, MPI_COMM_WORLD);
	}
	else
	{
		for (int i=0; i<size; i++) {
			if (i == rank) continue;
			MPI_Send(bufor, 2, MPI_INT, i, tag, MPI_COMM_WORLD);
		}
	}
}


void OutputThread::run()
{
	exec();
}
