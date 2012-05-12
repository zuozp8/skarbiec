#include "outputthread.hpp"
#include "inputthread.hpp"
#include <mpi/mpi.h>

OutputThread::OutputThread(QObject *parent) :
    QThread(parent)
{
	czyRabuje=false;
	qsrand(time(0));
}

int OutputThread::exec()
{

	forever {
		int waitTime = qrand()%10+3;
		sleep(waitTime);
		for (int i=0; i<size; i++) {
			if (i == rank) continue;
			int bufor[2];
			MPI_Send(bufor,2,MPI_INT,i,(rand()%2?TAG_ZWALNIANIE_ZASOBOW:TAG_ZAJMOWANIE_ZASOBOW),MPI_COMM_WORLD);
		}
	}
	return 0;
}
